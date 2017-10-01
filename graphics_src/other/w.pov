
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

//#declare Damaged = 0


light_source { <0, 1, -10> color White }


#declare W = 0.5
#declare Size = 1.8 + 0.6 - W

#declare Wall = union {

#if (Damaged = 0)
   cylinder { <-Size, 0, 0> <Size, 0, 0> W*0.75 }
   sphere { <-Size, 0, 0> W }
   sphere { <Size, 0, 0> W }
   texture { my_Blood_Marble }
#else
   union {
      cylinder { <-Size, 0, 0> <Size, 0, 0> W*0.75*0.5 }
      sphere { <-Size, 0, 0> W*0.5 }
      sphere { <Size, 0, 0> W*0.5 }
      texture {
         Polished_Brass
      }
   }
   union {
      cylinder { <-Size, 0, 0> <Size, 0, 0> W*0.75 }
      sphere { <-Size, 0, 0> W }
      sphere { <Size, 0, 0> W }
      texture {
         gradient x
         texture_map {
            [0.2 my_Blood_Marble ]
            [0.3 pigment { color rgbt <1, 1, 1, 1> } ]
            [0.7 pigment { color rgbt <1, 1, 1, 1> } ]
            [0.8 my_Blood_Marble ]
         }
         turbulence 0.75
         scale 0.5
      }
   }
#end
}

object {
   Wall
   rotate z*360*clock
}


