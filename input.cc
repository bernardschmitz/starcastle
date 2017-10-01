
// $Id: input.cc,v 1.2 2002-01-20 21:20:13 bernard Exp $

#include <allegro.h>

#include "input.h"

int fThrust    = 0;
int fLeftTurn  = 0;
int fRightTurn = 0;
int fQuit      = 0;
int fShoot     = 0;

void ProcessInput(void) {

   fThrust    = key[KEY_UP];
   fLeftTurn  = key[KEY_LEFT];
   fRightTurn = key[KEY_RIGHT];
   fQuit      = key[KEY_ESC];
   fShoot     = key[KEY_LCONTROL];

   // FIX THIS mouse sorta works...
   int dx, dy;
   get_mouse_mickeys(&dx, &dy);

   int mdelta = dx / 10;

   fLeftTurn  |= mdelta < 0;
   fRightTurn |= mdelta > 0;

   fShoot  |= mouse_b & 1;
   fThrust |= mouse_b & 2;
}

