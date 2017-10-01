
// $Id: main.cc,v 1.4 2004-06-24 01:53:44 bernard Exp $

#include <stdio.h>
#include <time.h>
#include <allegro.h>

#include "init.h"
#include "player.h"
#include "input.h"
#include "vector.h"
#include "shot.h"
#include "exp.h"
#include "random.h"
#include "shock.h"
#include "castle.h"
#include "laser.h"
#include "bomb.h"
#include "outer.h"
#include "middle.h"
#include "inner.h"
#include "sparks.h"
#include "score.h"
#include "message.h"

extern int Title(void);

int fFinished = 0;

int fStep = 0;  // single step flag

int nDifficultyCount = 0;

const int cFadeLen = 10;
int nFadeType;
int cFade = 0;

void Render(void) {

   alMessage.Erase(nPage);
   alShockWave.Erase(nPage);
   alExplosion.Erase(nPage);
   alLaser.Erase(nPage);
   alOuter.Erase(nPage);
   alMiddle.Erase(nPage);
   alInner.Erase(nPage);
   alPlayer.Erase(nPage);
   alCastle.Erase(nPage);
   alShot.Erase(nPage);
   alBomb.Erase(nPage);
   alSparks.Erase(nPage);
   alScore.Erase(nPage);

   blit(pbmBackground, pbmPage[nPage], 0, 20, 0, 20, 80, 20);

   alSparks.Draw(nPage);
   alBomb.Draw(nPage);
   alShot.Draw(nPage);
   alLaser.Draw(nPage);
   alCastle.Draw(nPage);
   alPlayer.Draw(nPage);
   alInner.Draw(nPage);
   alMiddle.Draw(nPage);
   alOuter.Draw(nPage);
   alLaser.Draw(nPage);
   alExplosion.Draw(nPage);
   alShockWave.Draw(nPage);
   alScore.Draw(nPage);
   alMessage.Draw(nPage);

   textprintf(pbmPage[nPage], rgpfntFont[0], 0, 20, nYellow, "fps %3d", fps);

   if(fPageFlipping)
      scroll_screen(0, nPage*SCREEN_H);
   else
      blit(pbmPage[nPage], screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

   if(nFadeType != 0) {
      PALETTE palOut;
      switch(nFadeType) {
         case 1 : // black -> white
                  fade_interpolate(palBlack, palWhite, palOut, cFade*64/cFadeLen, 0, 255);
                  break;
         case 2 : // white -> main
                  fade_interpolate(palWhite, palPalette, palOut, cFade*64/cFadeLen, 0, 255);
                  break;
         case 3 : // main -> white
                  fade_interpolate(palPalette, palWhite, palOut, cFade*64/cFadeLen, 0, 255);
                  break;
         case 4 : // white -> black
                  fade_interpolate(palWhite, palBlack, palOut, cFade*64/cFadeLen, 0, 255);
                  break;
         case 5 : // main -> gray
                  fade_interpolate(palPalette, palGray, palOut, cFade*64/cFadeLen, 0, 255);
                  break;
      }
      //set_palette_range(palOut, 0, 255, 0);
      set_palette(palOut);
   }

   //scroll_screen(0, nPage*SCREEN_H);

   if(nPage == 0)
      nPage = 1;
   else
      nPage = 0;

   frames++;
}

int GameLoop(void) {

   if(!fFinished && alScore.First()->GameOver()) {
      nFadeType = 5;
      alMessage.Insert(new Message(SCREEN_W/2, SCREEN_H/2, "GAME OVER", nGreen, 60, 30, -1, rgpfntFont[3]));
      fFinished = 1;
   }

   // check if player has died
   if(!fFinished && alPlayer.Count() == 0)
      alPlayer.Insert(new Player(Vector(SCREEN_W/4, SCREEN_H/4, 0)));

   // check if castle has died
   if(alCastle.Count() == 0) {
      alCastle.Insert(new Castle(0));
      alOuter.Clear();
      alMiddle.Clear();
      alInner.Clear();
      InitWalls();
   }

   CheckWalls();

   alMessage.Action();
   alShockWave.Action();
   alExplosion.Action();
   alPlayer.Action();
   alShot.Action();
   alBomb.Action();
   alLaser.Action();
   alInner.Action();
   alMiddle.Action();
   alOuter.Action();
   alCastle.Action();
   alSparks.Action();

   alScore.Action();

   alShot.Collision(alBomb);
   alShot.Collision(alOuter);
   alShot.Collision(alMiddle);
   alShot.Collision(alInner);
   alShot.Collision(alCastle);
   alBomb.Collision(alPlayer);

   //ProcessInput();

   actual_cycle++;

   if(fQuit)
      nFadeType = 3;

   return(0);
}

void NewGame(void) {

   set_palette(palBlack);
   //set_palette(palPalette);

   blit(pbmStars, pbmPage[0], 0, 0, 0, 0, SCREEN_W, SCREEN_H);
   blit(pbmStars, pbmPage[1], 0, 0, 0, 0, SCREEN_W, SCREEN_H);

   blit(pbmStars, pbmBackground, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

   nDifficultyCount = 0;
   ResetDifficulty();

   alPlayer.Insert(new Player(Vector(SCREEN_W/4, SCREEN_H/4, 0)));
   alCastle.Insert(new Castle(0));
   alScore.Insert(new Score());
   InitWalls();

   cFade = 0;
   nFadeType = 1;
   nPage = 0;

   fFinished = 0;

   //alMessage.Insert(new Message(SCREEN_W/2, SCREEN_H/2, "Get Ready", nGreen, 30, 0, 30, rgpfntFont[3]));
   alMessage.Insert(new Message(SCREEN_W/2, SCREEN_H/2, "GET READY", nGreen, 60, 30, -1, rgpfntFont[3]));

   actual_cycle = target_cycle = 0;
   frames = 0;

   for(int i=0; i<60; i++) {
      Render();

      // pause if going too fast
      while(actual_cycle >= target_cycle)
         ;
      
      // catch up if going too slow
      while(target_cycle > actual_cycle) {

         actual_cycle++;

         alMessage.Action();
         alInner.Action();
         alMiddle.Action();
         alOuter.Action();
         alSparks.Action();

         if(nFadeType != 0) {
            cFade++;
            if(cFade > cFadeLen) {
               cFade = 0;
               nFadeType++;
               if(nFadeType == 3) {
                  nFadeType = 0;
                  set_palette(palPalette);
               }
            }
         }
      }
   }
}

void EndGame(void) {

   //alMessage.Insert(new Message(SCREEN_W/2, SCREEN_H/2, "Game Over", nGreen, 30, 0, 30, rgpfntFont[3]));
//   alMessage.Insert(new Message(SCREEN_W/2, SCREEN_H/2, "GAME OVER", nGreen, 60, 30, -1, rgpfntFont[0]));

   cFade = 0;
   nFadeType = 0;
//   nPage = 0;

//   fFinished = 0;

//   actual_cycle = target_cycle = 0;
//   frames = 0;

   for(int i=0; i<60*3; i++) {
      Render();

      // pause if going too fast
      while(actual_cycle >= target_cycle)
         ;
      
      // catch up if going too slow
      while(target_cycle > actual_cycle) {

         actual_cycle++;

         alMessage.Action();
         alInner.Action();
         alMiddle.Action();
         alOuter.Action();
         alSparks.Action();

	   alShockWave.Action();
	   alExplosion.Action();
	   alShot.Action();
	   alBomb.Action();
	   alLaser.Action();
	   alCastle.Action();

	   alScore.Action();

         if(nFadeType != 0) {
            cFade++;
            if(cFade > cFadeLen) {
               cFade = 0;
               nFadeType++;
               if(nFadeType == 3) {
                  nFadeType = 0;
                  set_palette(palPalette);
               }
            }
         }
      }
   }

   alBomb.Clear();
   alPlayer.Clear();
   alCastle.Clear();
   alInner.Clear();
   alMiddle.Clear();
   alOuter.Clear();
   alSparks.Clear();
   alBomb.Clear();
   alShockWave.Clear();
   alExplosion.Clear();
   alShot.Clear();
   alScore.Clear();
   alMessage.Clear();
}

int MainLoop(void) {

   NewGame();

   int done = 0;

int gray = 0;

   while(!done) {

      Render();

      int tmp = target_cycle;
      if(fStep) {
         while(!key[KEY_ENTER])
            ;
         while(key[KEY_ENTER])
            ;
         target_cycle = tmp;
      }

      ProcessInput();

      if(key[KEY_S]) {
         while(key[KEY_S])
            ;
         if(fStep)
            fStep = 0;
         else
            fStep = 1;
      }

      if(key[KEY_SPACE]) {
         while(key[KEY_SPACE])
            ;
         if(gray) {
            set_palette(palPalette);
            gray = 0;
         }
         else {
            set_palette(palGray);
            gray = 1;
         }
      }

//done = GameLoop();

      // pause if going too fast
      while(actual_cycle >= target_cycle)
         ;

      
      done = 0;
      // catch up if going too slow
      while(target_cycle > actual_cycle)
         done += GameLoop();

      // increase in difficulty every minute

      if((timer - nDifficultyCount) > nDifficultyRate) {
         nDifficultyCount = timer;
         Escalate();
      }

      if(nFadeType != 0) {
         cFade++;
         if(cFade > cFadeLen) {
            cFade = 0;
            nFadeType++;
            if(nFadeType == 3)
               nFadeType = 0;
            if(nFadeType > 4)
               done = 1;
         }
      }
   }

   EndGame();

   return(done);
}

int main(int argc, char **argv) {

   if(argc == 2)
      fPageFlipping = atoi(argv[1]);

   Init();

   SeedRandom(time(NULL));

   int quit = 0;

   while(!quit) {
      quit = Title();
      if(!quit)
         MainLoop();
   }

   set_gfx_mode(GFX_TEXT, 80, 25, 0, 0);

   return(0);
}

END_OF_MAIN();


