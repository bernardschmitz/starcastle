
// $Id: castle.cc,v 1.2 2002-01-20 21:20:13 bernard Exp $

#include <math.h>

#include "castle.h"
#include "vector.h"
#include "matrix.h"
#include "param.h"
#include "bomb.h"
#include "laser.h"
#include "shock.h"
#include "exp.h"
#include "player.h"
#include "outer.h"
#include "middle.h"
#include "inner.h"
#include "score.h"
#include "sparks.h"



ActorList<Castle> alCastle;


Castle::Castle(int nA) : Actor(0, 0, rgprleCastle) {

   nAngle = nA;
   nTurn = 0;
   vPos = Vector(SCREEN_W/2, SCREEN_H/2, 0);

   nXPos = (int)vPos.x - nWidth/2;
   nYPos = (int)vPos.y - nHeight/2;

   fFlags |= ACT_SPH;
   nRadius = nWidth/4;

   nFrame = 15 + Angle2Frame(nAngle) * 16;

   nState = TARGET;
}

// Returns 1 if there will be a gap through the walls in direction nA
// in 22 game cycles.  Takes into account the speed the walls are rotating.
// 22 game cycles is the time the castle firing animation displays the
// laser when animating 3x slower
// FIX THIS 22 should be a const

int IsGap(int nA) {

   nA &= ~0x3f;  // round down direction angle to multiple of 64

   int fGap = 1;  // assume there is a gap

   // a gap exists if the absolute value of the difference of a wall section
   // position angle and the laser direction angle is greater than 250
   // need to take into account the speed of the wall too

   Outer *pout = alOuter.First();

   while(fGap && pout != alOuter.Head()) {
      fGap &= abs(AngleDiff(pout->Angle()+pout->Speed()*22, nA)) > 200;
      pout = alOuter.Next();
   }

   if(fGap) {

      Middle *pmid = alMiddle.First();

      while(fGap && pmid != alMiddle.Head()) {
         fGap &= abs(AngleDiff(pmid->Angle()+pmid->Speed()*22, nA)) > 200;
         pmid = alMiddle.Next();
      }

      if(fGap) {

         Inner *pinn = alInner.First();

         while(fGap && pinn != alInner.Head()) {
            fGap &= abs(AngleDiff(pinn->Angle()+pinn->Speed()*22, nA)) > 200;
            pinn = alInner.Next();
         }

         return(fGap);
      }
   }

   return(0);
}

