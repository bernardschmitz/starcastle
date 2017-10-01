
// $Id: inner.h,v 1.2 2002-01-20 21:20:13 bernard Exp $

#ifndef __INNER_H__
#define __INNER_H__

#include <stdio.h>
#include <allegro.h>

#include "init.h"
#include "actor.h"
#include "vector.h"
#include "param.h"

class Inner : public Actor {
   private:
      Vector vPos;
      int nDa;        // turn speed
      int nAngle;
      int nDamage;    // damage counter and also used to display damaged frames
   public:
      Inner(int, int);

      ~Inner() { }

      int Angle(void) { return(nAngle); }
      int Speed(void) { return(nDa); }
      void SetSpeed(int s) { nDa = s; }

      void Action(void);

      void Erase(int);
      void Draw(int);
};

extern ActorList<Inner> alInner;

#endif

