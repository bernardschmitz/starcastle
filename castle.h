
// $Id: castle.h,v 1.2 2002-01-20 21:20:13 bernard Exp $

#ifndef __CASTLE_H__
#define __CASTLE_H__

#include <stdio.h>
#include <allegro.h>

#include "init.h"
#include "actor.h"
#include "vector.h"

class Castle : public Actor {
   private:
      enum State { TARGET, TURN, SHOOT };
      State nState;
      Vector vPos;
      int nAngle;       // current direction
      int nTarget;      // direction moving to
      int nTurn;        // turn speed
      int nDelay;       // delay counter
   public:
      Castle(int);

      ~Castle() { }

      void Action(void);

      void Erase(int);
      void Draw(int);
};

extern ActorList<Castle> alCastle;

#endif

