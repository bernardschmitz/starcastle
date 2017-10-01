
// $Id: actor.h,v 1.2 2002-01-20 21:20:13 bernard Exp $

#ifndef __ACTOR_H__
#define __ACTOR_H__

#include <stdio.h>

#include <allegro.h>

#include "init.h"

struct Rect {
   int sx, sy, ex, ey;
};

#define ACT_HIT      0x01       // collision 
#define ACT_DEL      0x02       // delete this actor
#define ACT_SPH      0x04       // use bounding circles for collision tests

// actor class, much like a sprite

class Actor {
   protected:
      int nXPos, nYPos;          // position in pixel coords
      int nWidth, nHeight;       // size in pixels
      int nRadius;               // size in pixels
      int nFrame;                // current frame to display
      RLE_SPRITE **rgprleFrames; // array of frame pointers
      Rect rgrtDirty[2];         // rectangle that was drawn, one for each page
      int fFlags;                // various flags, collision, delete etc...
      int cErase[2];             // incremented every draw(), dec every erase()
      Actor *pactNext;           // next actor
      Actor *pactPrev;           // prev actor
   public:
      Actor();
      Actor(int, int, RLE_SPRITE **, int =0);
      Actor(int, int, int, int);
      virtual ~Actor() { }

      void Position(int x, int y) { nXPos = x; nYPos = y; }

      int XPos(void) { return(nXPos); }
      int YPos(void) { return(nYPos); }
      int Width(void) { return(nWidth); }
      int Height(void) { return(nHeight); }

      int Overlap(Actor *);   // returns true if this actor overlaps (collides)
                              // with the actor pointed to

      virtual void Action(void) { };  // called to update actor position
      virtual void Erase(int nPage) { nPage=nPage; }   // erases actor
      virtual void Draw(int nPage) { nPage=nPage; }    // draws actor

      // called when an actor hits another.
      // sets the collision flag
      virtual void Collision(Actor *pact) { pact=pact; fFlags |= ACT_HIT; }

      friend class ActorListBase;
};


// list of actors

class ActorListBase {
   private:
      Actor actHead;     // head of list
      Actor *pactIter;   // used for list iteration
      int cActors;       // number of actors in list
   public:
      ActorListBase() { cActors = 0; actHead.pactNext = &actHead; actHead.pactPrev = &actHead; }
      virtual ~ActorListBase();

      void Insert(Actor *);
      void Remove(Actor *);

      void Clear(void);

      int Count(void) { return(cActors); }

      void Action(void); // calls the action() function for each actor in list
      void Draw(int);    // draw
      void Erase(int);   // erase

      // returns the head of the list
      Actor *Head(void) { return(&actHead); }

      // returns the first actor in the list
      Actor *First(void) { pactIter = actHead.pactNext; return(pactIter); }

      // return the next actor in the list
      Actor *Next(void) { pactIter = pactIter->pactNext; return(pactIter); }

      // checks every actor in this list against every actor in passed list
      // calling overlap() to detect collision
      // calling collision() if collision occured
      void Collision(ActorListBase &);
};

// actor list template to avoid having to manually cast list elements

template<class T> class ActorList : public ActorListBase {
   public:
      void Insert(T *pact) { ActorListBase::Insert(pact); }
      void Remove(T *pact) { ActorListBase::Remove(pact); }
      T *Head(void) { return((T *)ActorListBase::Head()); }
      T *First(void) { return((T *)ActorListBase::First()); }
      T *Next(void) { return((T *)ActorListBase::Next()); }
};


#endif

