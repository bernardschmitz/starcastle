
// $Id: trig.cc,v 1.2 2002-01-20 21:20:13 bernard Exp $

#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "trig.h"


SineTable Sin;
CosineTable Cos;
TangentTable Tan;


SineTable::SineTable() {

   sin_table = new float [4096];
   assert(sin_table != NULL);

   for(int i=0; i<4096; i++)
      sin_table[i] = sin(float(i)*3.141592654/2048.0);
}

SineTable::~SineTable() {

   delete [] sin_table;
}

CosineTable::CosineTable() {

   cos_table = new float [4096];
   assert(cos_table != NULL);

   for(int i=0; i<4096; i++)
      cos_table[i] = cos(float(i)*3.141592654/2048.0);
}

CosineTable::~CosineTable() {

   delete [] cos_table;
}

TangentTable::TangentTable() {

   tan_table = new float [4096];
   assert(tan_table != NULL);

   for(int i=0; i<4096; i++)
      tan_table[i] = tan(float(i)*3.141592654/2048.0);
}

TangentTable::~TangentTable() {

   delete [] tan_table;
}

