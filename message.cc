
// $Id: message.cc,v 1.2 2002-01-20 21:20:13 bernard Exp $

#include "message.h"
#include "sparks.h"

ActorList<Message> alMessage;

Message::Message(int x, int y, char *sz, int c, int gl, int l, int sl, FONT *pfnt) : Actor(0, 0, 0, 0) {

   nColor   = c;
   szText   = sz;
   pfntFont = pfnt;

   nGrow   = gl;
   nSit    = l;
   nShrink = sl;

   nWidth  = text_length(pfntFont, szText);
   nHeight = text_height(pfntFont);

   pbmText = create_bitmap(nWidth, nHeight);

   clear(pbmText);
   textout(pbmText, pfntFont, szText, 0, 0, nColor);

   nXPos = x;
   nYPos = y;

   nState = GROW;
   nDelay = nGrow;

   nDw = (nWidth<<16) / nDelay;
   nDh = (nHeight<<16) / nDelay;
   nDx = (nWidth<<16)/2 / nDelay;
   nDy = (nHeight<<16)/2 / nDelay;

   nX = nXPos<<16;
   nY = nYPos<<16;
   nW = 1<<16;
   nH = 1<<16;
}

Message::~Message() {

   destroy_bitmap(pbmText);
}

void Message::Action(void) {

/*
   nAge++;

   if(nAge == nLife) {
      fFlags |= ACT_DEL;
      return;
   }
*/
   switch(nState) {

      case GROW : 
                  nW += nDw;
                  nH += nDh;
                  nX -= nDx;
                  nY -= nDy;

                  nDelay--;
                  if(nDelay <= 0) {
                     nState = SIT;
                     nDelay = nSit;
                     
                  }

                  break;

      case SIT : nDelay--;
                 if(nDelay <= 0) {
                    nState = SHRINK;
                    nDelay = nShrink;

                    nDw = (nWidth<<16) / nDelay;
                    nDh = (nHeight<<16) / nDelay;
                    nDx = (nWidth<<16)/2 / nDelay;
                    nDy = (nHeight<<16)/2 / nDelay;

                    nX = (nXPos-nWidth/2)<<16;
                    nY = (nYPos-nHeight/2)<<16;
                    nW = nWidth<<16;
                    nH = nHeight<<16;
                 }
                 break;

      case SHRINK : 

                  if(nShrink < 0) {
                     fFlags |= ACT_DEL;

                     alSparks.Insert(new Sparks(pbmText, 1, Vector(nX>>16, nY>>16, 0),
                                                               Vector(0, 0, 0), 
                                                               0.1, 0.5, 40, 70, nGreen));
                     return;
                  }

                  nW -= nDw;
                  nH -= nDh;
                  nX += nDx;
                  nY += nDy;

                  nDelay--;
                  if(nDelay <= 0)
                     fFlags |= ACT_DEL;

                  break;
   }

}

void Message::Erase(int nPage) {

   //blit(pbmBackground, pbmPage[nPage], rgrtDirty[nPage].sx, rgrtDirty[nPage].sy, rgrtDirty[nPage].sx, rgrtDirty[nPage].sy, nW>>16, nH>>16);
   blit(pbmBackground, pbmPage[nPage], rgrtDirty[nPage].sx, rgrtDirty[nPage].sy, rgrtDirty[nPage].sx, rgrtDirty[nPage].sy, rgrtDirty[nPage].ex, rgrtDirty[nPage].ey);
}

void Message::Draw(int nPage) {

   //draw_sprite(pbmPage[nPage], pbmText, nXPos, nYPos);
   stretch_sprite(pbmPage[nPage], pbmText, nX>>16, nY>>16, nW>>16, nH>>16);

   rgrtDirty[nPage].sx = nX>>16; rgrtDirty[nPage].sy = nY>>16;
   rgrtDirty[nPage].ex = (nX+nW)>>16; rgrtDirty[nPage].ey = (nY+nH)>>16;
}

