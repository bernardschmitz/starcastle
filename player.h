
// $Id: player.h,v 1.2 2002-01-20 21:20:13 bernard Exp $

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <stdio.h>
#include <allegro.h>

#include "init.h"
#include "actor.h"
#include "vector.h"

class Player : public Actor {
   private:
      Vector vPos, vVel;
      int nDir;
      int nShotDel;
      int nShotFrm;
      int nThrustFrm;
   public:
      Player(const Vector &v, int d=0);

      ~Player() { }

      Vector Pos(void) { return(vPos); }
      void Accelerate(const Vector &vAcc) { vVel += vAcc; }

      void Action(void);

      void Erase(int);
      void Draw(int);

};

extern ActorList<Player> alPlayer;

#endif

