
// $Id: input.h,v 1.2 2002-01-20 21:20:13 bernard Exp $

#ifndef __INPUT_H__
#define __INPUT_H__

extern int fThrust;        // player thrusting
extern int fLeftTurn;      // player left
extern int fRightTurn;     // player right
extern int fQuit;          // player wants to quit
extern int fShoot;         // player shooting

extern void ProcessInput(void);

#endif
