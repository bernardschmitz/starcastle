
#include <math.h>
#include <time.h>

#include <allegro.h>

#include "data.h"

struct Rect {
   int sx, sy, ex, ey;
};

RGB_MAP rgbmap;
COLOR_MAP trans;

const int D = 1;

const int cir1 = 90; // 64+48-4;
const int cir2 = 64+24-4;
const int cir3 = 64+0-4;

int black;
int white;
int green;
int red;
int blue;
int yellow;

float w1, w2, w3;
float dw1, dw2, dw3;

   DATAFILE *data;

   float xpos;
   float ypos;
   float xvel = 0;
   float yvel = 0;
   int dir = 0;
   int thrust = 0;
   int shoot = 0;
   int shootdel = 2/D;
   int shootcnt = 0;

   int expl = -2;
   int expldel = 4/D;
   int explcnt = 0;

   int other = 0;

   BITMAP *pbmPage[2];
   static Rect dirty[3][2];

volatile int fps = 0;
volatile int frames = 0;
int nPage = 0;

volatile int target_cycle = 0;
int actual_cycle = 0;
volatile int ticker = 0;
volatile int lastfrm = 0;
const int cps = 60/D;

void cycle_inc(...) {

   target_cycle++;
   ticker++;
   if(ticker == cps) {
      fps = frames - lastfrm;
      lastfrm = frames;
      ticker = 0;
   }
}
END_OF_FUNCTION(cycle_inc);


RGB additive(PALETTE p, int x, int y) {

   RGB c;

   c.r = p[x].r + p[y].r;
   c.g = p[x].g + p[y].g;
   c.b = p[x].b + p[y].b;

   if(c.r > 63)
      c.r = 63;
   if(c.g > 63)
      c.g = 63;
   if(c.b > 63)
      c.b = 63;

   return(c);
}

void show(int i) {

   line(screen, 5+i, 35, 5+i, 45, red);
}

void wall(BITMAP *bm, int x, int y, int r, float aa, int c) {

   float a = aa;
   float da = 2.0*PI/12.0;

   float ox = (float)x + (float)r*cos(a-da);
   float oy = (float)y + (float)r*sin(a-da);

   for(int i=0; i<12; i++) {
      float fx = (float)x + (float)r*cos(a);
      float fy = (float)y + (float)r*sin(a);

//      line(bm, (int)ox, (int)oy, (int)fx, (int)fy, c);

      int wang = (int)(a*63.0/(2.0*PI));
      wang = (15-wang)&0x3f;
      switch(r) {
/*         case cir3 : draw_rle_sprite(bm, (RLE_SPRITE *)data[wallc000+wang].dat, (int)fx-16, (int)fy-16);
                     break;
         case cir2 : draw_rle_sprite(bm, (RLE_SPRITE *)data[wallb000+wang].dat, (int)fx-24, (int)fy-24);
                     break;
         */
         case cir1 : draw_rle_sprite(bm, (RLE_SPRITE *)data[walla000+wang].dat, (int)fx-32, (int)fy-32);
                     break;
      }

      a += da;
      if(a >= 2.0*PI)
         a -= 2.0*PI;
      if(a < 0.0)
         a += 2.0*PI;
      ox = fx;
      oy = fy;
   }
}

