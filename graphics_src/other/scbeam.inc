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



//  $MRY$: 'Beam'


#declare Beam = 
   texture  // Beam
   {   
      pigment
      {
         gradient y
         color_map
         {
            [ 0.0     rgbft <0.0, 0.0, 1.0, 0.0, 1.0> ]
            [ 0.166667  rgbft <0.5, 0.5, 1.0, 0.0, 0.5> ]
            [ 0.333333  rgbft <0.875, 0.875, 1.0, 0.0, 0.0> ]
            [ 0.5     rgbft <1.0, 1.0, 1.0, 0.0, 0.0> ]
            [ 0.666667  rgbft <0.875, 0.875, 1.0, 0.0, 0.0> ]
            [ 0.833333  rgbft <0.5, 0.5, 1.0, 0.0, 0.5> ]
            [ 1.0     rgbft <0.0104, 0.0, 1.0, 0.0, 1.0> ]
         }
         scale  <1.0, 2.0, 1.0>
         rotate -90.0 * z
         translate 1.0 * x
      }   
      finish
      {
         ambient 1.0
         diffuse 0.503567
      }
   }
