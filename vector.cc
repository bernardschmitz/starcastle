
// $Id: vector.cc,v 1.2 2002-01-20 21:20:13 bernard Exp $

#include <math.h>

#include "vector.h"

/*
Vector operator%(const Vector& vA, const Vector& vB) {

   return(Vector(vA.y*vB.z - vA.z*vB.y,
                 vA.z*vB.x - vA.x*vB.z,
                 vA.x*vB.y - vA.y*vB.x));
}

Vector operator~(const Vector& v) {

   float f = v*v;

   if(f > 0.0) {
      f = sqrt(f);
      return(v/f);
   }

   return(v);
}
*/

