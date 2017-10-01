//  Persistance of Vision Raytracer V3.0
//  World definition file.
//
//  Contains 1 lights, 1 textures and 17 primitives.
//
//  This file was generated for POV-Ray V3.0 by
//  Moray V3.01 For Windows (c) 1991-1998 Lutz + Kretzschmar
//

//  Date : 08/03/1998    (03.08.1998)
//

/*
  The text between these two comments is in MorayPOV.INC and is
  automatically included in all POV files that Moray exports.
*/

/* // Scene Comment

This scene was created with Moray For Windows.

*/ // End Scene Comment

global_settings {
  adc_bailout 0.003922
  ambient_light <1.0,1.0,1.0>
  assumed_gamma 1.9
  hf_gray_16 off
  irid_wavelength <0.247059,0.176471,0.137255>
  max_intersections 64
  max_trace_level 10
  number_of_waves 10
/*
  radiosity {
    brightness       3.3
    count            100
    distance_maximum 0.0
    error_bound      0.4
    gray_threshold   0.5
    low_error_factor 0.8
    minimum_reuse    0.015
    nearest_count    6
    recursion_limit  1
  }
*/
}

background { color <0.000,0.000,0.000> }

camera {  //  Camera StdCam
  location  <0.000, -10.000, 0.000>
  direction <0.0,     0.0,  1.8317>
  sky       <0.0,     0.0,  1.0>  // Use right handed-system!
  up        <0.0,     0.0,  1.0>  // Where Z is up
//  right     <1.33333,  0.0,  0.0>
right <1, 0, 0>
  look_at   <0.000, 0.000, 0.000>
}

//
// *******  L I G H T S *******
//

light_source {   // Light1
  <0.000, -10.000, 0.000>
  color rgb <1.000, 1.000, 1.000>
}


//
// ********  TEXTURES  *******
//

//#include "wall.inc"
#include "colors.inc"
#include "sc.inc"


//
// ********  REFERENCED OBJECTS  *******
//

#declare Damaged = 0
#declare GenPos  = sin(2*clock*pi*2)*0.75

//
// ********  OBJECTS  *******
//

#declare Generator = union {
  cone { // Cone6
    <0,0,0>, 0.0, <0,0,1>, 1.0
    scale <0.125, 0.125, 0.5>
    texture { T_Chrome_3D }
    rotate -0.0*y
    translate  -0.9*z
  }
  cone { // Cone5
    <0,0,0>, 0.0, <0,0,1>, 1.0
    scale <0.125, 0.125, 0.5>
    texture { T_Chrome_3D }
    rotate 90.0*y
    translate  -0.9*x
  }
  cone { // Cone4
    <0,0,0>, 0.0, <0,0,1>, 1.0
    scale <0.125, 0.125, 0.5>
    texture { T_Chrome_3D }
    rotate <180.0, 0.0, 180.0>
    translate  0.9*z
  }
  cone { // Cone003
    <0,0,0>, 0.0, <0,0,1>, 1.0
    scale <0.125, 0.125, 0.5>
    texture { T_Chrome_3D }
    rotate -90.0*y
    translate  0.9*x
  }
  torus { // Torus004
    1.5, 0.5  rotate -x*90
    scale 0.25
    rotate -90.0*x
    texture { Polished_Brass }
  }
  rotate <0.0, 45.0, 0.0>
}
#declare InnerPart = union {
  torus { // Torus2
    1.5, 0.5  rotate -x*90
    scale 0.25
    rotate -90.0*x
    translate  -2.0*z
  }
  torus { // Torus001
    1.5, 0.5  rotate -x*90
    scale 0.25
    rotate -90.0*x
    translate  2.0*z
  }
  cone { // Cone2
    <0,0,0>, 0.0, <0,0,1>, 1.0
    scale <0.125, 0.1, 0.5>
    texture { Polished_Brass }
    rotate <-0.0, -90.0, 0.0>
    translate  <0.9, 0.0, -2.0>
  }
  cone { // Cone001
    <0,0,0>, 0.0, <0,0,1>, 1.0
    scale <0.125, 0.1, 0.5>
    texture { Polished_Brass }
    rotate <-0.0, -90.0, 0.0>
    translate  <0.9, 0.0, 2.0>
  }
  cone { // Cone002
    <0, 0, GenPos-.2>, 0.25, <0, 0, -1.7>, 0.1
    //<0,0,0>, 0.1, <0,0,1>, 0.25
    //scale <1.0, 1.0, 1.3+0.75*GenPos/0.75>
    //translate  <0, 0, -1.6+GenPos>
  }
  cone { // Cone3
    <0, 0, GenPos+.2>, 0.25, <0, 0, 1.7>, 0.1
    //<0,0,0>, 0.25, <0,0,1>, 0.1
    //scale <1.0, 1.0, 1.3+0.75*GenPos/0.75>
    //translate  <0, 0, 0.3+GenPos>
  }
  sphere {
    <0, 0, GenPos>, 0.125
    texture { T_Chrome_2C }
  }
  object { Generator rotate y*clock*360 translate <0, 0, GenPos> }
  texture { my_Blood_Marble }
}
#declare CSG001 = difference {
  torus { // Torus003
    2.0, 0.125  rotate -x*90
    rotate -90.0*x
    translate  -0.73*x
  }
  plane { // Plane001
    z,0
    rotate 45.0*y
    translate  <0.5, 0.0, -1.6>
  }
  plane { // Plane002
    z,0
    rotate <180.0, 45.0, 180.0>
    translate  <0.5, 0.0, 1.5>
  }
  rotate <0.0, -0.0, 0.0>
}
#declare OuterPart = union {
  torus { // Torus002
    1.5, 0.5  rotate -x*90
    scale 0.25
    rotate 45.0*y
    translate  <0.25, 0.0, 1.75>
  }
  torus { // Torus3
    1.5, 0.5  rotate -x*90
    scale 0.25
    rotate <0.0, -45.0, 0.0>
    translate  <0.25, 0.0, -1.75>
  }
  object { CSG001 }
  texture { T_Chrome_2C }
  rotate 0.0*z
}

union { // Wall
  object { InnerPart }
#if (Damaged = 0)
  object { OuterPart }
#end
  //texture { my_Blood_Marble }
  rotate y*clock*-360
}




