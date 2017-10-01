
// $Id: memory.cc,v 1.3 2002-04-03 05:14:32 bernard Exp $

#include <stdio.h>
#include <stdlib.h>

#ifdef MEMCNT

#include "memory.h"

static unsigned long cTotalBytes = 0;
static unsigned long cMaxBytes   = 0;
static unsigned long cTotalNew   = 0;
static unsigned long cTotalDel   = 0;

static unsigned long cMemCount   = 0;

void memory_report(void) {

   fprintf(stderr, "\nMaximum bytes allocated     %lu\n", cMaxBytes);

   if((cTotalNew - cTotalDel) != 0) {
      fprintf(stderr, "Total calls to new          %lu\n", cTotalNew);
      fprintf(stderr, "Total calls to delete       %lu\n", cTotalDel);
      fprintf(stderr, "Need %lu more calls to delete.\n", cTotalNew-cTotalDel);
   }

   if(cTotalBytes != 0)
      fprintf(stderr, "Memory LEAK!? %lu bytes still allocated\n", cTotalBytes);

}

void * operator new(size_t cBytes) {

   cMemCount++;

   cTotalNew++;
   cTotalBytes += cBytes;

   if(cTotalBytes > cMaxBytes)
      cMaxBytes = cTotalBytes;

   void *pvMem = malloc(cBytes + sizeof(int)*2);

   ((int *)pvMem)[0] = cBytes;
   ((int *)pvMem)[1] = cMemCount;

//fprintf(stderr, "%010d allocating %d\n", ((int *)pvMem)[1], ((int *)pvMem)[0]);

   return((void *)((int *)pvMem + sizeof(int)*2));
}

void operator delete(void *pvMem) {

   if(pvMem == NULL)
      return;

   cTotalDel++;

   //pvMem -= sizeof(int)*2;
   pvMem = (void *)((int *)pvMem - sizeof(int)*2);
   cTotalBytes -= ((int *)pvMem)[0];

   if(cTotalBytes == 0)
      memory_report();

//fprintf(stderr, "%010d deallocating %d\n", ((int *)pvMem)[1], ((int *)pvMem)[0]);

   free(pvMem);
}

#endif

