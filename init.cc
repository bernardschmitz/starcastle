
// $Id: init.cc,v 1.4 2004-06-24 01:01:42 bernard Exp $

#include <stdio.h>
#include <string.h>
#include <allegro.h>

#include "init.h"
#include "console.h"
#include "param.h"

#include "data.h"
#include "title.h"

RGB_MAP rgbmap;
COLOR_MAP trans;
COLOR_MAP lites;
//COLOR_MAP transTitle;
//COLOR_MAP litesTitle;

int fPageFlipping = 0;

int nRed;
int nGreen;
int nBlue;
int nBlack;
int nWhite;
int nYellow;

BITMAP *pbmBackground;
BITMAP *pbmPage[2];
int nPage = 0;

DATAFILE *pdatGraphics;
DATAFILE *pdatTitle;

PALETTE palPalette;
PALETTE palBlack, palWhite, palGray;

PALETTE palTitle;
RLE_SPRITE *prleStarTitle;
RLE_SPRITE *prleCastleTitle;

FONT *rgpfntFont[4];

RLE_SPRITE *rgprleCastle[1024];
RLE_SPRITE *rgprlePlayer[512];
RLE_SPRITE *rgrgprleExplosions[4][30];
RLE_SPRITE *rgrgprleSmallExp[4][30];
RLE_SPRITE *rgprleShock[2][24];
RLE_SPRITE *rgprleShot[8];
RLE_SPRITE *rgprleBomb[16];
RLE_SPRITE *rgprleLaser[5*32];
RLE_SPRITE *rgprleOuter[128];
RLE_SPRITE *rgprleMiddle[128];
RLE_SPRITE *rgprleInner[64];

BITMAP *pbmStars;

volatile int fps = 0;
volatile int frames = 0;
volatile int target_cycle = 0;
volatile int ticker = 0;
volatile int lastfrm = 0;
volatile int timer = 0;
int actual_cycle = 0;

void cycle_inc() {

   target_cycle++;
   ticker++;
   if(ticker == kFrameRate) {
      fps = frames - lastfrm;
      lastfrm = frames;
      ticker = 0;
   }
}
END_OF_FUNCTION(cycle_inc);

void timer_inc() {

   timer++;
}
END_OF_FUNCTION(timer_inc);

void additive(const RGB *p, int x, int y, RGB *rgb) {

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

//   return(c);

   *rgb = c;
}

void InitColors(void) {

   set_palette(palPalette);

   Console("Setting palettes...");
   for(int i=0; i<256; i++) {
      palBlack[i].r = 0;
      palBlack[i].g = 0;
      palBlack[i].b = 0;
      palWhite[i].r = 63;
      palWhite[i].g = 63;
      palWhite[i].b = 63;

      int gg = palPalette[i].r*30/100 +
               palPalette[i].g*59/100 +
               palPalette[i].b*11/100;

      palGray[i].r = gg;
      palGray[i].g = gg;
      palGray[i].b = gg;
   }

   Console("Calculating rgb table...");
   create_rgb_table(&rgbmap, palPalette, NULL);
   rgb_map = &rgbmap;

   Console("Calculating transparency table...");
   create_color_table(&trans, palPalette, additive, NULL);
   color_map = &trans;

   Console("Calculating light table...");
   create_light_table(&lites, palPalette, 0, 0, 0, NULL);

   nRed = makecol(255, 0, 0);
   nGreen = makecol(0, 255, 0);
   nBlue = makecol(0, 0, 255);
   nBlack = makecol(0, 0, 0);
   nWhite = makecol(255, 255, 255);
   nYellow = makecol(255, 255, 0);

   /*
   Console("Calculating rgb table...");
   create_rgb_table(&rgbmap, palTitle, NULL);
   rgb_map = &rgbmap;

   Console("Calculating transparency table...");
   create_color_table(&transTitle, palTitle, additive, NULL);

   Console("Calculating light table...");
   create_light_table(&litesTitle, palTitle, 0, 0, 0, NULL);
   */
}

void InitScreen(void) {

   if(fPageFlipping) {
      pbmPage[0] = create_sub_bitmap(screen, 0, 0, SCREEN_W, SCREEN_H);
      pbmPage[1] = create_sub_bitmap(screen, 0, SCREEN_H, SCREEN_W, SCREEN_H);
   }
   else {
      pbmPage[0] = create_bitmap(SCREEN_W, SCREEN_H);
      pbmPage[1] = create_bitmap(SCREEN_W, SCREEN_H);
   }

   pbmBackground = create_bitmap(SCREEN_W, SCREEN_H);
   clear(pbmBackground);
}

