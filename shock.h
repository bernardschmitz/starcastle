
// $Id: shock.h,v 1.2 2002-01-20 21:20:13 bernard Exp $

#ifndef __SHOCK_H__
#define __SHOCK_H__

#include <stdio.h>
#include <allegro.h>

#include "init.h"
#include "actor.h"
#include "vector.h"
#include "param.h"

#define SHK_LARGE   0
#define SHK_SMALL   1

class ShockWave : public Actor {
   private:
      Vector vPos, vVel;
   public:
      ShockWave(const Vector &vP, const Vector &vV, int =SHK_LARGE);

      ~ShockWave() { }

      void Action(void);

      void Erase(int);
      void Draw(int);
};

extern ActorList<ShockWave> alShockWave;

#endif

