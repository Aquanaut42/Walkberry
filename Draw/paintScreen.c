/******************************************************************************
 * 
 * This file is to draw all the images to the screen
 * 
 * it includes drawing images and writing text
 * (the functions are based on GUI_Paint.c from the code given)
 * 
******************************************************************************/

#include "paintScreen.h"
#include <DEV_Config.h>
#include <fonts.h>

PAINTSCREEN PaintScreen;

/******************************************************************************
function: Paint SetScale
parameter:
    scale  : Scale of the paint ( 2, 4, 7)
******************************************************************************/
void SetScale(UBYTE scale)
{
    if(scale == 2){
        PaintScreen.Scale = scale;
        PaintScreen.WidthByte = (PaintScreen.WidthMemory % 8 == 0)? (PaintScreen.WidthMemory / 8 ): (PaintScreen.WidthMemory / 8 + 1);
    }else if(scale == 4){
        PaintScreen.Scale = scale;
        PaintScreen.WidthByte = (PaintScreen.WidthMemory % 4 == 0)? (PaintScreen.WidthMemory / 4 ): (PaintScreen.WidthMemory / 4 + 1);
    }else if(scale == 7){//Only applicable with 5in65 e-Paper
		PaintScreen.Scale = scale;
		PaintScreen.WidthByte = (PaintScreen.WidthMemory % 2 == 0)? (PaintScreen.WidthMemory / 2 ): (PaintScreen.WidthMemory / 2 + 1);;
	}else{
        Debug("Set Scale Input parameter error\r\n");
        Debug("Scale Only support: 2 4 7\r\n");
    }
}
//*****************************************************************************

/******************************************************************************
function: Draw Pixels
parameter:
    Xpoint : At point X
    Ypoint : At point Y
    Color  : Painted colors
******************************************************************************/
void SetPixel(UWORD Xpoint, UWORD Ypoint, UWORD Color)
{
    
    if(PaintScreen.Scale == 2){
        UDOUBLE Addr = Ypoint / 8 + Xpoint * PaintScreen.WidthByte;
        UBYTE Rdata = PaintScreen.Image[Addr];
        if(Color == BLACK)
            PaintScreen.Image[Addr] = Rdata & ~(0x80 >> (Ypoint % 8));
        else
            PaintScreen.Image[Addr] = Rdata | (0x80 >> (Ypoint % 8));
    }else if(PaintScreen.Scale == 4){
        UDOUBLE Addr = Ypoint / 4 + Xpoint * PaintScreen.WidthByte;
        Color = Color % 4;//Guaranteed color scale is 4  --- 0~3
        UBYTE Rdata = PaintScreen.Image[Addr];
        
        Rdata = Rdata & (~(0xC0 >> ((Xpoint % 4)*2)));//Clear first, then set value
        PaintScreen.Image[Addr] = Rdata | ((Color << 6) >> ((Ypoint % 4)*2));
    }else if(PaintScreen.Scale == 7){
		UDOUBLE Addr = Ypoint / 2  + Xpoint * PaintScreen.WidthByte;
		UBYTE Rdata = PaintScreen.Image[Addr];
		Rdata = Rdata & (~(0xF0 >> ((Ypoint % 2)*4)));//Clear first, then set value
		PaintScreen.Image[Addr] = Rdata | ((Color << 4) >> ((Ypoint % 2)*4));
	}
}
//*****************************************************************************

/******************************************************************************
function: Show English characters
parameter:
    Xpoint           ：X coordinate
    Ypoint           ：Y coordinate
    Acsii_Char       ：To display the English characters
    Font             ：A structure pointer that displays a character size
    Color_Foreground : Select the foreground color
    Color_Background : Select the background color
******************************************************************************/
void DrawChar(UWORD Xpoint, UWORD Ypoint, const char Acsii_Char,
                    sFONT* Font, UWORD Color_Foreground, UWORD Color_Background)
{
    UWORD Page, Column;

    if (Xpoint > PaintScreen.Width || Ypoint > PaintScreen.Height) {
        Debug("Paint_DrawChar Input exceeds the normal display range\r\n");
        return;
    }

    uint32_t Char_Offset = (Acsii_Char - ' ') * Font->Height * (Font->Width / 8 + (Font->Width % 8 ? 1 : 0));
    const unsigned char *ptr = &Font->table[Char_Offset];

    for (Page = 0; Page < Font->Height; Page ++ ) {
        for (Column = 0; Column < Font->Width; Column ++ ) {

            //To determine whether the font background color and screen background color is consistent
            if (FONT_BACKGROUND == Color_Background) { //this process is to speed up the scan
                if (*ptr & (0x80 >> (Column % 8)))
                    SetPixel(Xpoint + Column, Ypoint + Page, Color_Foreground);
                    // Paint_DrawPoint(Xpoint + Column, Ypoint + Page, Color_Foreground, DOT_PIXEL_DFT, DOT_STYLE_DFT);
            } else {
                if (*ptr & (0x80 >> (Column % 8))) {
                    SetPixel(Xpoint + Column, Ypoint + Page, Color_Foreground);
                    // Paint_DrawPoint(Xpoint + Column, Ypoint + Page, Color_Foreground, DOT_PIXEL_DFT, DOT_STYLE_DFT);
                } else {
                    SetPixel(Xpoint + Column, Ypoint + Page, Color_Background);
                    // Paint_DrawPoint(Xpoint + Column, Ypoint + Page, Color_Background, DOT_PIXEL_DFT, DOT_STYLE_DFT);
                }
            }
            //One pixel is 8 bits
            if (Column % 8 == 7)
                ptr++;
        }// Write a line
        if (Font->Width % 8 != 0)
            ptr++;
    }// Write all
}
//*****************************************************************************

/******************************************************************************
function:	Display the string
parameter:
    Xstart           ：X coordinate
    Ystart           ：Y coordinate
    pString          ：The first address of the English string to be displayed
    Font             ：A structure pointer that displays a character size
    Color_Foreground : Select the foreground color
    Color_Background : Select the background color
******************************************************************************/
void DrawString_EN(UWORD Xstart, UWORD Ystart, const char * pString,
                         sFONT* Font, UWORD Color_Foreground, UWORD Color_Background)
{
    UWORD Xpoint = Xstart;
    UWORD Ypoint = Ystart;

    if (Xstart > PaintScreen.Width || Ystart > PaintScreen.Height) {
        Debug("Paint_DrawString_EN Input exceeds the normal display range\r\n");
        return;
    }

    while (* pString != '\0') {
        //if X direction filled , reposition to(Xstart,Ypoint),Ypoint is Y direction plus the Height of the character
        if ((Xpoint + Font->Width ) > PaintScreen.Width ) {
            Xpoint = Xstart;
            Ypoint += Font->Height;
        }

        // If the Y direction is full, reposition to(Xstart, Ystart)
        if ((Ypoint  + Font->Height ) > PaintScreen.Height ) {
            Xpoint = Xstart;
            Ypoint = Ystart;
        }
        DrawChar(Xpoint, Ypoint, * pString, Font, Color_Background, Color_Foreground);

        //The next character of the address
        pString ++;

        //The next word of the abscissa increases the font of the broadband
        Xpoint += Font->Width;
    }
}
//*****************************************************************************
