
// $Id: bomb.h,v 1.2 2002-01-20 21:20:13 bernard Exp $

#ifndef __BOMB_H__
#define __BOMB_H__

#include <stdio.h>
#include <allegro.h>

#include "init.h"
#include "actor.h"
#include "vector.h"
#include "param.h"

class Bomb : public Actor {
   private:
      Vector vPos, vVel;
      int nSearchDel;
      int nAnimRate;
   public:
      Bomb(int);

      ~Bomb() { }

      Vector Pos(void) { return(vPos); }

      void Action(void);

      void Erase(int);
      void Draw(int);
};

extern ActorList<Bomb> alBomb;

#endif

