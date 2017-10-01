
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

#declare Turbulence = (1-clock)*0+clock*2
#declare Freq = (1-clock)*2+clock*.5
#declare Samples = 5

#declare Size = sin(clock*3.14159/2)*1.5 + .2

#declare cc = (clock<.25)*1+(clock>=.25)*(1-(clock-.25)/.75)

#declare Halo = halo {
   linear
   spherical_mapping
   emitting
   max_value 1
   color_map
   {
      [0.0 color rgbt<cc, 0, 0, 1>]
      [0.5 color rgbt<cc, cc, 0, -1>]
      [1.0 color rgbt<cc, 0, 0, 1>]
//      [1.0 color rgbt<cc, cc, 0, -1>]
   }
//   frequency Freq
   turbulence Turbulence
   samples Samples
   aa_level 3
   aa_threshold 0.3
   scale Size
}

#declare Exp_Tex = 
texture {
   pigment { color Clear }
   finish { ambient 0 diffuse 0 }
   halo { Halo }
}

sphere {
   <0, 0, 0> 2.2 hollow
   //pigment { White }
   texture { Exp_Tex } 
   rotate <56, -89, -34>
   rotate <clock*45, clock*-92, clock*-26>
}

