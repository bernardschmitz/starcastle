
// $Id: shot.cc,v 1.2 2002-01-20 21:20:13 bernard Exp $

#include "vector.h"
#include "matrix.h"
#include "param.h"
#include "shot.h"
#include "exp.h"
#include "score.h"

ActorList<Shot> alShot;


Shot::Shot(const Vector &vP, const Vector &vV) : Actor(0, 0, rgprleShot) {
   vPos = vP;
   vVel = vV;
   nLife = nShotLife;
   nAnimRate = 0;

   fFlags |= ACT_SPH;

   nXPos = (int)vPos.x-nWidth/2;
   nYPos = (int)vPos.y-nHeight/2;
                   
   alScore.First()->IncFired();
}

void Shot::Collision(Actor *pact) {

   fFlags |= ACT_HIT;
   pact = pact;

   alScore.First()->IncHits();
}


void Shot::Action(void) {

   if(fFlags & ACT_HIT) {
      fFlags |= ACT_DEL;
      alExplosion.Insert(new Explosion(vPos, vVel/6, EXP_SMALL|EXP_ORANGE));
      return;
   }

   nLife--;
   if(nLife == 0) {
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

   // FIX THIS all there animation params should be consts
   nAnimRate++;
   nAnimRate &= 0x1f;

   nFrame = nAnimRate/4;
}

void Shot::Erase(int nPage) {

   blit(pbmBackground, pbmPage[nPage], rgrtDirty[nPage].sx, rgrtDirty[nPage].sy, rgrtDirty[nPage].sx, rgrtDirty[nPage].sy, nWidth, nHeight);
}

void Shot::Draw(int nPage) {

   draw_rle_sprite(pbmPage[nPage], rgprleFrames[nFrame], nXPos, nYPos);

   rgrtDirty[nPage].sx = nXPos; rgrtDirty[nPage].sy = nYPos;
   rgrtDirty[nPage].ex = nXPos+nWidth; rgrtDirty[nPage].ey = nYPos+nHeight;

//circle(pbmPage[nPage], nXPos+nWidth/2, nYPos+nHeight/2, nRadius-1, nWhite);
}