void Castle::Action(void) {

   Vector vDelta;
   int nDelta;
   int nShootAnim = 0;

   switch(nState) {

      case TARGET : // target state finds the angle to the player
                    // and begins turning towards it

                    vDelta = alPlayer.First()->Pos() - vPos;
                    nTarget = (int)((atan2(-vDelta.y, vDelta.x) + M_PI) * 4096.0 / (2.0*M_PI));
                    nTarget = 2048 - nTarget;
                    nTarget &= 0xfff;

                    nDelay = nCastleTargetRate;
                    nDelta = AngleDiff(nAngle, nTarget);
                    if(nDelta < 0)
                       nTurn = -nCastleTurnSpd;
                    else
                       nTurn = nCastleTurnSpd;

                    if(nDelta == 0)
                       nTurn = 0;

                    nState = TURN;

                    break;

      case TURN :   // turn state turns toward target angle
                    // if allready at target angle, just do nothing

                    nDelta = AngleDiff(nAngle, nTarget);
                    if(abs(nDelta) < nCastleTurnSpd) {
                       nAngle = nTarget;
                       nTurn = 0;
                    }
                    else
                       nAngle += nTurn;

                    nAngle &= 0xfff;

                    nDelay--;

                    if(nDelay == 0) {
                       // launch some homing bombs
                       if(alBomb.Count() < nMaxBombs)
                          alBomb.Insert(new Bomb(Random(4096)));
                       // if finished turn and the is a gap in the
                       // wall, then shoot.  Maybe we will hit the player?
                       if(nAngle == nTarget) {
                          if(IsGap(nAngle)) {
                             nDelay = 48;
                             nState = SHOOT;
                          }
                          else  // if no gap, then target player again
                             nState = TARGET;
                       }
                       else
                          nState = TARGET;
                    }

                    break;

     case SHOOT :   // shoot state just displays castle shooting animation
                    nDelay--;

                    nShootAnim = nDelay;

                    // finish shooting?  then target player again
                    if(nDelay == 0)
                       nState = TARGET;

                    // put these values into consts
                    // animation reached laser point, fire!
                    if(nDelay == 26)
                       alLaser.Insert(new Laser(nAngle));

                    break;


   }

   // castle hit!
   if(fFlags & ACT_HIT) {
      //fFlags &= ~ACT_HIT;

      // Hack! Sometimes a players bullet can move fast enough to 
      // skip over the walls and hit the castle
      // here we ignore the hit if any wall has 12 segments
      if(alOuter.Count() == 12 || alMiddle.Count() == 12 || alInner.Count() == 12)
         return;

      // delete castle
      fFlags |= ACT_DEL;

      // reward player
      alScore.First()->IncCastle();
      alScore.First()->IncLives();
      alScore.First()->AddPoints(nCastlePoints);
      alScore.First()->AddPoints(alOuter.Count()*nOuterPoints*nWallBonus);
      alScore.First()->AddPoints(alMiddle.Count()*nMiddlePoints*nWallBonus);
      alScore.First()->AddPoints(alInner.Count()*nInnerPoints*nWallBonus);

      // blow up castle
      alShockWave.Insert(new ShockWave(vPos, Vector(0, 0, 0)));
      for(int i=0; i<4; i++)
         alExplosion.Insert(new Explosion(vPos+Vector(4-Random(9), 4-Random(9), 0), Vector(1-Random(3), 1-Random(3), 0), EXP_RAND|EXP_LARGE));

      BITMAP *pbm = create_bitmap(nWidth, nHeight);
      clear(pbm);
      draw_rle_sprite(pbm, rgprleFrames[nFrame], 0, 0);
      alSparks.Insert(new Sparks(pbm, 3, Vector(nXPos, nYPos, 0), Vector(0, 0, 0), 1, 4, 60, 180, 0));
      alSparks.Insert(new Sparks(pbm, 3, Vector(nXPos, nYPos, 0), Vector(0, 0, 0), 3, 5, 30, 60, nWhite));
      destroy_bitmap(pbm);
   }

   //nXPos = (int)vPos.x - nWidth/2;
   //nYPos = (int)vPos.y - nHeight/2;

   nFrame = 15 + Angle2Frame(nAngle) * 16 - nShootAnim/3;
}

void Castle::Erase(int nPage) {

   blit(pbmBackground, pbmPage[nPage], rgrtDirty[nPage].sx, rgrtDirty[nPage].sy, rgrtDirty[nPage].sx, rgrtDirty[nPage].sy, nWidth, nHeight);
}

void Castle::Draw(int nPage) {

   draw_rle_sprite(pbmPage[nPage], rgprleFrames[nFrame], nXPos, nYPos); 
   rgrtDirty[nPage].sx = nXPos; rgrtDirty[nPage].sy = nYPos;
   rgrtDirty[nPage].ex = nXPos+nWidth; rgrtDirty[nPage].ey = nYPos+nHeight;

//circle(pbmPage[nPage], nXPos+nWidth/2, nYPos+nHeight/2, nRadius-1, nWhite);

/*
if(gap)
   textprintf(pbmPage[nPage], font, nXPos, nYPos, nGreen, "GAP");
switch(nState) {
   case TARGET : textprintf(pbmPage[nPage], font, nXPos, nYPos+8, nGreen, "TARGET");
                 break;
   case TURN   : textprintf(pbmPage[nPage], font, nXPos, nYPos+8, nGreen, "TURN");
                 break;
   case SHOOT  : textprintf(pbmPage[nPage], font, nXPos, nYPos+8, nGreen, "SHOOT");
                 break;
}
textprintf(pbmPage[nPage], font, nXPos, nYPos+16, nYellow, "%4d", nAngle);
textprintf(pbmPage[nPage], font, nXPos, nYPos+16+8, nYellow, "%4d", nTarget);
textprintf(pbmPage[nPage], font, nXPos, nYPos+32, nRed, "%4d", nDelay);
*/

}