int gameloop(void) {

   int done = 0;

      if(key[KEY_RIGHT])
         dir--;

      if(key[KEY_LEFT])
         dir++;

      dir &= 0x3f;

      if(key[KEY_ESC])
         done = 1;

      if(key[KEY_SPACE] && expl < 0) {
         explcnt = expldel;
         expl = 29;
      }

      explcnt--;
      if(explcnt == 0) {
         expl--;
         explcnt = expldel;
      }

      if(key[KEY_UP]) {
         shoot = 0;
         thrust++;
         if(thrust > 7)
            thrust = 7;
         xvel += sin(dir*2.0*PI/63.0)/5*D;
         yvel += cos(dir*2.0*PI/63.0)/5*D;
      }
      else {
         if(thrust > 0)
            thrust--;
      }

      if(shootcnt > 0) {
         shootcnt--;
         if(shootcnt == 0) {
            if(shoot < 0) {
               shoot++;
               shootcnt = shootdel;
               //line(pbmPage[nPage], (int)xpos, (int)ypos, (int)(xpos-sin(dir*2.0*PI/63.0)*200), (int)(ypos-cos(dir*2.0*PI/63.0)*200), 255);
            }
         }
      }

      if(key[KEY_LCONTROL] && shoot == 0) { // && thrust == 0) {
         thrust = 0;
         shoot = -7;
         shootcnt = shootdel;
         xvel -= sin(dir*2.0*PI/63.0)/25*D;
         yvel -= cos(dir*2.0*PI/63.0)/25*D;
      }

      xpos -= xvel;
      ypos -= yvel;

      if(xpos < 0)
         xpos = SCREEN_W-1;
      if(xpos > SCREEN_W-1)
         xpos = 0;

      if(ypos < 0)
         ypos = SCREEN_H-1;
      if(ypos > SCREEN_H-1)
         ypos = 0;

      float dx = xpos - SCREEN_W/2;
      float dy = ypos - SCREEN_H/2;

      other = (int)((PI + atan2(-dy, dx)) * 63 / (2.0*PI));

      other = (other + 1*16) & 0x3f;

      if(dx*dx+dy*dy < (cir1+16)*(cir1+16)) {

         float dist = sqrt(dx*dx + dy*dy) + 0.1;
         float radx = dx / dist;
         float rady = dy / dist;

         float vmag = sqrt(xvel*xvel + yvel*yvel) + 0.1;

         float vx = xvel / vmag;
         float vy = yvel / vmag;

         float nl = radx*vx + rady*vy;

         float rx = 2*radx*nl - vx;
         float ry = 2*rady*nl - vy;

         xvel = rx * -vmag;
         yvel = ry * -vmag;
      }

      w1 += dw1;
      if(w1 > 2.0*PI)
         w1 -= 2.0*PI;
      if(w1 < 0.0)
         w1 += 2.0*PI;

      w2 += dw2;
      if(w2 > 2.0*PI)
         w2 -= 2.0*PI;
      if(w2 < 0.0)
         w2 += 2.0*PI;

      w3 += dw3;
      if(w3 > 2.0*PI)
         w3 -= 2.0*PI;
      if(w3 < 0.0)
         w3 += 2.0*PI;

      actual_cycle++;

      return(done);
}

void render(void) {

//blit((BITMAP *)data[stars].dat, pbmPage[nPage], 0, 0, 0, 0, SCREEN_W, SCREEN_H);

      for(int i=0; i<2; i++) {
         int sx = dirty[nPage][i].sx;
         int sy = dirty[nPage][i].sy;
         int w = dirty[nPage][i].ex - sx + 1;
         int h = dirty[nPage][i].ey - sy + 1;
         blit((BITMAP *)data[stars].dat, pbmPage[nPage], sx, sy, sx, sy, w, h);
         //rectfill(pbmPage[nPage], dirty[i][nPage].sx, dirty[i][nPage].sy, dirty[i][nPage].ex, dirty[i][nPage].ey, 0);
      }
      if(expl > -1) {
         int sx = dirty[2][nPage].sx;
         int sy = dirty[2][nPage].sy;
         int w = dirty[2][nPage].ex - sx + 1;
         int h = dirty[2][nPage].ey - sy + 1;
         blit((BITMAP *)data[stars].dat, pbmPage[nPage], sx, sy, sx, sy, w, h);
         //rectfill(pbmPage[nPage], dirty[2][nPage].sx, dirty[2][nPage].sy, dirty[2][nPage].ex, dirty[2][nPage].ey, 0);
         expl--;
      }

// delete walls
blit((BITMAP *)data[stars].dat, pbmPage[nPage], SCREEN_W/2-120, SCREEN_H/2-120, SCREEN_W/2-120, SCREEN_H/2-120, 240, 240);
// delete text
blit((BITMAP *)data[stars].dat, pbmPage[nPage], 0, 0, 0, 0, 80, 20);


      int ddir = dir/2 * 16 + 7;
      draw_rle_sprite(pbmPage[nPage], (RLE_SPRITE *)data[player000+ddir+thrust+shoot].dat, (int)xpos-32, (int)ypos-32);
      //rotate_sprite(pbmPage[nPage], (BITMAP *)data[test007+thrust+shoot].dat, (int)xpos-32, (int)ypos-32, ((63-(dir-1)&0x3f)*4)<<16);
      dirty[nPage][0].sx = (int)xpos-32;
      dirty[nPage][0].sy = (int)ypos-32;
      dirty[nPage][0].ex = (int)xpos-32+64;
      dirty[nPage][0].ey = (int)ypos-32+64;

      int dother = other/2;
      draw_rle_sprite(pbmPage[nPage], (RLE_SPRITE *)data[castle000+other].dat, SCREEN_W/2-64, SCREEN_H/2-64);
      //rotate_sprite(pbmPage[nPage], (BITMAP *)data[leng].dat, SCREEN_W/2-64, SCREEN_H/2-64, ((63-(other-1)&0x3f)*4)<<16);
      dirty[nPage][1].sx = SCREEN_W/2-64;
      dirty[nPage][1].sy = SCREEN_H/2-64;
      dirty[nPage][1].ex = SCREEN_W/2-64+128;
      dirty[nPage][1].ey = SCREEN_H/2-64+128;

      if(expl > 0) {
         draw_trans_rle_sprite(pbmPage[nPage], (RLE_SPRITE *)data[expa000+29-expl].dat, (int)xpos-64, (int)ypos-64);
         dirty[nPage][0].sx = (int)xpos-64;
         dirty[nPage][0].sy = (int)ypos-64;
         dirty[nPage][0].ex = (int)xpos-64+128;
         dirty[nPage][0].ey = (int)ypos-64+128;

      }

      //circle(pbmPage[nPage], SCREEN_W/2, SCREEN_H/2, cir+0, blue);
      //circle(pbmPage[nPage], SCREEN_W/2, SCREEN_H/2, cir+24, green);
      //circle(pbmPage[nPage], SCREEN_W/2, SCREEN_H/2, cir+48, red);
      wall(pbmPage[nPage], SCREEN_W/2, SCREEN_H/2, cir1, w1, blue);
      wall(pbmPage[nPage], SCREEN_W/2, SCREEN_H/2, cir2, w2, green);
      wall(pbmPage[nPage], SCREEN_W/2, SCREEN_H/2, cir3, w3, red);

textprintf(pbmPage[nPage], (FONT *)data[xm10x20].dat, 0, 0, yellow, "fps %3d", fps);


      
      scroll_screen(0, nPage*SCREEN_H);

      frames++;

      if(nPage == 0)
         nPage = 1;
      else
         nPage = 0;
}


