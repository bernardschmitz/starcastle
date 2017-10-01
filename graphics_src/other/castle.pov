//  Persistance of Vision Raytracer V3.0
//  World definition file.
//
//  Contains 1 lights, 4 textures and 20 primitives.
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
  location  <0.000, -0.001, 8.000>
  direction <0.0,     0.0,  1.1547>
  sky       <0.0,     0.0,  1.0>  // Use right handed-system!
  up        <0.0,     0.0,  1.0>  // Where Z is up
  right     <1.33333,  0.0,  0.0>
  look_at   <0.000, 0.000, 0.000>
}

//
// *******  L I G H T S *******
//

light_source {   // Light001
  <0.000, 0.000, 10.000>
  color rgb <1.000, 1.000, 1.000>
}


//
// ********  TEXTURES  *******
//

#include "castle.inc"


//
// ********  REFERENCED OBJECTS  *******
//



//
// ********  OBJECTS  *******
//



#declare CockpitPart = union {
  torus { // CockpitRing1
    0.6, 0.05  rotate -x*90
    texture {
      T_Chrome_2C
    }
    scale <1.0, 0.8, 1.3>
    rotate <-90.0, -0.0, -60.0>
    translate  <-0.2, -0.6, 0.0>
  }
  torus { // CockpitRing2
    0.6, 0.05  rotate -x*90
    texture {
      T_Chrome_2C
    }
    scale <1.0, 0.8, 1.3>
    rotate <-90.0, -0.0, 60.0>
    translate  <0.2, -0.6, 0.0>
  }
  torus { // CockpitRing
    0.692, 0.106  rotate -x*90
    texture {
      T_Chrome_2C
    }
    scale <1.0, 0.8, 1.3>
    rotate -45.0*x
    translate  -0.5*y
  }
  sphere { // Cockpit
    <0,0,0>,1
    texture {
      Polished_Brass
    }
    scale <0.7, 0.7, 0.5>
    translate  -0.5*y
  }
  torus { // Swivel
    0.7, 0.2  rotate -x*90
    texture {
      my_Blood_Marble
    }
    scale <1.0, 1.0, 0.5>
    translate  -0.2*z
  }
}
#declare LeftEnginePart = union {
  cone { // LeftEnginePoint
    <0,0,0>, 0.0, <0,0,1>, 1.0
    texture {
      T_Chrome_3D
    }
    scale <0.15, 0.1, 0.8>
    rotate 90.0*x
    translate  <-1.15, 1.1, 0.0>
  }
  cone { // LeftPoint
    <0,0,0>, 0.0, <0,0,1>, 1.0
    texture {
      T_Chrome_3D
    }
    scale <0.4, 0.2, 1.1>
    rotate <100.0, 0.0, 120.0>
    translate  <-2.1, -1.3, 0.2>
  }
  cone { // LeftEngine
    <0,0,0>, 0.2, <0,0,1>, 0.3
    texture {
      T_Chrome_3D
    }
    scale <1.0, 1.0, 1.5>
    rotate <90.0, 0.0, -10.0>
    translate  <-1.1, 0.6, 0.0>
  }
}
#declare RightEnginePart = union {
  cone { // RightEnginePoint
    <0,0,0>, 0.0, <0,0,1>, 1.0
    texture {
      T_Chrome_3D
    }
    scale <0.15, 0.1, 0.8>
    rotate 90.0*x
    translate  <1.15, 1.1, 0.0>
  }
  cone { // RightEngine
    <0,0,0>, 0.2, <0,0,1>, 0.3
    texture {
      T_Chrome_3D
    }
    scale <1.0, 1.0, 1.5>
    rotate <90.0, 0.0, 10.0>
    translate  <1.1, 0.6, 0.0>
  }
  cone { // RightPoint
    <0,0,0>, 0.0, <0,0,1>, 1.0
    texture {
      T_Chrome_3D
    }
    scale <0.4, 0.2, 1.1>
    rotate <100.0, -0.0, -120.0>
    translate  <2.1, -1.3, 0.2>
  }
}
#declare LeftBackWingPart = union {
  sphere { // LeftEngineSphere
    <0,0,0>,1
    texture {
      Polished_Brass
    }
    scale 0.4
    translate  <-1.0, -1.3, 0.0>
  }
  cone { // LeftWing
    <0,0,0>, 0.3, <0,0,1>, 0.5
    texture {
      my_Blood_Marble
    }
    rotate <90.0, 0.0, -45.0>
    translate  <-0.3, -0.6, 0.0>
  }
}
#declare RightBackWingPart = union {
  sphere { // RightEngineSphere
    <0,0,0>,1
    texture {
      Polished_Brass
    }
    scale 0.4
    translate  <1.0, -1.3, 0.0>
  }
  cone { // RightWing
    <0,0,0>, 0.3, <0,0,1>, 0.5
    texture {
      my_Blood_Marble
    }
    rotate <90.0, -0.0, 45.0>
    translate  <0.3, -0.6, 0.0>
  }
}
#declare BigGun = union {
  cone { // Fuselage
    <0,0,0>, 0.15, <0,0,1>, 0.5
    texture {
      my_Blood_Marble
    }
    scale <1.0, 0.6, 3.3>
    rotate 90.0*x
    translate  2.478286*y
  }
  cone { // RightGun
    <0,0,0>, 0.0, <0,0,1>, 0.1
    texture {
      T_Chrome_3D
    }
    rotate <90.0, 0.0, -145.0>
    translate  <0.5, 1.8, 0.0>
  }
  cone { // LeftGun
    <0,0,0>, 0.0, <0,0,1>, 0.1
    texture {
      T_Chrome_3D
    }
    rotate <90.0, 0.0, 145.0>
    translate  <-0.5, 1.8, 0.0>
  }
  cone { // Gun
    <0,0,0>, 0.0, <0,0,1>, 0.1
    texture {
      T_Chrome_3D
    }
    rotate 90.0*x
    translate  3.2*y
  }
}
union { // StarCastle
  object { CockpitPart }
  object { LeftEnginePart }
  object { RightEnginePart }
  object { LeftBackWingPart }
  object { RightBackWingPart }
  object { BigGun }
}


