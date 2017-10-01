
// Persistence of Vision Ray Tracer Scene Description File
// File: test.pov
// Vers: 3
// Desc: speed test file
// Date: 25th July 1998
// Auth: Bernard Schmitz


// ==== Standard POV-Ray Includes ====
#include "colors.inc"	// Standard Color definitions
#include "textures.inc"	// Standard Texture definitions
#include "metals.inc"


camera
{
  location  <2.0 , 2.0 ,-5.0>
  look_at   <0.0 , 0.0 , 0.0>
}


// Create an infinite sphere around scene and allow any texture on it
sky_sphere
{
  pigment
  {
    gradient y
    color_map { [0.0 color Blue*0.6] [1.0 color Blue] }
  }
  
}


// An area light (creates soft shadows)
// WARNING: This special light can significantly slow down rendering times!
light_source
{
  0*x // light's position (translated below)
  color rgb 1.0  // light's color
  // <widthVector> <heightVector> nLightsWide mLightsHigh
  area_light
  <8, 0, 0> <0, 0, 8> // lights spread out across this distance (x * z)
  4, 4                // total number of lights in grid (4x*4z = 16 lights)
  adaptive 0          // 0,1,2,3... 
  jitter              // adds random softening of light
  translate <4, 10, -4>   // <x y z> position of light
}

light_source
{
  0*x // light's position (translated below)
  color rgb 0.5  // light's color
  // <widthVector> <heightVector> nLightsWide mLightsHigh
  area_light
  <8, 0, 0> <0, 0, 8> // lights spread out across this distance (x * z)
  4, 4                // total number of lights in grid (4x*4z = 16 lights)
  adaptive 0          // 0,1,2,3... 
  jitter              // adds random softening of light
  translate <-4, 4, -4>   // <x y z> position of light
}

// create a sphere shape
sphere
{
  <0, 1, 0> // center of sphere <X Y Z>
  1       // radius of sphere
  //pigment { color Yellow }
  texture { T_Silver_4E }
}

// An infinite planar surface
// plane {<A, B, C>, D } where: A*x + B*y + C*z = D
plane
{
  y, // <X Y Z> unit surface normal, vector points "away from surface"
  -1.0 // distance from the origin in the direction of the surface normal
  pigment { hexagon color Red color Green color Blue }
  //finish { F_MetalE }
}
