
// $Id: player.cc,v 1.3 2004-06-24 01:01:42 bernard Exp $

#include "player.h"
#include "input.h"
#include "vector.h"
#include "matrix.h"
#include "param.h"
#include "shot.h"
#include "shock.h"
#include "exp.h"
#include "score.h"
#include "sparks.h"

ActorList<Player> alPlayer;

Player::Player(const Vector &v, int d) : Actor((int)v.x, (int)v.y, rgprlePlayer) {
   vPos = v;
   vVel = Vector(0, 0, 0);
   nDir = d;
   nShotDel = 0;
   nThrustFrm = 0;
   nShotFrm = 14;  // FIX THIS make a param
   fFlags |= ACT_SPH;
   nRadius = nWidth/4;

   nXPos = (int)vPos.x-nWidth/2;
   nYPos = (int)vPos.y-nHeight/2;

   nFrame = (Angle2Frame(nDir)/2) * 16 + nShotFrm/2 + nThrustFrm/2;
}

void Player::Action(void) {

   // player hit
   if(fFlags & ACT_HIT) {
      fFlags &= ~ACT_HIT;
      alExplosion.Insert(new Explosion(vPos, vVel/4, EXP_LARGE|EXP_ORANGE));
      alShockWave.Insert(new ShockWave(vPos, vVel/4, SHK_SMALL));
      alScore.First()->DecLives();

      BITMAP *pbm = create_bitmap(nWidth, nHeight);
      clear(pbm);
      draw_rle_sprite(pbm, rgprleFrames[nFrame], 0, 0);
      alSparks.Insert(new Sparks(pbm, 1, Vector(nXPos, nYPos, 0), vVel/3, 0.5, 2.5, 30, 120, 0));
      destroy_bitmap(pbm);

      fFlags |= ACT_DEL;
   }

   if(fLeftTurn) {
      nDir -= nPlayerTurnSpd;
   }

   if(fRightTurn) {
      nDir += nPlayerTurnSpd;
   }

   nDir &= 0xfff;

   if(fThrust) {
      nThrustFrm++;
      if(nThrustFrm > 14)
         nThrustFrm = 14;

      Matrix m;
      m.RotateZ(nDir);

      vVel += m * Vector(1.0, 0.0, 0.0) * rPlayerAcc;
   }
   else {
      if(nThrustFrm > 0)
         nThrustFrm--;
   }

   // bounce off wall area

   Vector vDelta = vPos - Vector(SCREEN_W/2, SCREEN_H/2, 0);

   if(vDelta*vDelta < 120*120) {

      Vector vN = ~vDelta;
      Vector vL = ~(-vVel);

      vVel = (vN*2.0*(vN*vL) - vL) * sqrt(vVel*vVel);

      vPos = Vector(SCREEN_W/2, SCREEN_H/2, 0) + ~vDelta*120;
   }

   vVel += ~(-vVel)*rPlayerFriction;

   // limit velocity
   if(vVel*vVel > rPlayerMaxSpd*rPlayerMaxSpd)
      vVel = ~vVel * rPlayerMaxSpd;

   vPos += vVel;

   // wrap around screen

   if(vPos.x < 0)
      vPos.x = SCREEN_W-1;

   if(vPos.x > SCREEN_W-1)
      vPos.x = 0;

   if(vPos.y < 0)
      vPos.y = SCREEN_H-1;

   if(vPos.y > SCREEN_H-1)
      vPos.y = 0;

   if(nShotFrm < 14)
      nShotFrm++;

   if(nShotDel > 0)
      nShotDel--;

   if(fShoot && nShotDel == 0 && alShot.Count() < nMaxShots) {
      Matrix m;
      m.RotateZ(nDir&~0x3f);
      Vector v = m * Vector(1.0, 0.0, 0.0);
      alShot.Insert(new Shot(vPos, vVel+v*rShotSpd));
      nShotFrm = 0;
      nShotDel = nPlayerShotRate;
      vVel -= v * rPlayerRecoil;
   }

   nXPos = (int)vPos.x-nWidth/2;
   nYPos = (int)vPos.y-nHeight/2;

   nFrame = (Angle2Frame(nDir)/2) * 16 + nShotFrm/2 + nThrustFrm/2;
}

void Player::Erase(int nPage) {

   blit(pbmBackground, pbmPage[nPage], rgrtDirty[nPage].sx, rgrtDirty[nPage].sy, rgrtDirty[nPage].sx, rgrtDirty[nPage].sy, nWidth, nHeight);
}

void Player::Draw(int nPage) {

   draw_rle_sprite(pbmPage[nPage], rgprleFrames[nFrame], nXPos, nYPos); 

//circle(pbmPage[nPage], nXPos+nWidth/2, nYPos+nHeight/2, nRadius-1, nWhite);
//rect(pbmPage[nPage], nXPos, nYPos, nXPos+nWidth-1, nYPos+nHeight-1, nWhite);

   rgrtDirty[nPage].sx = nXPos; rgrtDirty[nPage].sy = nYPos;
   rgrtDirty[nPage].ex = nXPos+nWidth; rgrtDirty[nPage].ey = nYPos+nHeight;

/*
line(pbmPage[nPage], nXPos+nWidth/2, nYPos+nHeight/2, (int)(vPos.x+vVel.x*3), (int)(vPos.y+vVel.y*3), nRed);

Matrix m;
m.RotateZ(nDir);
Vector v = m * Vector(1.0, 0.0, 0.0) * 30.0;
line(pbmPage[nPage], nXPos+nWidth/2, nYPos+nHeight/2, (int)(vPos.x+v.x), (int)(vPos.y+v.y), nYellow);

textprintf(pbmPage[nPage], font, nXPos, nYPos, nGreen, "%2d", ((63-nDir/64)-15)&0x3f);
textprintf(pbmPage[nPage], font, nXPos, nYPos+8, nYellow, "%4d", nDir);
textprintf(pbmPage[nPage], font, nXPos, nYPos+16, nBlue, "%8.3f", vPos.x);
textprintf(pbmPage[nPage], font, nXPos, nYPos+16+8, nBlue, "%8.3f", vPos.y);
textprintf(pbmPage[nPage], font, nXPos, nYPos+32, nRed, "%8.3f", vVel.x);
textprintf(pbmPage[nPage], font, nXPos, nYPos+32+8, nRed, "%8.3f", vVel.y);
*/


}

