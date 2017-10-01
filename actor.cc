
// $Id: actor.cc,v 1.2 2002-01-20 21:20:13 bernard Exp $

#include <stdio.h>
#include <allegro.h>

#include "actor.h"

// creates a blank actor

Actor::Actor() {

   nXPos = 0;
   nYPos = 0;
   nWidth = 0;
   nHeight = 0;
   nRadius = 0;
   rgprleFrames = NULL;

   nFrame = 0;

   fFlags = 0;

   cErase[0] = 0;
   cErase[1] = 0;

   rgrtDirty[0].sx = 0;
   rgrtDirty[0].sy = 0;
   rgrtDirty[0].ex = 0;
   rgrtDirty[0].ey = 0;
   rgrtDirty[1].sx = 0;
   rgrtDirty[1].sy = 0;
   rgrtDirty[1].ex = 0;
   rgrtDirty[1].ey = 0;

   pactNext = pactPrev = NULL;
}

Actor::Actor(int x, int y, RLE_SPRITE **rgprle, int nF) {

   nXPos = x;
   nYPos = y;
   nWidth = rgprle[0]->w;
   nHeight = rgprle[0]->h;
   nRadius = (nWidth+nHeight)/4;
   rgprleFrames = rgprle;

   nFrame = nF;

   fFlags = 0;

   cErase[0] = 0;
   cErase[1] = 0;

   rgrtDirty[0].sx = 0;
   rgrtDirty[0].sy = 0;
   rgrtDirty[0].ex = 0;
   rgrtDirty[0].ey = 0;
   rgrtDirty[1].sx = 0;
   rgrtDirty[1].sy = 0;
   rgrtDirty[1].ex = 0;
   rgrtDirty[1].ey = 0;

   pactNext = pactPrev = NULL;
}

Actor::Actor(int x, int y, int w, int h) {

   nXPos = x;
   nYPos = y;
   nWidth = w;
   nHeight = h;
   nRadius = (nWidth+nHeight)/4;
   rgprleFrames = NULL;

   nFrame = 0;

   fFlags = 0;

   cErase[0] = 0;
   cErase[1] = 0;

   rgrtDirty[0].sx = 0;
   rgrtDirty[0].sy = 0;
   rgrtDirty[0].ex = 0;
   rgrtDirty[0].ey = 0;
   rgrtDirty[1].sx = 0;
   rgrtDirty[1].sy = 0;
   rgrtDirty[1].ex = 0;
   rgrtDirty[1].ey = 0;

   pactNext = pactPrev = NULL;
}


int Actor::Overlap(Actor *pact) {

   if(fFlags & ACT_SPH) {   // use bounding circles?

      int x0 = nXPos+nWidth/2;
      int y0 = nYPos+nHeight/2;

      int x1 = pact->nXPos+pact->nWidth/2;
      int y1 = pact->nYPos+pact->nHeight/2;

      int dx = x1 - x0;
      int dy = y1 - y0;

      int dist = dx*dx + dy*dy;

      if(dist - nRadius*nRadius - pact->nRadius*pact->nRadius < 0)
         return(1);
   }
   else {

      // bounding rectangles

      int w0 = nWidth;
      int h0 = nHeight;

      int w1 = pact->nWidth;
      int h1 = pact->nHeight;

      if(nXPos+w0 >= pact->nXPos && pact->nXPos+w1 >= nXPos &&
         nYPos+h0 >= pact->nYPos && pact->nYPos+h1 >= nYPos) {
         return(1);
      }
   }

   return(0);
}


void ActorListBase::Collision(ActorListBase &al1) {

   Actor *pact0 = First();

   // only check collision if not allready collided
   while(!(pact0->fFlags & ACT_HIT) && pact0 != Head()) {

      Actor *pact1 = al1.First();

      // only check collision if not allready collided
      while(!(pact1->fFlags & ACT_HIT) && !(pact0->fFlags & ACT_HIT)
                        && pact1 != al1.Head()) {

         if(pact0 != pact1) {
            if(pact0->Overlap(pact1)) {
               pact1->Collision(pact0);
               pact0->Collision(pact1);
            }
         }
         pact1 = al1.Next();
      }

      pact0 = Next();
   }

}

void ActorListBase::Insert(Actor *pact) {

   pact->pactNext = actHead.pactNext;
   pact->pactPrev = &actHead;
   actHead.pactNext->pactPrev = pact;
   actHead.pactNext = pact;

   cActors++;
}

void ActorListBase::Remove(Actor *pact) {

   cActors--;

   pact->pactNext->pactPrev = pact->pactPrev;
   pact->pactPrev->pactNext = pact->pactNext;
}

ActorListBase::~ActorListBase() {

   Actor *pact = actHead.pactNext;

   while(pact != &actHead) {
      Actor *pactTmp = pact->pactNext;
      Remove(pact);
      delete pact;
      pact = pactTmp;
   }
}

void ActorListBase::Action(void) {

   Actor *pact = actHead.pactNext;

   while(pact != &actHead) {
      // don't call if actor going to be deleted
      if(!(pact->fFlags & ACT_DEL))
         pact->Action();
      pact = pact->pactNext;
   }
}

void ActorListBase::Draw(int nPage) {

   Actor *pact = actHead.pactNext;

   while(pact != &actHead) {
      // don't call if actor going to be deleted
      if(!(pact->fFlags & ACT_DEL)) {
         pact->cErase[nPage]++;
         pact->Draw(nPage);

//circle(pbmPage[nPage], pact->nXPos+pact->nWidth/2, pact->nYPos+pact->nHeight/2, pact->nRadius-1, nWhite);

      }
      pact = pact->pactNext;
   }
}

void ActorListBase::Erase(int nPage) {

   Actor *pact = actHead.pactNext;

   while(pact != &actHead) {
      // call erase if needed
      if(pact->cErase[nPage] > 0) {
         pact->Erase(nPage);
         pact->cErase[nPage]--;
      }
      // if flags for deletion and no more erasure needed then delete
      if(pact->fFlags & ACT_DEL && pact->cErase[0] == 0 && pact->cErase[1] == 0) {
         Actor *pactTmp = pact->pactNext;
         Remove(pact);
         delete pact;
         pact = pactTmp;
      }
      else
         pact = pact->pactNext;
   }
}


void ActorListBase::Clear(void) {

   Actor *pact = actHead.pactNext;

   while(pact != &actHead) {
      Actor *pactTmp = pact->pactNext;
      Remove(pact);
      delete pact;
      pact = pactTmp;
   }
}

