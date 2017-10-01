
//#declare frm = 0

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

#switch (clock)
   #range (0, 0.25)
      #declare Trad = 0.02+(clock/0.25)*0.06
      #declare Srad = 0.0
      #declare Tscl = 1.0
      #declare Pos  = 0.3
      #declare Recoil = 0.0
      #break
   #range (0.25, 0.35)
      #declare Trad = 0.08
      #declare Srad = (clock-0.25)/0.1*0.1
      #declare Tscl = (clock-0.25)/0.1*1+1.0
      #declare Pos  = 0.3+(clock-0.25)/0.1*0.6
      #declare Recoil = sin((clock-0.25)/0.1*pi/2)*-0.15
      #break
   #else
      #declare Trad = 0.08
      #declare Srad = 0.1
      #declare Tscl = 2.0
      #declare Pos  = 0.9+(clock-0.35)/0.65*0.3
      #declare Recoil = -0.075-cos((clock-0.35)/0.65*pi)*0.075 
      #break
#end

#declare Shot = union {
   torus {
      Trad, 0.05
      pigment { color Yellow } 
      finish { F_MetalC }
      scale <1, 1, Tscl>
   }
   sphere { <0, 0, 0> Srad
      pigment { color Red }
      finish { F_MetalC }
   }

   scale 0.75
   rotate 90*x
//   rotate -90*180*clock*y
   translate y*Pos
}

light_source {
   <0, 0, -1.0>
   color <(1-clock)*2, (1-clock)*2, 0>
   rotate frm/32*360*z
   translate y*(Pos+.2)
}


#declare Ship = merge {

   // wings
   merge {
      cone { <0, 0, 0> .15 <0, 1.1, 0> 0 rotate (140+Recoil*25*0)*z }
      cone { <0, 0, 0> .15 <0, 1.1, 0> 0 rotate (-140-Recoil*25*0)*z }
      //pigment { color Gray75 }
      texture { T_Stone22 scale <0.3, 0.3, 0.3> }
   }

   // fuselage
   merge {
      cone { <0, 0+Recoil*1.5, 0> .1 <0, 1.25+Recoil*1.5, 0> 0 rotate -10*z translate <-0.3, -.5, 0> }
      cone { <0, 0+Recoil*1.5, 0> .1 <0, 1.25+Recoil*1.5, 0> 0 rotate 10*z  translate <0.3, -.5, 0> }
      //pigment { color White }
      texture { T_Silver_3C }
      //translate y*Recoil*1
   }

   // thrusters
   merge {
      cone { <0, 0+Recoil*1.5, 0> .08 <0, -.05+Recoil*1.5, 0> .15 rotate -10*z translate <-0.3, -.5, 0> }
      cone { <0, 0+Recoil*1.5, 0> .08 <0, -.05+Recoil*1.5, 0> .15 rotate 10*z translate <0.3, -.5, 0> }
      //pigment { color Gray50 } 
      texture { T_Chrome_3B }
      //translate y*Recoil
   }

   // cockpit
   sphere { <0, 0, 0> 0.2 texture { T_Brass_4B } }
   torus { 0.2, 0.05 texture { T_Copper_2C } rotate -45*x }
   torus { 0.2, 0.025 texture { T_Copper_2C } rotate 90*z }

   // gun
   cone { <0, 0, 0> .15 <0, 0.4, 0> 0
      //pigment { color Gray50 }
      texture { T_Gold_4A }
      translate y*Recoil/2
   }

   // shooting animation

#if (clock<0.35)
   object { Shot }
#end
}


object {
   Ship
   scale <2.25, 2.25, 2.25>
   //rotate clock*360*z
   rotate frm/32*360*z
}

