
// $Id: score.h,v 1.2 2002-01-20 21:20:13 bernard Exp $

#ifndef __SCORE_H__
#define __SCORE_H__

#include "actor.h"
#include "param.h"

class Score : public Actor {
   private:
      int nScore;
      int nLives;
      int nHits;
      int nFired;
      int nStartTime, nTime;
      int nCastle;
   public:
      Score();
      ~Score() { }

      void Action(void);

      int GameOver(void) { return(nLives <= 0); }

      void IncFired(void) { nFired++; }
      void IncHits(void) { nHits++; }
      void IncCastle(void) { nCastle++; }

      void IncLives(void) { nLives++; }
      void DecLives(void) { nLives--; }

      void AddPoints(int p) { nScore += p; }

      void Draw(int);
      void Erase(int);
};

extern ActorList<Score> alScore;

#endif

