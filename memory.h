
// $Id: memory.h,v 1.3 2002-04-03 05:14:32 bernard Exp $

#ifndef __MEM_H__
#define __MEM_H__

#ifndef NDEBUG

void * operator new(size_t);
void operator delete(void *);

void memory_report(void);

#endif

#endif

