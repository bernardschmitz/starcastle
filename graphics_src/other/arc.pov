
#version 3.0
global_settings { assumed_gamma 2.2 }

#include "colors.inc"

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

#declare Arc = union {

#declare R1 = seed(clock*100)

#declare Sx = -2
#declare Ex = 2
#declare Width = 0.1
#declare Num = 10


#declare X = Sx
#declare Dx = (Ex - Sx) / Num

#declare sd1 = 0

   sphere { <X, sd1, 0> Width }

#while (X < Ex-Dx)
   #declare sd2 = (0.5-rand(R1))/1
   cylinder { <X, sd1, 0> <X+Dx, sd2, 0> Width }
   #declare X = X+Dx
   #declare sd1 = sd2
   sphere { <X, sd1, 0> Width }
#end

   cylinder { <X, sd1, 0> <X+Dx, 0, 0> Width }
   sphere { <X+Dx, 0, 0> Width }
   
   pigment { color rgbt <0.5, 0.5, 1, 1*0.5> }
   finish { ambient 1-0*1/2 diffuse 1 }
}


object {
   Arc
}

