
// $Id: outer.h,v 1.2 2002-01-20 21:20:13 bernard Exp $

#ifndef __OUTER_H__
#define __OUTER_H__

#include <stdio.h>
#include <allegro.h>

#include "init.h"
#include "actor.h"
#include "vector.h"
#include "param.h"

class Outer : public Actor {
   private:
      Vector vPos;
      int nDa;        // turn speed
      int nAngle;
      int nDamage;
   public:
      Outer(int, int);

      ~Outer() { }

      int Angle(void) { return(nAngle); }
      int Speed(void) { return(nDa); }
      void SetSpeed(int s) { nDa = s; } 

      void Action(void);

      void Erase(int);
      void Draw(int);
};

extern ActorList<Outer> alOuter;

// makes three new walls
extern void InitWalls(void);  

// check if walls need to be regenerated
extern void CheckWalls(void);

// speed up walls
template<class T>
void SpeedWalls(ActorList<T> &al, int nSpd) {

   T *pT = al.First();
   while(pT != al.Head()) {
      pT->SetSpeed(nSpd);
      pT = al.Next();
   }
}

// copy walls from al0 to al1
template<class T, class K>
void GrowWalls(ActorList<T> &al0, ActorList<K> &al1) {

   // ensure al1 empty
   K *pK = al1.First();
   while(pK != al1.Head()) {
      K *pKTmp = al1.Next();
      al1.Remove(pK);
      pK = pKTmp;
   }

   // do the copy
   T *pT = al0.First();
   while(pT != al0.Head()) {
      al1.Insert(new K(pT->Angle(), pT->Speed()));
      pT = al0.Next();
   }
}

#endif

