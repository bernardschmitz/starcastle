
// $Id: message.h,v 1.2 2002-01-20 21:20:13 bernard Exp $

#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <stdio.h>
#include <allegro.h>

#include "init.h"
#include "actor.h"
#include "vector.h"
#include "param.h"

class Message : public Actor {
   private:
      enum States { GROW, SHRINK, SIT };
      States nState;
      char *szText;
      int nColor;
      FONT *pfntFont;
      BITMAP *pbmText;
      int nDelay;
      int nDx, nDy, nDw, nDh;
      int nX, nY, nW, nH;
      int nGrow, nSit, nShrink;
   public:
      Message(int, int, char *, int, int, int, int, FONT * =rgpfntFont[0]);

      ~Message();

      void Action(void);

      void Erase(int);
      void Draw(int);
};

extern ActorList<Message> alMessage;

#endif

