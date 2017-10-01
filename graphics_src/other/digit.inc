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



//  $MRY$: 'Brass_Valley'


#declare Brass_Valley = 
   texture  // Brass_Valley
   {   
      pigment
      {
         granite
         color_map
         {
            [ 0.0     rgbft <0.82, 0.57, 0.46, 0.0, 0.0> ]
            [ 0.3     rgbft <0.82, 0.57, 0.46, 0.0, 0.0> ]
            [ 0.3     rgbft <0.0, 0.0, 0.0, 0.0, 0.0> ]
            [ 0.6     rgbft <0.85, 0.85, 0.95, 0.0, 0.0> ]
            [ 0.6     rgbft <0.82, 0.57, 0.46, 0.0, 0.0> ]
            [ 1.0     rgbft <0.85, 0.85, 0.95, 0.0, 0.0> ]
         }
      }   
      finish
      {
         ambient 0.1
         brilliance 6.0
         phong 0.75
         reflection 0.75
      }
   }


//  $MRY$: 'Red_Vein_Grey_Plastic'


#declare Red_Vein_Grey_Plastic = 
   texture  // Red_Vein_Grey_Plastic
   {   
      pigment
      {
         marble
         color_map
         {
            [ 0.0     rgbft <1.0, 0.0, 0.0, 0.0, 0.0> ]
            [ 0.7     rgbft <1.0, 0.0, 0.0, 0.0, 0.0> ]
            [ 0.9     rgbft <1.0, 1.0, 1.0, 0.0, 0.0> ]
            [ 0.9     rgbft <0.9, 0.8, 0.8, 0.0, 0.0> ]
            [ 1.0     rgbft <0.7, 0.5, 0.5, 0.0, 0.0> ]
         }
         turbulence 1.0
      }   
      finish
      {
         ambient 0.1
         phong 1.0
      }
   }


//  $MRY$: 'Texture1'


#declare Texture1 = 
   texture  // Texture1
   {   
      pigment
      {
         color rgb <0.0, 1.0, 0.0>
      }
   }
