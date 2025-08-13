
#include "DEV_Config.h"

/**
 * Image attributes
**/
typedef struct {
    UBYTE *Image;
    UWORD Width;
    UWORD Height;
    UWORD WidthMemory;
    UWORD HeightMemory;
    UWORD Color;
    UWORD WidthByte;
    UWORD HeightByte;
    UWORD Scale;
} PAINTSCREEN;
extern PAINTSCREEN PaintScreen    ;

/**
 * image color
**/
#define WHITE          0xFF
#define BLACK          0x00
#define RED            BLACK

#define IMAGE_BACKGROUND    WHITE
#define FONT_FOREGROUND     BLACK
#define FONT_BACKGROUND     WHITE

/**
 * Drawing images and text
 */
void SetScale(UBYTE scale);
void SetPixel(UWORD Xpoint, UWORD Ypoint, UWORD Color);
void DrawChar(UWORD Xpoint, UWORD Ypoint, const char Acsii_Char, sFONT* Font, UWORD Color_Foreground, UWORD Color_Background);
void DrawString_EN(UWORD Xstart, UWORD Ystart, const char * pString, sFONT* Font, UWORD Color_Foreground, UWORD Color_Background);