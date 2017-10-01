
// $Id: laser.h,v 1.2 2002-01-20 21:20:13 bernard Exp $

#ifndef __LASER_H__
#define __LASER_H__

#include <stdio.h>
#include <allegro.h>

#include "init.h"
#include "actor.h"
#include "vector.h"

class Laser : public Actor {
   private:
      int nAngle;
      int nAge;
      int rgnX[4], rgnY[4];         // positions for laser segments
      Rect rgrgrtClean[4][2];       // dirty rects for laser segments
      Vector vDir;                  // direction of laser
      Vector vPerp;                 // perpendicular to direction of laser
      int nSize;                    // width of laser
      int LaserHit(const Vector &); // true if point in laser kill zone
   public:
      Laser(int);

      ~Laser() { }

      void Action(void);

      void Erase(int);
      void Draw(int);
};

extern ActorList<Laser> alLaser;

#endif

