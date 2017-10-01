
// $Id: console.cc,v 1.2 2002-01-20 21:20:13 bernard Exp $

#include <stdio.h>
#include <allegro.h>

#include "init.h"
#include "console.h"

void Console(char *sz) {

   static int nRow = 0;

   textout(screen, font, sz, 0, nRow, makecol(255, 255, 255));

   nRow += 8;

   if(nRow >= SCREEN_H) {
      nRow -= 8;
      blit(screen, screen, 0, 0, 0, 8, SCREEN_W, SCREEN_H-8);
   }

//   fprintf(stderr, "%s\n", sz);
}


