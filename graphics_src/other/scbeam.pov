//  Persistance of Vision Raytracer V3.0
//  World definition file.
//
//  Contains 0 lights, 1 textures and 1 primitives.
//
//  This file was generated for POV-Ray V3.0 by
//  Moray V3.01 For Windows (c) 1991-1998 Lutz + Kretzschmar
//

//  Date : 08/01/1998    (01.08.1998)
//

/*
  The text between these two comments is in MorayPOV.INC and is
  automatically included in all POV files that Moray exports.
*/

/* // Scene Comment

This scene was created with Moray V3.01 For Windows.

*/ // End Scene Comment

global_settings {
  adc_bailout 0.003922
  ambient_light <1.0,1.0,1.0>
  assumed_gamma 1.8
  hf_gray_16 off
  irid_wavelength <0.247059,0.176471,0.137255>
  max_intersections 64
  max_trace_level 10
  number_of_waves 10
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
}

background { color <0.000,0.000,0.000> }

camera {  //  Camera Camera01
  location  <0.000, -10.000, 0.000>
  direction <0.0,     0.0,  2.4880>
  sky       <0.0,     0.0,  1.0>  // Use right handed-system!
  up        <0.0,     0.0,  1.0>  // Where Z is up
  right     <1.33333,  0.0,  0.0>
  look_at   <0.000, 0.000, 0.000>
}


//
// ********  TEXTURES  *******
//

#include "scbeam.inc"


//
// ********  REFERENCED OBJECTS  *******
//



//
// ********  OBJECTS  *******
//

cylinder { // Cylndr001
  <0,0,1>, <0,0,0>, 1 
  texture {
    Beam
  }
  scale <1.0, 1.0, 3.0>
  translate  -1.5*z
}


