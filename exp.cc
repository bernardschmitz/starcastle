
// $Id: exp.cc,v 1.2 2002-01-20 21:20:13 bernard Exp $

#include "vector.h"
#include "matrix.h"
#include "param.h"
#include "exp.h"
#include "random.h"
#include "sparks.h"

ActorList<Explosion> alExplosion;


Explosion::Explosion(const Vector &vP, const Vector &vV, int fType) : Actor() {

   // work out type of explosion
   if(fType & EXP_RAND)
      if(Random(10) < 5) {
         int t = Random(4);
         rgprleFrames = rgrgprleSmallExp[t];
         if(t > 2)
            alSparks.Insert(new Sparks(nSparksSmall, vP, vV, fSparksMinSpd, fSparksMaxSpd, nSparksMinAge, nSparksMaxAge, nGreen, 192, 255));
         else
            alSparks.Insert(new Sparks(nSparksSmall, vP, vV, fSparksMinSpd, fSparksMaxSpd, nSparksMinAge, nSparksMaxAge, nYellow, 192, 255));
      }
      else {
         int t = Random(4);
         rgprleFrames = rgrgprleExplosions[t];
         if(t > 2)
            alSparks.Insert(new Sparks(nSparksLarge, vP, vV, fSparksMinSpd, fSparksMaxSpd, nSparksMinAge, nSparksMaxAge, nGreen, 192, 255));
         else
            alSparks.Insert(new Sparks(nSparksLarge, vP, vV, fSparksMinSpd, fSparksMaxSpd, nSparksMinAge, nSparksMaxAge, nYellow, 192, 255));
      }
   else
      if(fType & EXP_GREEN)
         if(fType & EXP_SMALL) {
            rgprleFrames = rgrgprleSmallExp[2+Random(2)];
            alSparks.Insert(new Sparks(nSparksSmall, vP, vV, fSparksMinSpd, fSparksMaxSpd, nSparksMinAge, nSparksMaxAge, nGreen, 192, 255));
         }
         else {
            rgprleFrames = rgrgprleExplosions[2+Random(2)];
            alSparks.Insert(new Sparks(nSparksLarge, vP, vV, fSparksMinSpd, fSparksMaxSpd, nSparksMinAge, nSparksMaxAge, nGreen, 192, 255));
         }
      else
         if(fType & EXP_SMALL) {
            rgprleFrames = rgrgprleSmallExp[Random(2)];
            alSparks.Insert(new Sparks(nSparksSmall, vP, vV, fSparksMinSpd, fSparksMaxSpd, nSparksMinAge, nSparksMaxAge, nYellow, 192, 255));
         }
         else {
            rgprleFrames = rgrgprleExplosions[Random(2)];
            alSparks.Insert(new Sparks(nSparksLarge, vP, vV, fSparksMinSpd, fSparksMaxSpd, nSparksMinAge, nSparksMaxAge, nYellow, 192, 255));
         }

   nXPos = (int)vP.x-rgprleFrames[0]->w/2;
   nYPos = (int)vP.y-rgprleFrames[0]->h/2;

   nWidth = rgprleFrames[0]->w;
   nHeight = rgprleFrames[0]->h;

   vPos = vP;
   vVel = vV;
   nAge = 0;
}


void Explosion::Action(void) {

   nAge++;
   if(nAge >= 60) {
      fFlags |= ACT_DEL;
      return;
   }

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

   nXPos = (int)vPos.x-nWidth/2;
   nYPos = (int)vPos.y-nHeight/2;

   nFrame = nAge/2;
}

void Explosion::Erase(int nPage) {

   blit(pbmBackground, pbmPage[nPage], rgrtDirty[nPage].sx, rgrtDirty[nPage].sy, rgrtDirty[nPage].sx, rgrtDirty[nPage].sy, nWidth, nHeight);
}

void Explosion::Draw(int nPage) {

   draw_trans_rle_sprite(pbmPage[nPage], rgprleFrames[nFrame], nXPos, nYPos);
   rgrtDirty[nPage].sx = nXPos; rgrtDirty[nPage].sy = nYPos;
   rgrtDirty[nPage].ex = nXPos+nWidth; rgrtDirty[nPage].ey = nYPos+nHeight;
}

