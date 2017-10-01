
// $Id: random.cc,v 1.2 2002-01-20 21:20:13 bernard Exp $

#include <time.h>
#include <stdlib.h>

#include "random.h"

static int seed = 0;

// seed the random number generator
// use the rand() seeded with the current time if no seed given

void SeedRandom(int s) {

   if(s != 0)
       seed = s;
   else {
      srand(time(NULL));
      seed = rand();
   }
}

// returns the next 16bit psuedo random number in the range 0 .. n-1

int Random(int n) {

   if(n <= 0)
      return(0);

//   seed = seed * 69069 + 1;
// was using the above, but maybe below is better, I don't know

   seed = seed * 0x015a4e35 + 1;

   return(((seed >> 8) & 0xffff) % n);
}

