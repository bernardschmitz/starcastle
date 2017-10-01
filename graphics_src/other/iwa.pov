
#version 3.0
global_settings { assumed_gamma 2.2 }

#include "colors.inc"
#include "metals.inc"
#include "textures.inc"

#include "castle.inc"

camera {
  location <0, 0, -5>
  look_at <0, 0, 0>
  right <1, 0, 0>
  up <0, 1, 0>
  sky <0, 1, 0>
  direction <0, 0, 1>
}

#declare Damaged = 0


light_source { <0, 0, -5> color White }


#declare W = 0.5
#declare Size = 1.8 + 0.5 - W

#declare Wall = union {
   union {
      cylinder { <-Size, 0, 0> <Size, 0, 0> W }
      sphere { <-Size, 0, 0> W }
      sphere { <Size, 0, 0> W }
#if (Damaged = 1)
      texture { T_Chrome_3D }
#else
      texture { Polished_Brass }
#end
   }
   rotate z*90
}

object {
   Wall
   rotate z*360*clock
}


