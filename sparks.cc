
// $Id: sparks.cc,v 1.2 2002-01-20 21:20:13 bernard Exp $

#include <stdio.h>
#include <allegro.h>

#include "init.h"
#include "sparks.h"
#include "random.h"
#include "trig.h"
#include "vector.h"

ActorList<Sparks> alSparks;

Particle *Bitmap2Particle(BITMAP *pbm, int step, int &n, const Vector &vP, const Vector &vV, float mins, float maxs, int mina, int maxa, int c, int mini, int maxi) { 

   int cBits = 0;

   for(int y=0; y<pbm->h; y+=step) {
      for(int x=0; x<pbm->w; x+=step) {
         if(_getpixel(pbm, x, y) != 0)
            cBits++;
      }
   }

   Particle *p = new Particle[cBits];

   int i = 0;
   for(int y=0; y<pbm->h; y+=step) {
      for(int x=0; x<pbm->w; x+=step) {
         int pix = _getpixel(pbm, x, y);
         if(pix != 0) {

            float rS = (float)(Random(1000)/1000.0)*(maxs-mins)+mins;
            int nA = mina + Random(maxa-mina);
            int nI = mini + Random(maxi-mini);

            p[i++] = Particle(vP+Vector(x, y, 0),
                       vV+Vector(Cos[Random(4096)], Sin[Random(4096)], 0)*rS,
                       nA, lites.data[nI][c==0?pix:c]);
 
         }


      }
   }

   n = cBits;

   return(p);
}

Sparks::Sparks(BITMAP *pbm, int step, const Vector &vP, const Vector &vV, float mins, float maxs, int mina, int maxa, int c, int mini, int maxi) : Actor(0, 0, 0, 0) {

   ps = Bitmap2Particle(pbm, step, nParticles, vP, vV, mins, maxs, mina, maxa, c, mini, maxi);

   fAlloc = 1;
}


Sparks::Sparks(int n, Particle *p) : Actor(0, 0, 0, 0) {

   fAlloc = 0;

   nParticles = n;
   ps = p;
}

Sparks::Sparks(int n, const Vector &vP, const Vector &vV, float mins, float maxs, int mina, int maxa, int c, int mini, int maxi) : Actor(0, 0, 0, 0) {

   fAlloc = 1;

   nParticles = n;
   ps = new Particle[nParticles];

   for(int i=0; i<nParticles; i++) {

      float rS = (float)(Random(1000)/1000.0)*(maxs-mins)+mins;
      int nA = mina + Random(maxa-mina);
      int nI = mini + Random(maxi-mini);

      ps[i] = Particle(vP,
                       vV+Vector(Cos[Random(4096)], Sin[Random(4096)], 0)*rS,
                       nA, lites.data[nI][c]);
   }
}

Sparks::~Sparks() {

   if(fAlloc) {
      delete [] ps;
   }
}

void Sparks::Action(void) {

   int fAlive = 0;

   // update all particles
   for(int i=0; i<nParticles; i++) {
      ps[i].nLife--;
      if(ps[i].nLife > 0) {
         ps[i].vOldPos = ps[i].vPos;
         ps[i].vPos += ps[i].vVel;
         fAlive = 1;
      }
      else
         ps[i].nLife = 0;
   }

   // if all particles dead, then kill this actor
   if(!fAlive)
      fFlags |= ACT_DEL;
}

void Sparks::Erase(int nPage) {

   blit(pbmBackground, pbmPage[nPage], rgrtDirty[nPage].sx, rgrtDirty[nPage].sy, rgrtDirty[nPage].sx, rgrtDirty[nPage].sy, 
        rgrtDirty[nPage].ex-rgrtDirty[nPage].sx+1, rgrtDirty[nPage].ey-rgrtDirty[nPage].sy+1);
}

void Sparks::Draw(int nPage) {

   int xmin = SCREEN_W-1;
   int ymin = SCREEN_H-1;
   int xmax = 0;
   int ymax = 0;

   // draw a line for each living particle
   // calculating bounding box
   for(int i=0; i<nParticles; i++) {

      if(ps[i].nLife > 0) {

         int sx = (int)ps[i].vPos.x;
         int sy = (int)ps[i].vPos.y;
         int ex = (int)ps[i].vOldPos.x;
         int ey = (int)ps[i].vOldPos.y;

         if(sx < xmin)
            xmin = sx;
         if(sy < ymin)
            ymin = sy;

         if(sx > xmax)
            xmax = sx;
         if(sy > ymax)
            ymax = sy;

         if(ex < xmin)
            xmin = ex;
         if(ey < ymin)
            ymin = ey;

         if(ex > xmax)
            xmax = ex;
         if(ey > ymax)
            ymax = ey;

         line(pbmPage[nPage], ex, ey, sx, sy, lites.data[ps[i].nLife*255/ps[i].nAge][ps[i].nColor]);
      }
   }

   rgrtDirty[nPage].sx = xmin;
   rgrtDirty[nPage].sy = ymin;
   rgrtDirty[nPage].ex = xmax;
   rgrtDirty[nPage].ey = ymax;

//rect(pbmPage[nPage], rgrtDirty[nPage].sx, rgrtDirty[nPage].sy, rgrtDirty[nPage].ex, rgrtDirty[nPage].ey, nWhite);
}