int main(void) {

   allegro_init();
   install_keyboard();
   install_timer();
   set_color_depth(8);
   set_gfx_mode(GFX_AUTODETECT, 640, 480, 640, 960);
   text_mode(-1);
   clear(screen);
   textout(screen, font, "Loading graphics...", 0, 0, 15);

   data = load_datafile("data.dat");

   set_palette((PALETTE)data[pal].dat);

   black = makecol(0, 0, 0);
   white = makecol(255, 255, 255);
   red = makecol(255, 0, 0);
   green = makecol(0, 255, 0);
   blue = makecol(0, 0, 255);
   yellow = makecol(255, 255, 0);

   clear(screen);
   textout(screen, (FONT *)data[xm10x20].dat, "Calculating rgb table...", 0, 0, green);
   rectfill(screen, 0, 30, 256+6, 30+20, white);
   rectfill(screen, 3, 33, 256+3, 30+20-3, blue);
   create_rgb_table(&rgbmap, (PALETTE)data[pal].dat, show);
   rgb_map = &rgbmap;

   clear(screen);
   textout(screen, (FONT *)data[xm10x20].dat, "Calculating transparency table...", 0, 0, green);
   rectfill(screen, 0, 30, 256+6, 30+20, white);
   rectfill(screen, 3, 33, 256+3, 30+20-3, blue);
   create_color_table(&trans, (PALETTE)data[pal].dat, additive, show);

   color_map = &trans;



   int done = 0;


   pbmPage[0] = create_sub_bitmap(screen, 0, 0, SCREEN_W, SCREEN_H);
   pbmPage[1] = create_sub_bitmap(screen, 0, SCREEN_H, SCREEN_W, SCREEN_H);


   clear(pbmPage[0]);
   clear(pbmPage[1]);

   blit((BITMAP *)data[stars].dat, pbmPage[0], 0, 0, 0, 0, SCREEN_W, SCREEN_H);
   blit((BITMAP *)data[stars].dat, pbmPage[1], 0, 0, 0, 0, SCREEN_W, SCREEN_H);

   for(int i=0; i<3; i++) {
      dirty[i][0].sx = 0;
      dirty[i][0].sy = 0;
      dirty[i][0].ex = 0;
      dirty[i][0].ey = 0;
      dirty[i][1].sx = 0;
      dirty[i][1].sy = 0;
      dirty[i][1].ex = 0;
      dirty[i][1].ey = 0;
   }

   xpos = SCREEN_W/4;
   ypos = SCREEN_H*3/4;

   w1 = 0.0;
   w2 = 0.0;
   w3 = 0.0;

   dw1 = 2.0*PI/60/5;
   dw2 = -2.0*PI/90/5;
   dw3 = 2.0*PI/120/5;

   LOCK_VARIABLE(fps);
   LOCK_VARIABLE(frames);
   LOCK_VARIABLE(target_cycle);
   LOCK_VARIABLE(ticker);
   LOCK_VARIABLE(lastfrm);
   LOCK_FUNCTION(cycle_inc);

   install_int_ex(cycle_inc, BPS_TO_TIMER(cps));

   actual_cycle = target_cycle = 0;

   frames = 0;

   while(!done) {

      render();

      while(actual_cycle >= target_cycle)
         ;

      done = 0;
      while(target_cycle > actual_cycle)
         done += gameloop();

//      render();
//      done = gameloop();
   }

   set_gfx_mode(GFX_TEXT, 80, 25, 0, 0);

   return(0);
}

