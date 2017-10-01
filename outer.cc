
// $Id: outer.cc,v 1.2 2002-01-20 21:20:13 bernard Exp $

#include "vector.h"
#include "matrix.h"
#include "param.h"
#include "exp.h"
#include "outer.h"
#include "middle.h"
#include "inner.h"
#include "score.h"
#include "sparks.h"

ActorList<Outer> alOuter;


Outer::Outer(int a, int da) : Actor(0, 0, rgprleOuter) {

   nAngle = a;
   nDa = da;
   // FIX THIS 100 should be a const, same for other walls
   int x = (int)(Cos[nAngle]*nOuterRadius);
   int y = (int)(Sin[nAngle]*nOuterRadius);
   vPos = Vector(SCREEN_W/2+x, SCREEN_H/2+y, 0);
   nXPos = (int)vPos.x-nWidth/2;
   nYPos = (int)vPos.y-nHeight/2;
   nDamage = 0;
   nFrame = nDamage + ((15+Angle2Frame(nAngle))&0x3f);
   fFlags |= ACT_SPH;
}


void Outer::Action(void) {

   if(fFlags & ACT_HIT) {
      fFlags &= ~ACT_HIT;
      if(nDamage == 64) {
         alExplosion.Insert(new Explosion(vPos, Vector(0,0,0), EXP_GREEN|EXP_LARGE));
         fFlags |= ACT_DEL;
         alScore.First()->AddPoints(nOuterPoints);
/*
         BITMAP *pbm = create_bitmap(nWidth, nHeight);
         clear(pbm);
         draw_rle_sprite(pbm, rgprleFrames[nFrame], 0, 0);
         alSparks.Insert(new Sparks(pbm, 2, Vector(nXPos, nYPos, 0), Vector(-Sin[nAngle], Cos[nAngle], 0)*(nDa*3.14159/2048.0*nOuterRadius), 0.1, 2.5, 25, 75, 0));
         destroy_bitmap(pbm);
*/
      }
      else {
         alExplosion.Insert(new Explosion(vPos, Vector(0,0,0), EXP_GREEN|EXP_SMALL));
         nDamage = 64;
      }
      return;
   }

   nAngle += nDa;
   nAngle &= 0xfff;

   int x = (int)(Cos[nAngle]*nOuterRadius); //100);
   int y = (int)(Sin[nAngle]*nOuterRadius); //100);
   vPos = Vector(SCREEN_W/2+x, SCREEN_H/2+y, 0);

   nXPos = (int)vPos.x-nWidth/2;
   nYPos = (int)vPos.y-nHeight/2;

   //nFrame = nDamage + ((15+((63-(nAngle/64))-15))&0x3f);
   nFrame = nDamage + ((15+Angle2Frame(nAngle))&0x3f);
}

void Outer::Erase(int nPage) {

   blit(pbmBackground, pbmPage[nPage], rgrtDirty[nPage].sx, rgrtDirty[nPage].sy, rgrtDirty[nPage].sx, rgrtDirty[nPage].sy, nWidth, nHeight);
}

void Outer::Draw(int nPage) {

   draw_rle_sprite(pbmPage[nPage], rgprleFrames[nFrame], nXPos, nYPos);

//rect(pbmPage[nPage], nXPos, nYPos, nXPos+nWidth-1, nYPos+nHeight-1, nWhite);
//circle(pbmPage[nPage], nXPos+nWidth/2, nYPos+nHeight/2, nRadius-1, nWhite);

//textprintf(pbmPage[nPage], font, nXPos, nYPos, nGreen, "%4d", nFrame);
//textprintf(pbmPage[nPage], font, nXPos, nYPos+8, nYellow, "%4d", nDamage);

   rgrtDirty[nPage].sx = nXPos; rgrtDirty[nPage].sy = nYPos;
   rgrtDirty[nPage].ex = nXPos+nWidth; rgrtDirty[nPage].ey = nYPos+nHeight;
}

// build three new walls
void InitWalls(void) {

   for(int i=0; i<12; i++) {
      alOuter.Insert(new Outer(i*4095/11, nOuterSpd));
      alMiddle.Insert(new Middle(i*4095/11, nMiddleSpd));
      alInner.Insert(new Inner(i*4095/11, nInnerSpd));
   }
}

// make a new inner wall
void NewInner(int nSpd) {

   // clear inner wall ring
   Inner *pinn = alInner.First();
   while(pinn != alInner.Head()) {
      Inner *pinnTmp = alInner.Next();
      alInner.Remove(pinn);
      pinn = pinnTmp;
   }

   // build 12 shiny new walls
   for(int i=0; i<12; i++)
      alInner.Insert(new Inner(i*4095/11, nSpd));
}

// rotate wall speeds.
// when a wall dies, the next inner wall moves out to replace it
// hence need to replace speed variable too
void RotateWallSpeeds(void) {

   int nTmp = nOuterSpd;
   nOuterSpd = nMiddleSpd;
   nMiddleSpd = nInnerSpd;
   nInnerSpd = nTmp;
}

// check if walls need to be regenerated
void CheckWalls(void) {

   if(alOuter.Count() == 0) {
      RotateWallSpeeds();
      GrowWalls(alMiddle, alOuter);
      GrowWalls(alInner, alMiddle);
      NewInner(nInnerSpd);
   }

   if(alMiddle.Count() == 0) {
      RotateWallSpeeds();
      GrowWalls(alInner, alMiddle);
      NewInner(nInnerSpd);
   }

   if(alInner.Count() == 0)
      NewInner(nInnerSpd);

   SpeedWalls(alOuter, nOuterSpd);
   SpeedWalls(alMiddle, nMiddleSpd);
   SpeedWalls(alInner, nInnerSpd);
}

