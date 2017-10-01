
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

#declare Ship = merge {

   // wings
   merge {
      cone { <0, 0, 0> .15 <0, 1.1, 0> 0 rotate 140*z }
      cone { <0, 0, 0> .15 <0, 1.1, 0> 0 rotate -140*z }
      //pigment { color Gray75 }
      texture { T_Stone22 scale <0.3, 0.3, 0.3> }
   }

   // fuselage
   merge {
      cone { <0, 0, 0> .1 <0, 1.25, 0> 0 rotate -10*z translate <-0.3, -.5, 0> }
      cone { <0, 0, 0> .1 <0, 1.25, 0> 0 rotate 10*z  translate <0.3, -.5, 0> }
      //pigment { color White }
      texture { T_Silver_3C }
   }

   // thrusters
   merge {
      cone { <0, 0, 0> .08 <0, -.05, 0> .15 rotate -10*z translate <-0.3, -.5, 0> }
      cone { <0, 0, 0> .08 <0, -.05, 0> .15 rotate 10*z translate <0.3, -.5, 0> }
      //pigment { color Gray50 } 
      texture { T_Chrome_3B }
   }

   // cockpit
   sphere { <0, 0, 0> 0.2 texture { T_Brass_4B } }
   torus { 0.2, 0.05 texture { T_Copper_2C } rotate -45*x }
   torus { 0.2, 0.025 texture { T_Copper_2C } rotate 90*z }

   // gun
   cone { <0, 0, 0> .15 <0, 0.4, 0> 0
      //pigment { color Gray50 }
      texture { T_Gold_4A }
   }
}

object {
   Ship
   scale <2.25, 2.25, 2.25>
   rotate clock*360*z
}

