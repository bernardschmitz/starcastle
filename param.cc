
// $Id: param.cc,v 1.4 2004-06-24 01:53:44 bernard Exp $

#include "param.h"

int kFrameRate = 60;
int kTimerRate = 600;

int nDifficultyRate = kTimerRate * 30;

int nPlayerTurnSpd = 64;
float rPlayerAcc = 0.2;
float rPlayerFriction = 0.04;
float rPlayerMaxSpd = 5.0; 
float rPlayerRecoil = 0.4;
int nPlayerShotRate= 10;
int nMaxShots = 3;

int nShotLife = 40;
float rShotSpd = 10.0;

float fBombSpd;
int nBombSearchRate;

int nOuterPoints = 10;
int nMiddlePoints = 20;
int nInnerPoints = 30;
int nCastlePoints = 100;
int nWallBonus = 2;

int nCastleTargetRate;
int nCastleTurnSpd;
int nMaxBombs;

int nStartLives = 3;
int nMaxLives = 10;

int nSparksMinAge = 30;
int nSparksMaxAge = 50;
int nSparksSmall  = 32;
int nSparksLarge  = 64;
float fSparksMinSpd = 0.1;
float fSparksMaxSpd = 2.5;

int nOuterSpd;
int nMiddleSpd;
int nInnerSpd;

int nOuterRadius = 100;
int nMiddleRadius = 75;
int nInnerRadius = 50;

void ResetDifficulty(void) {

   fBombSpd = 0.5;
   nBombSearchRate = 60;

   nCastleTargetRate = 30;
   nCastleTurnSpd = 4;
   nMaxBombs = 10;

   nOuterSpd = 4;
   nMiddleSpd = -4;
   nInnerSpd = 2;
}

void Escalate(void) {

   static int nCalled = 0;

   if(nCalled % 2 == 0) {
      nOuterSpd = (int)((float)nOuterSpd * 1.5);
      nMiddleSpd = (int)((float)nMiddleSpd * 1.5);
      nInnerSpd = (int)((float)nInnerSpd * 1.5);

      if(nOuterSpd > 24)
         nOuterSpd = 24;
      if(nOuterSpd < -24)
         nOuterSpd = -24;
      
      if(nMiddleSpd > 24)
         nMiddleSpd = 24;
      if(nMiddleSpd < -24)
         nMiddleSpd = -24;

      if(nInnerSpd > 24)
         nInnerSpd = 24;
      if(nInnerSpd < -24)
         nInnerSpd = -24;
   }
   
   if(fBombSpd < 3.0)
      fBombSpd += 0.5;

   nBombSearchRate -= 4;
   if(nBombSearchRate <= 0)
      nBombSearchRate = 1;

   nCastleTargetRate -= 2;
   if(nCastleTargetRate <= 0)
      nCastleTargetRate = 1;

   if(nCastleTurnSpd < 512)
      nCastleTurnSpd += 4;

   if(nCalled % 2 == 0)
      if(nMaxBombs < 40)
         nMaxBombs++;

   nCalled++;
}

