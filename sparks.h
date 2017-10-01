
// $Id: sparks.h,v 1.2 2002-01-20 21:20:13 bernard Exp $

#ifndef __SPARKS_H__
#define __SPARKS_H__

#include <stdio.h>
#include <allegro.h>

#include "init.h"
#include "actor.h"
#include "vector.h"
#include "param.h"

struct Particle {
   int nLife;
   int nColor;
   Vector vOldPos;
   Vector vPos;
   Vector vVel;
   int nAge;
   Particle() { nLife = nColor = 0; vPos = vVel = vOldPos = Vector(0, 0, 0); nAge = 0; }
   Particle(const Vector &p, const Vector &v, int l, int c) {
                vOldPos = vPos = p; vVel = v; nLife = l; nColor = c; nAge = nLife; }
   ~Particle() { }
};

class Sparks : public Actor {
   private:
      int fAlloc;      // true if class allocated ps array
      int nParticles;
      Particle *ps;
   public:
      Sparks(int, Particle *);
      Sparks(int, const Vector &, const Vector &, float, float, int, int, int, int =255, int =255);
      Sparks(BITMAP *, int, const Vector &, const Vector &, float, float, int, int, int, int =255, int =255);

      ~Sparks();

      void Action(void);

      void Erase(int nPage);
      void Draw(int nPage);
};

extern ActorList<Sparks> alSparks;

extern Particle *Bitmap2Particle(BITMAP *, int, int &, const Vector &, const Vector &, float, float, int, int, int, int =255, int =255);

#endif

