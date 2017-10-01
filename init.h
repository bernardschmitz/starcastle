
// $Id: init.h,v 1.2 2002-01-20 21:20:13 bernard Exp $

#ifndef __INIT_H__
#define __INIT_H__

#include <allegro.h>

// some useful colors
extern int nRed;
extern int nGreen;
extern int nBlue;
extern int nBlack;
extern int nWhite;
extern int nYellow;

extern int fPageFlipping;

// screen info
extern BITMAP *pbmPage[2];
extern int nPage;
extern BITMAP *pbmBackground;

// lighting colormap
extern COLOR_MAP lites;
//extern COLOR_MAP litesTitle;

// various palettes
extern PALETTE palPalette;
extern PALETTE palWhite, palBlack, palGray;
extern PALETTE palTitle;

extern RLE_SPRITE *prleStarTitle;
extern RLE_SPRITE *prleCastleTitle;

// some fonts
extern FONT *rgpfntFont[4];

// sprite animation frames
extern RLE_SPRITE *rgprleCastle[1024];
extern RLE_SPRITE *rgprlePlayer[512];
extern RLE_SPRITE *rgrgprleExplosions[4][30];
extern RLE_SPRITE *rgrgprleSmallExp[4][30];
extern RLE_SPRITE *rgprleShock[2][24];
extern RLE_SPRITE *rgprleShot[8];
extern RLE_SPRITE *rgprleBomb[16];
extern RLE_SPRITE *rgprleLaser[32*5];
extern RLE_SPRITE *rgprleOuter[128];
extern RLE_SPRITE *rgprleMiddle[128];
extern RLE_SPRITE *rgprleInner[64];

// background bitmap
extern BITMAP *pbmStars;

// timing stuff
// FIX THIS change the names
extern volatile int fps;
extern volatile int frames;
extern volatile int target_cycle;
extern volatile int ticker;
extern volatile int lastfrm;
extern volatile int timer;
extern int actual_cycle;

extern void Init(void);

// converts a clockwise 0..4095 angle to an anticlockwise 0.63 frame angle
inline int Angle2Frame(int nA) {

   return(((63-nA/64)-15)&0x3f);
}

// converts an anticlockwise 0..63 frame angle to a clockwise 0..4095 angle
inline int Frame2Angle(int nF) {

   return((-64*(nF-48))&0xfff);
}

// returns the difference between nA0 and nA1, >0 is clockwise
inline int AngleDiff(int nA0, int nA1) {

   int nD = nA1 - nA0;

   if(nD > 2048)
      nD -= 4096;

   if(nD < -2048)
      nD += 4096;

   return(nD);
}

#endif

