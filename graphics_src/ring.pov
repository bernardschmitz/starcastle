
#version 3.0
global_settings { assumed_gamma 2.2 }

#include "colors.inc"

camera {
  location <0, 0, -5>
  look_at <0, 0, 0>
  right <1, 0, 0>
  up <0, 1, 0>
  sky <0, 1, 0>
  direction <0, 0, 1>
}

light_source { <0, 0, -5> color White }

/*

cylinder {
   <0, 0, 0>
   <0, 0, 1> 2.2
   pigment { White }
}

*/

#declare Size = clock*22
#declare Width = clock*4+4

#declare Color = (clock<=0.6)*1 + (clock>0.6)*(1-(clock-0.6)/.4)

rainbow {
   angle Size
   width Width 
   distance 10
   direction <0, 0, 1>
   jitter 0.01
   color_map {
      [ 0.0 color rgbt <0, 0, 0, 1> ]
      [ 1.0 color rgbt <Color, Color, Color, 0> ]
   }
}

