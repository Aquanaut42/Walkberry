
#include "DEV_Config.h"
#include "../Fonts/fonts.h"


/**
 * image color
**/
#define WHITE          0xFF
#define BLACK          0x00
#define RED            BLACK

#define IMAGE_BACKGROUND    WHITE
#define FONT_FOREGROUND     BLACK
#define FONT_BACKGROUND     WHITE

//4 Gray level
#define  GRAY1 0x03 //Blackest
#define  GRAY2 0x02
#define  GRAY3 0x01 //gray
#define  GRAY4 0x00 //white


/**
 * Drawing images and text
 */
void SetScale(UBYTE scale);
void SetPixel(UWORD Xpoint, UWORD Ypoint, UWORD Color);
void DrawChar(UWORD Xpoint, UWORD Ypoint, const char Acsii_Char, sFONT* Font, UWORD Color_Foreground, UWORD Color_Background);
void DrawString_EN(UWORD Xstart, UWORD Ystart, const char * pString, sFONT* Font, UWORD Color_Foreground, UWORD Color_Background);
