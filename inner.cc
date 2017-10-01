
// $Id: inner.cc,v 1.2 2002-01-20 21:20:13 bernard Exp $

#include "vector.h"
#include "matrix.h"
#include "param.h"
#include "exp.h"
#include "inner.h"
#include "score.h"

ActorList<Inner> alInner;


Inner::Inner(int a, int da) : Actor(0, 0, rgprleInner) {

   nAngle = a;
   nDa = da;
   int x = (int)(Cos[nAngle]*nInnerRadius);
   int y = (int)(Sin[nAngle]*nInnerRadius);
   vPos = Vector(SCREEN_W/2+x, SCREEN_H/2+y, 0);
   nXPos = (int)vPos.x-nWidth/2;
   nYPos = (int)vPos.y-nHeight/2;
   nDamage = 0;
   nFrame = nDamage + (((15+Angle2Frame(nAngle))&0x3f)&0x1f);
   fFlags |= ACT_SPH;
}


void Inner::Action(void) {

   // wall hit
   if(fFlags & ACT_HIT) {
      fFlags &= ~ACT_HIT;

      alExplosion.Insert(new Explosion(vPos, Vector(0,0,0), EXP_GREEN|EXP_SMALL));

      // takes 2 hits
      if(nDamage == 32) {
         fFlags |= ACT_DEL;
         alScore.First()->AddPoints(nInnerPoints);
      }
      else
         nDamage = 32;
      return;
   }

   nAngle += nDa;
   nAngle &= 0xfff;

   int x = (int)(Cos[nAngle]*nInnerRadius);
   int y = (int)(Sin[nAngle]*nInnerRadius);
   vPos = Vector(SCREEN_W/2+x, SCREEN_H/2+y, 0);

   nXPos = (int)vPos.x-nWidth/2;
   nYPos = (int)vPos.y-nHeight/2;

   // only 32 frames, hence the &0x1f
   nFrame = nDamage + (((15+Angle2Frame(nAngle))&0x3f)&0x1f);
}

void Inner::Erase(int nPage) {

   blit(pbmBackground, pbmPage[nPage], rgrtDirty[nPage].sx, rgrtDirty[nPage].sy, rgrtDirty[nPage].sx, rgrtDirty[nPage].sy, nWidth, nHeight);
}

void Inner::Draw(int nPage) {

   draw_rle_sprite(pbmPage[nPage], rgprleFrames[nFrame], nXPos, nYPos);

//rect(pbmPage[nPage], nXPos, nYPos, nXPos+nWidth-1, nYPos+nHeight-1, nWhite);
//circle(pbmPage[nPage], nXPos+nWidth/2, nYPos+nHeight/2, nRadius, nWhite);

//textprintf(pbmPage[nPage], font, nXPos, nYPos, nGreen, "%4d", nFrame);
//textprintf(pbmPage[nPage], font, nXPos, nYPos+8, nYellow, "%4d", nDamage);

   rgrtDirty[nPage].sx = nXPos; rgrtDirty[nPage].sy = nYPos;
   rgrtDirty[nPage].ex = nXPos+nWidth; rgrtDirty[nPage].ey = nYPos+nHeight;
}

