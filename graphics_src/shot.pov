
#version 3.0
global_settings { assumed_gamma 2.2 }

#include "colors.inc"
#include "metals.inc"
#include "stones.inc"
#include "golds.inc"

camera {
  location <0, 0, -5>
  look_at <0, 0, 0>
  //right <4/3, 0, 0>
  right <1, 0, 0>
  up <0, 1, 0>
  sky <0, 1, 0>
  direction <0, 0, 1>
}

light_source { <0, 0, -5> color White }

#declare rr = cos(clock*pi*2.0)+1
#declare gg = cos(clock*pi*2.0+pi)+1

#declare Shot = union {
   torus {
      1, 0.3
      //pigment { color Yellow } 
      pigment { color <gg, 1, rr> }
      finish { F_MetalC }
   }
   sphere { <0, 0, 0> 0.5
      pigment { color <rr, gg, 0> }
      finish { F_MetalC }
      scale <1, 2, 1>
   }
   rotate 90*x
}

object {
   Shot
   scale <1.5, 1.5, 1.5>
   rotate y*180*clock
}

