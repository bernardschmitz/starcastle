//  Texture Include file.
//
//  This file was generated for POV-Ray V3.0 by
//  NOTE: Do *NOT* remove the comment lines containing '$MRY$'.
//        To make Moray not re-export the texture, change
//        the '$MRY$' to '$MRX$'.
//


//
// ********  TEXTURES  *******
//







// Textures from previous exports [MRY]

// Textures exported in this run [MRY]



//  $MRY$: 'my_Blood_Marble'


#declare my_Blood_Marble = 
   texture  // my_Blood_Marble
   {   
      pigment
      {
         marble
         color_map
         {
            [ 0.0     rgbft <0.1, 0.1, 0.1, 0.0, 0.0> ]
            [ 0.8     rgbft <0.0, 0.8, 0.8, 0.0, 0.0> ]
            [ 0.9     rgbft <0.8, 0.0, 0.0, 0.0, 0.0> ]
            [ 1.0     rgbft <0.1, 0.1, 0.1, 0.0, 0.0> ]
         }
         turbulence 2.3
      }   
      finish
      {
         //ambient 0.1
         ambient 0.0
         brilliance 4.0
         specular 0.8
         roughness 0.01
      }
   }


//  $MRY$: 'T_Chrome_3D'


#declare T_Chrome_3D = 
   texture  // T_Chrome_3D
   {   
      pigment
      {
         color rgb <0.5, 0.5, 0.5>
      }   
      finish
      {
         //ambient 0.15
         ambient 0.1
         brilliance 5.0
         specular 0.8
         roughness 0.01
         reflection 0.65
      }
   }


//  $MRY$: 'T_Chrome_2C'


#declare T_Chrome_2C = 
   texture  // T_Chrome_2C
   {   
      pigment
      {
         color rgb <0.39, 0.41, 0.43>
      }   
      finish
      {
         //ambient 0.25
         ambient 0.1
         diffuse 0.5
         brilliance 4.0
         specular 0.8
         roughness 0.0125
         reflection 0.5
      }
   }


//  $MRY$: 'Polished_Brass'


#declare Polished_Brass = 
   texture  // Polished_Brass
   {   
      pigment
      {
         color rgb <0.578, 0.422, 0.195>
      }   
      finish
      {
         ambient 0.1
         diffuse 0.8
         brilliance 6.0
         phong 0.8
         phong_size 120.0
         reflection 0.4
      }
   }
