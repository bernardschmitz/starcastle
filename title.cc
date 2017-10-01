
// $Id: title.cc,v 1.3 2004-06-24 01:53:44 bernard Exp $

#include <stdio.h>
#include <time.h>
#include <allegro.h>

#include "init.h"
#include "input.h"
#include "random.h"
#include "shock.h"
#include "bomb.h"
#include "sparks.h"
#include "vector.h"
#include "actor.h"
#include "matrix.h"
#include "message.h"

class TitleThing : public Actor {
   private:
      Vector vPos, vVel;
      int nAngle, nDir;
      int nTrans;
      int nW, nH;
      BITMAP *pbmFrame;
   public:
      TitleThing(const Vector &, int, int, int, RLE_SPRITE **);

      ~TitleThing() { destroy_bitmap(pbmFrame); }

      Vector Pos(void) { return(vPos); }

      void Action(void);

      void Erase(int);
      void Draw(int);
};

ActorList<TitleThing> alTitleThing;


TitleThing::TitleThing(const Vector &vP, int nA, int nD, int nT, RLE_SPRITE **pprle) : Actor(0, 0, pprle) {

   pbmFrame = create_bitmap(nWidth, nHeight);
   clear(pbmFrame);
   draw_rle_sprite(pbmFrame, rgprleFrames[nFrame], 0, 0);

   nTrans = nT;

   nDir = nD;
   nAngle = nA;

   vPos = vP;
   vVel = Vector(0, 0, 0);

   fFlags |= ACT_SPH;

   nXPos = (int)vPos.x-nWidth/2;
   nYPos = (int)vPos.y-nHeight/2;
}


void TitleThing::Action(void) {

   nAngle += nDir;
   nAngle &= 0xfff;

   vVel = Vector(Cos[nAngle], Sin[nAngle], 0);
   Vector vP = vPos + vVel * 80.0;

   nW = nWidth/2 + int((1.0+Sin[nAngle])/4.0 * float(nWidth));
   nH = nHeight/2 + int((1.0+Cos[nAngle])/4.0 * float(nHeight));

   nXPos = (int)vP.x-nW/2;
   nYPos = (int)vP.y-nH/2;

   nFrame = 0;
}

void TitleThing::Erase(int nPage) {

   blit(pbmBackground, pbmPage[nPage], rgrtDirty[nPage].sx, rgrtDirty[nPage].sy, rgrtDirty[nPage].sx, rgrtDirty[nPage].sy, nWidth, nHeight);
}

void TitleThing::Draw(int nPage) {

   if(nTrans) {
      draw_trans_rle_sprite(pbmPage[nPage], rgprleFrames[nFrame], nXPos, nYPos);
      rgrtDirty[nPage].sx = nXPos; rgrtDirty[nPage].sy = nYPos;
      rgrtDirty[nPage].ex = nXPos+nWidth; rgrtDirty[nPage].ey = nYPos+nHeight;
   }
   else {
      stretch_sprite(pbmPage[nPage], pbmFrame, nXPos, nYPos, nW, nH);
      rgrtDirty[nPage].sx = nXPos; rgrtDirty[nPage].sy = nYPos;
      rgrtDirty[nPage].ex = nXPos+nW; rgrtDirty[nPage].ey = nYPos+nH;
   }
}


void NextText(void) {

   static char *rgszText[] = {
   "Instructions",
   "Left and right arrow rotates ship", 
   "Up arrow thrusts ship",
   "Left control fires ships gun",
   "Escape quits",
   " ",
   "Press control to begin",

   "High Scores",
   "9999999999 B   100% 00:01:00",
   "0000000000     000% 00:00:00",
   "0000000000     000% 00:00:00",
   "0000000000     000% 00:00:00",
   "0000000000     000% 00:00:00",
   "0000000000     000% 00:00:00",
   "0000000000     000% 00:00:00",
   "0000000000     000% 00:00:00",
   "0000000000     000% 00:00:00",
   "0000000000     000% 00:00:00",
   };
   static int rgnPageLen[] = { 7, 17 };


   static int nTextPage = 0;
   static int nNext = 0;
   static int nDelay = 15;
   static int nRow = 80;

   nDelay--;
   if(nDelay > 0)
      return;

   nDelay = 15;

   alMessage.Insert(new Message(SCREEN_W/2, nRow, rgszText[nNext], nGreen, 30, 240, 30, rgpfntFont[3]));

   nRow += 35;
   nNext++;
   if(nNext == rgnPageLen[nTextPage]) {
      nTextPage++;
      if(nTextPage == 2) {
         nTextPage = 0;
         nNext = 0;
      }
      nRow = 80;
      nDelay = 400;
   }

}

void TitleRender(void) {

   alMessage.Erase(nPage);
   alTitleThing.Erase(nPage);

blit(pbmBackground, pbmPage[nPage], 0, 20, 0, 20, 80, 20);

   alTitleThing.Draw(nPage);
   alMessage.Draw(nPage);

textprintf(pbmPage[nPage], rgpfntFont[0], 0, 20, nYellow, "fps %3d", fps);

   if(fPageFlipping)
      scroll_screen(0, nPage*SCREEN_H);
   else
      blit(pbmPage[nPage], screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

   if(nPage == 0)
      nPage = 1;
   else
      nPage = 0;

   frames++;
}

int TitleLoop(void) {


   if(alTitleThing.Count() == 0) {
      alTitleThing.Insert(new TitleThing(Vector(SCREEN_W/2, 120, 0), 0, 16, 0, &prleStarTitle));
      alTitleThing.Insert(new TitleThing(Vector(SCREEN_W/2, SCREEN_H-120, 0), 0, -16, 0, &prleCastleTitle));
      //alTitleThing.Insert(new TitleThing(Vector(SCREEN_W/2, 120, 0), 0, -16, 1, &prleStarTitle));
      //alTitleThing.Insert(new TitleThing(Vector(SCREEN_W/2, SCREEN_H-120, 0), 0, 16, 1, &prleCastleTitle));
   }

   NextText();

   alTitleThing.Action();
   alMessage.Action();

   actual_cycle++;

   return(0);
}

int Title(void) {

   set_palette(palTitle);

   clear(pbmPage[0]);
   clear(pbmPage[1]);

   blit(pbmStars, pbmPage[0], 0, 0, 0, 0, SCREEN_W, SCREEN_H);

   blit(pbmPage[0], pbmBackground, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
   blit(pbmBackground, pbmPage[1], 0, 0, 0, 0, SCREEN_W, SCREEN_H);

   while(fQuit == 0 && fShoot == 0) {

      TitleRender();

      ProcessInput();

      while(actual_cycle >= target_cycle)
         ;

      while(target_cycle > actual_cycle)
         TitleLoop();
   }

   alMessage.Clear();
   alTitleThing.Clear();

   return(fQuit);
}


