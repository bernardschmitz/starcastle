
// $Id: trig.h,v 1.2 2002-01-20 21:20:13 bernard Exp $

#ifndef __TRIG_H__
#define __TRIG_H__

#include <assert.h>

class SineTable {
   private:
      float *sin_table;
   public:
      SineTable();
      ~SineTable();

      // maybe have it automatically bounds check?
      float operator[](int d) { assert(d>=0 && d<4096); return(sin_table[d]); }
};

class CosineTable {
   private:
      float *cos_table;
   public:
      CosineTable();
      ~CosineTable();

      // maybe have it automatically bounds check?
      float operator[](int d) { assert(d>=0 && d<4096); return(cos_table[d]); }
};

class TangentTable {
   private:
      float *tan_table;
   public:
      TangentTable();
      ~TangentTable();

      // maybe have it automatically bounds check?
      float operator[](int d) { assert(d>=0 && d<4096); return(tan_table[d]); }
};

extern SineTable Sin;
extern CosineTable Cos;
extern TangentTable Tan;

#endif

