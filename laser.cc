
// $Id: laser.cc,v 1.2 2002-01-20 21:20:13 bernard Exp $

#include "laser.h"
#include "vector.h"
#include "matrix.h"
#include "param.h"
#include "player.h"
#include "bomb.h"

ActorList<Laser> alLaser;

Laser::Laser(int nA) : Actor(0, 0, rgprleLaser) {

   nAngle = nA;
   nAge = 0;
   nFrame = (Angle2Frame(nAngle)&0x1f) * 5 + nAge/3;

   int dx = (int)(Cos[nAngle&~0x3f]*nWidth*3/4);
   int dy = (int)(Sin[nAngle&~0x3f]*nHeight*3/4);

   int x = SCREEN_W/2-nWidth/2 + dx;
   int y = SCREEN_H/2-nHeight/2 + dy;

   // get laser section positions
   for(int i=0; i<4; i++) {
      rgnX[i] = x;
      rgnY[i] = y;
      x += dx;
      y += dy;
   }

   vDir = ~Vector(dx, dy, 0);
   vPerp = ~Vector(-dy, dx, 0);
}

// returns true if point vP is on the normal (vN) side of the plane defined
// by rD and vN
int InPlane(float rD, const Vector &vN, const Vector &vP) {

   float d = rD + vP*vN;

   return(d > 0.0);
}

// returns true if point vP is withing the zone bounded by
// three planes defining the laser kill zone
int Laser::LaserHit(const Vector &vP) {

   Vector vN = vDir;
   float rD = -vN*Vector(SCREEN_W/2, SCREEN_H/2, 0);

   if(InPlane(rD, vN, vP)) {

      vN = vPerp;
      rD = -vN*(-vPerp*30+Vector(SCREEN_W/2, SCREEN_H/2, 0));

      if(InPlane(rD, vN, vP)) {

         vN = -vPerp;
         rD = -vN*(vPerp*30+Vector(SCREEN_W/2, SCREEN_H/2, 0));

         if(InPlane(rD, vN, vP)) {

            return(1);
         }
      }
   }

   return(0);
}

void Laser::Action(void) {

   nAge++;
   if(nAge == 15) {
      fFlags |= ACT_DEL;
      return;
   }

   // check collisions when laser has reached full size
   if(nAge == 7) {

      // kill player if we hit
      Player *pPlayer = alPlayer.First();
      if(LaserHit(pPlayer->Pos())) {
         pPlayer->Collision(this);
         pPlayer->Accelerate(vDir*2);
      }

      // kill any homing bombs as a bonus!
      Bomb *pBomb = alBomb.First();
      while(pBomb != alBomb.Head()) {

         if(LaserHit(pBomb->Pos()))
            pBomb->Collision(this);

         pBomb = alBomb.Next();
      }
   }

   // only 32 laser frame hence the &0x1f clip
   nFrame = (Angle2Frame(nAngle)&0x1f) * 5 + nAge/3;
}

void Laser::Erase(int nPage) {

   for(int i=0; i<4; i++)
      blit(pbmBackground, pbmPage[nPage], rgrgrtClean[i][nPage].sx, rgrgrtClean[i][nPage].sy, rgrgrtClean[i][nPage].sx, rgrgrtClean[i][nPage].sy, nWidth, nHeight);
}

void Laser::Draw(int nPage) {

   for(int i=0; i<4; i++) {
      draw_rle_sprite(pbmPage[nPage], rgprleFrames[nFrame], rgnX[i], rgnY[i]);
//textprintf(pbmPage[nPage], font, rgnX[i], rgnY[i], nGreen, "%4d", nAngle);
//textprintf(pbmPage[nPage], font, rgnX[i], rgnY[i]+8, nGreen, "%4d", nFrame);
      rgrgrtClean[i][nPage].sx = rgnX[i]; rgrgrtClean[i][nPage].sy = rgnY[i];
      rgrgrtClean[i][nPage].ex = rgnX[i]+nWidth; rgrgrtClean[i][nPage].ey = rgnY[i]+nHeight;
   }

//line(pbmPage[nPage], SCREEN_W/2, SCREEN_H/2, SCREEN_W/2+(int)(vDir.x*64), SCREEN_H/2+(int)(vDir.y*64), nRed);
//line(pbmPage[nPage], SCREEN_W/2, SCREEN_H/2, SCREEN_W/2+(int)(vPerp.x*64), SCREEN_H/2+(int)(vPerp.y*64), nGreen);
//line(pbmPage[nPage], SCREEN_W/2+(int)(vPerp.x*30), SCREEN_H/2+(int)(vPerp.y*30), SCREEN_W/2+(int)(vPerp.x*30+vDir.x*64), SCREEN_H/2+(int)(vPerp.y*30+vDir.y*64), nYellow);

}

