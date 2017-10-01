
// $Id: shot.h,v 1.2 2002-01-20 21:20:13 bernard Exp $

#ifndef __SHOT_H__
#define __SHOT_H__

#include <stdio.h>
#include <allegro.h>

#include "init.h"
#include "actor.h"
#include "vector.h"
#include "param.h"

class Shot : public Actor {
   private:
      Vector vPos, vVel;
      int nLife;
      int nAnimRate;
   public:
      Shot(const Vector &vP, const Vector &vV);

      ~Shot() { }

      void Action(void);

      void Collision(Actor *);

      void Erase(int);
      void Draw(int);
};

extern ActorList<Shot> alShot;

#endif

