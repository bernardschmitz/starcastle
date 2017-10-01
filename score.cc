
// $Id: score.cc,v 1.2 2002-01-20 21:20:13 bernard Exp $

#include "param.h"
#include "score.h"

ActorList<Score> alScore;

Score::Score() : Actor(0, 0, 10*(10+1+2+1+2+1+4+1+8), 20) {

   nScore = nHits = nFired = nTime = 0;
   nLives = nStartLives;
   nCastle = 1;

   nStartTime = timer;
}

void Score::Action(void) {

   nTime = (timer - nStartTime) / kTimerRate;

   if(nLives > nMaxLives)
      nLives = nMaxLives;

}

void Score::Erase(int nPage) {

   blit(pbmBackground, pbmPage[nPage], rgrtDirty[nPage].sx, rgrtDirty[nPage].sy, rgrtDirty[nPage].sx, rgrtDirty[nPage].sy, nWidth, nHeight);
}

void Score::Draw(int nPage) {

   textprintf(pbmPage[nPage], rgpfntFont[0], nXPos, nYPos, nGreen, "%010d %02d %02d %03d%% %02d:%02d:%02d", nScore, nCastle, nLives, nFired==0?0:nHits*100/nFired, nTime/3600, nTime%3600/60, nTime%3600%60);

   rgrtDirty[nPage].sx = nXPos; rgrtDirty[nPage].sy = nYPos;
   rgrtDirty[nPage].ex = nXPos+nWidth; rgrtDirty[nPage].ey = nYPos+nHeight;
}

