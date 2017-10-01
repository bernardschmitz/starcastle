
#include "vector.h"
#include "matrix.h"
#include "param.h"
#include "exp.h"
#include "middle.h"
#include "score.h"

ActorList<Middle> alMiddle;


Middle::Middle(int a, int da) : Actor(0, 0, rgprleMiddle) {

   nAngle = a;
   nDa = da;
   int x = (int)(Cos[nAngle]*nMiddleRadius);
   int y = (int)(Sin[nAngle]*nMiddleRadius);
   vPos = Vector(SCREEN_W/2+x, SCREEN_H/2+y, 0);
   nXPos = (int)vPos.x-nWidth/2;
   nYPos = (int)vPos.y-nHeight/2;
   nDamage = 0;
   nFrame = nDamage + ((15+Angle2Frame(nAngle))&0x3f);
   fFlags |= ACT_SPH;
}


void Middle::Action(void) {

   if(fFlags & ACT_HIT) {
      fFlags &= ~ACT_HIT;
      // takes two hits
      if(nDamage == 64) {
         alExplosion.Insert(new Explosion(vPos, Vector(0,0,0), EXP_GREEN|EXP_LARGE));
         fFlags |= ACT_DEL;
         alScore.First()->AddPoints(nMiddlePoints);
      }
      else {
         alExplosion.Insert(new Explosion(vPos, Vector(0,0,0), EXP_GREEN|EXP_SMALL));
         nDamage = 64;
      }
      return;
   }

   nAngle += nDa;
   nAngle &= 0xfff;

   int x = (int)(Cos[nAngle]*nMiddleRadius);
   int y = (int)(Sin[nAngle]*nMiddleRadius);
   vPos = Vector(SCREEN_W/2+x, SCREEN_H/2+y, 0);

   nXPos = (int)vPos.x-nWidth/2;
   nYPos = (int)vPos.y-nHeight/2;

   //nFrame = nDamage + ((15+((63-(nAngle/64))-15))&0x3f);
   nFrame = nDamage + ((15+Angle2Frame(nAngle))&0x3f);
}

void Middle::Erase(int nPage) {

   blit(pbmBackground, pbmPage[nPage], rgrtDirty[nPage].sx, rgrtDirty[nPage].sy, rgrtDirty[nPage].sx, rgrtDirty[nPage].sy, nWidth, nHeight);
}

void Middle::Draw(int nPage) {

   draw_rle_sprite(pbmPage[nPage], rgprleFrames[nFrame], nXPos, nYPos);

//rect(pbmPage[nPage], nXPos, nYPos, nXPos+nWidth-1, nYPos+nHeight-1, nWhite);
//circle(pbmPage[nPage], nXPos+nWidth/2, nYPos+nHeight/2, 16, nWhite);

//textprintf(pbmPage[nPage], font, nXPos, nYPos, nGreen, "%4d", nFrame);
//textprintf(pbmPage[nPage], font, nXPos, nYPos+8, nYellow, "%4d", nDamage);

   rgrtDirty[nPage].sx = nXPos; rgrtDirty[nPage].sy = nYPos;
   rgrtDirty[nPage].ex = nXPos+nWidth; rgrtDirty[nPage].ey = nYPos+nHeight;
}

