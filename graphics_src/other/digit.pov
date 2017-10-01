
#include "colors.inc"
#include "sc.inc"

background { color <0.000,0.000,0.000> }

camera {
  location  <0.0, 0, -2>
//  location  <2.0, 2, -2>
  direction <0.0,     0.0,  1.0>
  sky       <0.0,     1.0,  0.0> 
  up        <0.0,     1.0,  0.0>
  right     <1,  0.0,  0.0>
  look_at   <0, 0, 0>
}

light_source { <-5, 10, -10> color White }

#declare Letter = text {

    ttf      "C:\WINDOWS\Fonts\Bauhs93.ttf",
    chr(clock*95+32), // "A",
    0.1,  
    <0.0, 0.0, 0.0> 
}

object {
   Letter
   texture { my_Blood_Marble finish { ambient 0.5 } }
   scale 2
//   rotate <0, 25, 0>
   translate <-0.6, -0.5, 0>
}

box { <-.65, 1, 0> <.85, -1, 1> pigment { color White } finish { ambient 1 diffuse 1 } }

