
// $Id: bomb.cc,v 1.2 2002-01-20 21:20:13 bernard Exp $

#include "vector.h"
#include "matrix.h"
#include "param.h"
#include "bomb.h"
#include "player.h"
#include "exp.h"
#include "sparks.h"

ActorList<Bomb> alBomb;


Bomb::Bomb(int nA) : Actor(0, 0, rgprleBomb) {

   vPos = Vector(SCREEN_W/2, SCREEN_H/2, 0);
   nAnimRate = 0;
   nSearchDel = 200;
   vVel = Vector(Cos[nA], Sin[nA], 0) * 0.5;

   fFlags |= ACT_SPH;

   nXPos = (int)vPos.x-nWidth/2;
   nYPos = (int)vPos.y-nHeight/2;
}


void Bomb::Action(void) {

   if(fFlags & ACT_HIT) {
      fFlags |= ACT_DEL;
      alExplosion.Insert(new Explosion(vPos, vVel/2, EXP_SMALL|EXP_GREEN));

      BITMAP *pbm = create_bitmap(nWidth, nHeight);
      clear(pbm);
      draw_rle_sprite(pbm, rgprleFrames[nFrame], 0, 0);
      alSparks.Insert(new Sparks(pbm, 1, Vector(nXPos, nYPos, 0), vVel/2, 0.1, 2, 25, 75, 0));
      destroy_bitmap(pbm);

      return;
   }

// have a state thing here

   if(nSearchDel > 0) {
      nSearchDel--;
      if(nSearchDel == 0) {
         nSearchDel = nBombSearchRate;
         //Vector vAcc = ~(pPlayer->Pos() - vPos) * fBombSpd;
         Vector vAcc = ~(alPlayer.First()->Pos() - vPos) * fBombSpd;
         vVel += vAcc/2;

         vVel = ~vVel * fBombSpd;

      }
   }

   // die if off screen
   if(vPos.x < 0 || vPos.x > SCREEN_W-1 || vPos.y < 0 || vPos.y > SCREEN_H-1) {
      fFlags |= ACT_DEL;
      return;
   }

   vPos += vVel;

   nXPos = (int)vPos.x-nWidth/2;
   nYPos = (int)vPos.y-nHeight/2;

   nAnimRate++;
   nAnimRate &= 0x1f;

   nFrame = nAnimRate/4;
}

void Bomb::Erase(int nPage) {

   blit(pbmBackground, pbmPage[nPage], rgrtDirty[nPage].sx, rgrtDirty[nPage].sy, rgrtDirty[nPage].sx, rgrtDirty[nPage].sy, nWidth, nHeight);
}

void Bomb::Draw(int nPage) {

   draw_rle_sprite(pbmPage[nPage], rgprleFrames[nFrame], nXPos, nYPos);

//rect(pbmPage[nPage], nXPos, nYPos, nXPos+nWidth-1, nYPos+nHeight-1, nWhite);
//circle(pbmPage[nPage], nXPos+nWidth/2, nYPos+nHeight/2, nRadius-1, nWhite);

   rgrtDirty[nPage].sx = nXPos; rgrtDirty[nPage].sy = nYPos;
   rgrtDirty[nPage].ex = nXPos+nWidth; rgrtDirty[nPage].ey = nYPos+nHeight;
}

