
// $Id: exp06.pov,v 1.1 2002-05-09 02:17:17 bernard Exp $

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
#declare Samples = 5

#declare Size = sin(clock*3.14159/2)*1.5 + .2

#declare cc = (clock<.25)*1+(clock>=.25)*(1-(clock-.25)/.75);

#declare Halo = media {
   emission 1.5
   density {
      spherical
      color_map {
         [0.0 rgb <cc, 0, 0>*0.0]
         [0.25 rgb <cc, cc, 0>*0.25]
         [0.5 rgb <cc, 0, 0>*0.5]
         [0.75 rgb <cc, cc, 0>*0.75]
         [1.0 rgb <cc, 0, 0>*1.0]
      }
      turbulence Turbulence
      scale Size
   }
   samples 10, 10
}

#declare Exp_Tex = 
texture {
   pigment { color rgbt 1 }
   finish { ambient 0 diffuse 0 }
}

sphere {
   <0, 0, 0> 2.2 hollow no_shadow
   texture { Exp_Tex } 
   interior { media { Halo } }
   rotate <clock*-90, clock*18, clock*36>
}

#declare Halo1 = media {
   emission 1.5
   density {
      spherical
      color_map {
         [0.0 rgb <cc, 0, 0>*0.0]
         [0.25 rgb <cc, cc, 0>*0.5]
         [0.5 rgb <cc, 0, 0>*0.5]
         [0.75 rgb <cc, cc, 0>*0.75]
         [1.0 rgb <cc, 0, 0>*1.0]
      }
      turbulence Turbulence*1.2
      scale Size*.9
   }
   samples 10, 10
}

#declare Exp_Tex = 
texture {
   pigment { color rgbt 1 }
   finish { ambient 0 diffuse 0 }
}

sphere {
   <0, 0, 0> 2.1 hollow no_shadow
   texture { Exp_Tex } 
   interior { media { Halo1 } }
   rotate <clock*72, clock*-13, clock*45>
}


