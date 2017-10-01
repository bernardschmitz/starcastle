
// $Id: exp.h,v 1.2 2002-01-20 21:20:13 bernard Exp $

#ifndef __EXP_H__
#define __EXP_H__

#include <stdio.h>
#include <allegro.h>

#include "init.h"
#include "actor.h"
#include "vector.h"
#include "param.h"
#include "random.h"

#define EXP_LARGE   0x00     // large explosion
#define EXP_ORANGE  0x00     // orange explosion

#define EXP_SMALL   0x01     // small explosion
#define EXP_GREEN   0x02     // green explosion

#define EXP_RAND    0x04     // random explosion

class Explosion : public Actor {
   private:
      Vector vPos, vVel;
      int nAge;
   public:
      // defaults to a random explosion
      Explosion(const Vector &, const Vector &, int =EXP_RAND);

      ~Explosion() { }

      void Action(void);

      void Erase(int);
      void Draw(int);
};

extern ActorList<Explosion> alExplosion;

#endif

