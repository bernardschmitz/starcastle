
// $Id: makegrid.cc,v 1.2 2002-01-20 21:20:13 bernard Exp $

#include <stdio.h>
#include <stdlib.h>

#include <allegro.h>

int main(int argc, char **argv) {

   if(argc < 7) {
      fprintf(stderr, "usage: makegrid width height columns rows infile outfile\n");
      exit(1);
   }

   int w = atoi(argv[1]);
   int h = atoi(argv[2]);
   int r = atoi(argv[3]);
   int c = atoi(argv[4]);

   allegro_init();
   set_color_depth(24);
   set_color_conversion(COLORCONV_NONE);

   PALETTE pal;

   printf("Making %d %d image\n", w*c, h*r);
   BITMAP *grid = create_bitmap(w*c, h*r);

   for(int y=0; y<r; y++) {
      for(int x=0; x<c; x++) {
         char infile[80];
         sprintf(infile, argv[5], x+y*c);

         printf("Reading image %s\n", infile);
         BITMAP *bm = load_bitmap(infile, pal);

         printf("Blitting image %d %d\n", x*w, y*h);
         blit(bm, grid, 0, 0, x*w, y*h, w, h);

         destroy_bitmap(bm);
      }
   }

   printf("Writing image %s\n", argv[6]);
   save_bitmap(argv[6], grid, pal);

   return(0);
}

/*

$save = "exp01";

$n = 30;

$tw = 128;
$th = 128;

$w = 6;
$h = 5;

$name = "exp01";
$num  = 0;

printf("tl %s%02d\nrescale %d %d\n\n", $name, $num, $w*$tw, $h*$th);

for($y=0; $y<$h; $y++) {
   for($x=0; $x<$w; $x++) {
      printf("tl %s%02d\noverlay %d %d\n", $name, $num, $x*$tw, $y*$th);
      $num++;
   }
}

printf("\nts %s\n", $save);

*/

