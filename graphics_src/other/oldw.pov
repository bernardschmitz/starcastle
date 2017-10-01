
#version 3.0
global_settings { assumed_gamma 2.2 }

#include "colors.inc"
#include "metals.inc"
#include "textures.inc"

camera {
  location <0, 0, -5>
  look_at <0, 0, 0>
  right <1, 0, 0>
  up <0, 1, 0>
  sky <0, 1, 0>
  direction <0, 0, 1>
}

//#declare Damaged = 1

// 0 wall a, 1 wall b, 2 wall c
//#declare Type = 2

#switch (Type)
   #case (0)
      #declare CC = color <0.0, 0.0, 1.0>
      #declare Col = color rgbt <0.0, 0.0, 1.0, 0.75>
      #declare HiCol = color rgbt <0.6, 0.6, 1.0, 0.5>
      #declare Move = 0.0
      #break
   #case (1)
      #declare CC = color <0.0, 1.0, 0.0>
      #declare Col = color rgbt <0.0, 1.0, 0.0, 0.75>
      #declare HiCol = color rgbt <0.6, 1.0, 0.6, 0.5>
      #declare Move = 0.4
      #break
   #case (2)
      #declare CC = color <1.0, 0.0, 0.0>
      #declare Col = color rgbt <1.0, 0.0, 0.0, 0.75>
      #declare HiCol = color rgbt <1.0, 0.6, 0.6, 0.5>
      #declare Move = 0.2
      #break
#end


light_source { <0, 1, -5> color White }

#ifndef (Damaged)
light_source { <0, 0, -5> color <1, 1, 0.5, 1>*2 }
#end

#declare Size = 1.8

#declare Wall = union {

#ifndef (Damaged)
   cylinder { <-Size, 0, 0> <Size, 0, 0> 0.5
      pigment {
         spiral1 1
         color_map {
            [ 0, 0.15 color rgbt <1, 1, 1, 0.5> color HiCol ]
            [ 0.15, 0.25 color HiCol color Col ]
            [ 0.25, 0.5 color Col color rgbt <1, 1, 1, 1> ]
            [ 0.5, 1 color rgbt <1, 1, 1, 1> color rgbt <1, 1, 1, 1> ]
         }
         turbulence 0.25
         rotate y*clock*-360
         translate y*Move
      }
      finish { ambient 1 }
   }

#end

   cylinder { <-Size, 0, 0> <Size, 0, 0> 0.25 }
   sphere { <-Size, 0, 0> 0.6 }
   sphere { <Size, 0, 0> 0.6 }

   pigment {
      marble
      color_map {
         [ 0.0 color CC ]
         [ 0.1 color CC*0.3 ]
         [ 1.0 color White*0.5 ]
      }
      turbulence 2
      rotate x*clock*-360
   }

   finish { F_MetalD }
}

object {
   Wall
   rotate z*360*clock
}


