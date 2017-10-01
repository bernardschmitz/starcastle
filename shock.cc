
// $Id: shock.cc,v 1.2 2002-01-20 21:20:13 bernard Exp $

#include "vector.h"
#include "matrix.h"
#include "param.h"
#include "shock.h"

ActorList<ShockWave> alShockWave;


ShockWave::ShockWave(const Vector &vP, const Vector &vV, int s) :
                 Actor((int)vP.x-rgprleShock[s][0]->w/2, (int)vP.y-rgprleShock[s][0]->h/2,
                               rgprleShock[s]) {
                    vPos = vP;
                    vVel = vV;
               }

void ShockWave::Action(void) {

   nFrame++;
   if(nFrame >= 23) {
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
}

void ShockWave::Erase(int nPage) {

   blit(pbmBackground, pbmPage[nPage], rgrtDirty[nPage].sx, rgrtDirty[nPage].sy, rgrtDirty[nPage].sx, rgrtDirty[nPage].sy, nWidth, nHeight);
}

void ShockWave::Draw(int nPage) {

   draw_trans_rle_sprite(pbmPage[nPage], rgprleFrames[nFrame], nXPos, nYPos);
   rgrtDirty[nPage].sx = nXPos; rgrtDirty[nPage].sy = nYPos;
   rgrtDirty[nPage].ex = nXPos+nWidth; rgrtDirty[nPage].ey = nYPos+nHeight;
}