int LoadGraphics(char *sz) {

   pdatGraphics = load_datafile(sz);

   if(pdatGraphics == NULL)
      return(1);

   Console("Fonts...");
   rgpfntFont[0] = (FONT *)pdatGraphics[xm10x20].dat;
   rgpfntFont[1] = (FONT *)pdatGraphics[xm10x20b].dat;
   rgpfntFont[2] = (FONT *)pdatGraphics[helv17i].dat;
   rgpfntFont[3] = (FONT *)pdatGraphics[helv38b].dat;

   Console("Palette...");
   memcpy(palPalette, (RGB *)pdatGraphics[pal].dat, sizeof(PALETTE));

   Console("Castle frames...");
   for(int i=0; i<1024; i++)
      rgprleCastle[i] = (RLE_SPRITE *)pdatGraphics[sca000+i].dat;

   Console("Player frames...");
   for(int i=0; i<512; i++)
      rgprlePlayer[i] = (RLE_SPRITE *)pdatGraphics[player000+i].dat;

   Console("Explosion frames...");
   for(int i=0; i<30; i++) {
      rgrgprleExplosions[0][i] = (RLE_SPRITE *)pdatGraphics[expa000+i].dat;
      rgrgprleExplosions[1][i] = (RLE_SPRITE *)pdatGraphics[expb000+i].dat;
      rgrgprleExplosions[2][i] = (RLE_SPRITE *)pdatGraphics[expc000+i].dat;
      rgrgprleExplosions[3][i] = (RLE_SPRITE *)pdatGraphics[expd000+i].dat;
      rgrgprleSmallExp[0][i] = (RLE_SPRITE *)pdatGraphics[sexpa000+i].dat;
      rgrgprleSmallExp[1][i] = (RLE_SPRITE *)pdatGraphics[sexpb000+i].dat;
      rgrgprleSmallExp[2][i] = (RLE_SPRITE *)pdatGraphics[sexpc000+i].dat;
      rgrgprleSmallExp[3][i] = (RLE_SPRITE *)pdatGraphics[sexpd000+i].dat;
   }

   Console("Shot frames...");
   for(int i=0; i<8; i++)
      rgprleShot[i] = (RLE_SPRITE *)pdatGraphics[shot000+i].dat;

   Console("Bomb frames...");
   for(int i=0; i<16; i++)
      rgprleBomb[i] = (RLE_SPRITE *)pdatGraphics[bomb000+i].dat;

   Console("Laser frames...");
   for(int i=0; i<32*5; i++)
      rgprleLaser[i] = (RLE_SPRITE *)pdatGraphics[laser000+i].dat;

   Console("Shockwave frames...");
   for(int i=0; i<24; i++) {
      rgprleShock[0][i] = (RLE_SPRITE *)pdatGraphics[ring000+i].dat;
      rgprleShock[1][i] = (RLE_SPRITE *)pdatGraphics[sring000+i].dat;
   }

   Console("Wall frames...");
   for(int i=0; i<128; i++) {
      rgprleOuter[i] = (RLE_SPRITE *)pdatGraphics[owa000+i].dat;
      rgprleMiddle[i] = (RLE_SPRITE *)pdatGraphics[mwa000+i].dat;
   }
   for(int i=0; i<64; i++)
      rgprleInner[i] = (RLE_SPRITE *)pdatGraphics[iwa000+i].dat;

   Console("Star background...");
   pbmStars = (BITMAP *)pdatGraphics[stars].dat;

   return(0);
}

int LoadTitleGraphics(char *sz) {

   pdatTitle = load_datafile(sz);

   if(pdatTitle == NULL)
      return(1);

   Console("Title...");
   memcpy(palTitle, (RGB *)pdatTitle[t_pal].dat, sizeof(PALETTE));
   prleStarTitle = (RLE_SPRITE *)pdatTitle[t_star].dat;
   prleCastleTitle = (RLE_SPRITE *)pdatTitle[t_castle].dat;

   return(0);
}


void InitTimer(void) {

   LOCK_VARIABLE(fps);
   LOCK_VARIABLE(frames);
   LOCK_VARIABLE(target_cycle);
   LOCK_VARIABLE(ticker);
   LOCK_VARIABLE(lastfrm);
   LOCK_VARIABLE(timer);
   LOCK_FUNCTION(cycle_inc);
   LOCK_FUNCTION(timer_inc);

   install_int_ex(cycle_inc, BPS_TO_TIMER(kFrameRate));
   install_int_ex(timer_inc, BPS_TO_TIMER(kTimerRate));

   actual_cycle = target_cycle = 0;

   frames = 0;
}


void Init(void) {

   allegro_init();
   install_timer();
   install_mouse();
   install_keyboard();

   set_color_depth(8);
   text_mode(-1);
   set_mouse_speed(1, 1);

   if(fPageFlipping)
      //set_gfx_mode(GFX_AUTODETECT, 640, 480, 640, 960);
	  // TODO doesn't work
      set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
   else
      set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0);

   Console("Star Castle 0.5");

   Console("Loading graphics...");
   LoadGraphics("data.dat");

   Console("Loading title...");
   LoadTitleGraphics("title.dat");

   Console("Init colors...");
   InitColors();

   Console("Init screen...");
   InitScreen();

   Console("Init timer...");
   InitTimer();
}

