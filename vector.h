
// $Id: vector.h,v 1.2 2002-01-20 21:20:13 bernard Exp $

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <math.h>

struct Vector {
   float x, y, z;

   Vector() { }
   Vector(float fx, float fy, float fz) { x = fx; y = fy; z = fz; }
   Vector(const Vector& v) { x = v.x; y = v.y; z = v.z; }
   ~Vector() { }

   friend Vector operator-(const Vector& v) { return(Vector(-v.x, -v.y, -v.z)); }

   friend Vector operator+(const Vector& vA, const Vector& vB) { return(Vector(vA.x+vB.x, vA.y+vB.y, vA.z+vB.z)); }
   friend Vector operator-(const Vector& vA, const Vector& vB) { return(Vector(vA.x-vB.x, vA.y-vB.y, vA.z-vB.z)); }

   // norm
   friend Vector operator~(const Vector& v);

   // dot product
   friend float operator*(const Vector& vA, const Vector& vB) { return(vA.x*vB.x + vA.y*vB.y + vA.z*vB.z); }

   // cross product
   friend Vector operator%(const Vector& vA, const Vector& vB);

   Vector& operator+=(const Vector& v) { x += v.x; y += v.y; z += v.z; return(*this); }
   Vector& operator-=(const Vector& v) { x -= v.x; y -= v.y; z -= v.z; return(*this); }
   Vector& operator*=(const float f) { x *= f; y *= f; z *= f; return(*this); }
   Vector& operator/=(const float f) { float ff = 1.0/f; return(operator*=(ff)); }

   friend Vector operator*(const Vector& v, const float f) { return(Vector(v.x*f, v.y*f, v.z*f)); }
   friend Vector operator/(const Vector& v, const float f) { float ff = 1.0/f; return(v * ff); }
};


inline Vector operator%(const Vector& vA, const Vector& vB) {

   return(Vector(vA.y*vB.z - vA.z*vB.y,
                 vA.z*vB.x - vA.x*vB.z,
                 vA.x*vB.y - vA.y*vB.x));
}

inline Vector operator~(const Vector& v) {

   float f = v*v;

   if(f > 0.0) {
      f = sqrt(f);
      return(v/f);
   }

   return(v);
}

#endif

