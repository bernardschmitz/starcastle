
// $Id: param.h,v 1.2 2002-01-20 21:20:13 bernard Exp $

#ifndef __PARAM_H__
#define __PARAM_H__

// important game parameters

extern int kFrameRate;
extern int kTimerRate;

extern int nDifficultyRate;

extern int nPlayerTurnSpd;
extern float rPlayerAcc;
extern float rPlayerFriction;
extern float rPlayerMaxSpd; 
extern float rPlayerRecoil;
extern int nPlayerShotRate;
extern int nMaxShots;

extern int nShotLife;
extern float rShotSpd;

extern float fBombSpd;
extern int nBombSearchRate;

extern int nOuterPoints;
extern int nMiddlePoints;
extern int nInnerPoints;
extern int nCastlePoints;
extern int nWallBonus;

extern int nCastleTargetRate;
extern int nCastleTurnSpd;
extern int nMaxBombs;

extern int nStartLives;
extern int nMaxLives;

extern int nSparksMinAge;
extern int nSparksMaxAge;
extern int nSparksSmall;
extern int nSparksLarge;
extern float fSparksMinSpd;
extern float fSparksMaxSpd;

extern int nOuterSpd;
extern int nMiddleSpd;
extern int nInnerSpd;

extern int nOuterRadius;
extern int nMiddleRadius;
extern int nInnerRadius;

extern void ResetDifficulty(void);
extern void Escalate(void);

#endif

