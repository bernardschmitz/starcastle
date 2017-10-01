
#version 3.0
global_settings { assumed_gamma 2.2 }

#include "colors.inc"
#include "metals.inc"
//#include "stones.inc"
//#include "golds.inc"

//#include "sc.inc"

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

#declare lite = cos(clock*pi*2.0)+1
#declare pwrc = cos(pi+clock*pi*2.0)+1



#declare PowerCells = texture {
   pigment { color <0.75+pwrc, 0.5+pwrc, 0+pwrc+lite> }
   finish {
      ambient 0.15
      brilliance 5.0
      specular 0.8
      roughness 0.01
      reflection 0.65
   }
}






#declare Shot = union {

light_source { <0, 0, -4> color <lite, lite, lite*4> }

   sphere { <0, 0, 0> 0.5+clock*1.25
      pigment { color rgbt <lite, lite, pwrc, 0.25+clock*0.75> }
      //finish { ambient 0 diffuse 1 }
      //finish { F_MetalC }
   }
   sphere { <0, 0, 0> 0.6
      texture { PowerCells }
   }
   union {
      cone { <0, 0, 0>, 0.4 <2, 0, 0>, 0 }
      cone { <0, 0, 0>, 0.4 <-2, 0, 0>, 0 }
      cone { <0, 0, 0>, 0.4 <0, 2, 0>, 0 }
      cone { <0, 0, 0>, 0.4 <0, -2, 0>, 0 }
      //cone { <0, 0, 0>, 0.4 <0, 0, 2>, 0 }
      //cone { <0, 0, 0>, 0.4 <0, 0, -2>, 0 }
      //pigment { color <gg, gg, 1+gg>*2 }
      //finish { F_MetalC }
      texture { PowerCells }
   }
}

object {
   Shot
   scale <1.2, 1.2, 1.2>
   rotate <0, 0, 180*clock>
}

