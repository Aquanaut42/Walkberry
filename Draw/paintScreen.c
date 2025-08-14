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
#include "../Fonts/fonts.h"
#include "GUI_Paint.h"


/******************************************************************************
function: Paint SetScale
parameter:
    scale  : Scale of the paint ( 2, 4, 7)
******************************************************************************/
void SetScale(UBYTE scale)
{
    if(scale == 2){
        Paint.Scale = scale;
        Paint.WidthByte = (Paint.WidthMemory % 8 == 0)? (Paint.WidthMemory / 8 ): (Paint.WidthMemory / 8 + 1);
    }else if(scale == 4){
        Paint.Scale = scale;
        Paint.WidthByte = (Paint.WidthMemory % 4 == 0)? (Paint.WidthMemory / 4 ): (Paint.WidthMemory / 4 + 1);
    }else if(scale == 7){//Only applicable with 5in65 e-Paper
		Paint.Scale = scale;
		Paint.WidthByte = (Paint.WidthMemory % 2 == 0)? (Paint.WidthMemory / 2 ): (Paint.WidthMemory / 2 + 1);;
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
Returns:
    1 if successful, -1 if out of bounds
******************************************************************************/
int SetPixel(UWORD Xpoint, UWORD Ypoint, UWORD Color)
{
    if ( Xpoint >= Paint.Width || Xpoint <= 0 || 
         Ypoint >= Paint.Height || Ypoint <= 0) {
        Debug("Exceeding display boundaries\r\n");
        return -1;
    }
    if(Paint.Scale == 2){
        UDOUBLE Addr = Xpoint / 8 + Ypoint * Paint.WidthByte;
        UBYTE Rdata = Paint.Image[Addr];
        if(Color == BLACK)
            Paint.Image[Addr] = Rdata & ~(0x80 >> (Xpoint % 8));
        else
            Paint.Image[Addr] = Rdata | (0x80 >> (Xpoint % 8));
    }else if(Paint.Scale == 4){
        UDOUBLE Addr = Xpoint / 4 + Ypoint * Paint.WidthByte;
        Color = Color % 4;//Guaranteed color scale is 4  --- 0~3
        UBYTE Rdata = Paint.Image[Addr];
        
        Rdata = Rdata & (~(0xC0 >> ((Xpoint % 4)*2)));//Clear first, then set value
        Paint.Image[Addr] = Rdata | ((Color << 6) >> ((Xpoint % 4)*2));
    }else if(Paint.Scale == 7){
		UDOUBLE Addr = Xpoint / 2  + Ypoint * Paint.WidthByte;
		UBYTE Rdata = Paint.Image[Addr];
		Rdata = Rdata & (~(0xF0 >> ((Xpoint % 2)*4)));//Clear first, then set value
		Paint.Image[Addr] = Rdata | ((Color << 4) >> ((Xpoint % 2)*4));
		// printf("Add =  %d ,data = %d\r\n",Addr,Rdata);
	}
    return 1;
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
Returns:
    1 if successful, -1 if out of bounds
******************************************************************************/
int DrawChar(UWORD Xpoint, UWORD Ypoint, const char Acsii_Char,
                    sFONT* Font, UWORD Color_Foreground, UWORD Color_Background)
{
    UWORD Page, Column;

    if ( (Xpoint + Font->Width) > Paint.Width || Xpoint <= 0|| 
         (Ypoint + Font->Height) > Paint.Height || Ypoint <= 0) {
        Debug("Paint_DrawString_EN Input exceeds the normal display range (DrawChar)\r\n");
        return -1;
    }

    uint32_t Char_Offset = (Acsii_Char - ' ') * Font->Height * (Font->Width / 8 + (Font->Width % 8 ? 1 : 0));
    const unsigned char *ptr = &Font->table[Char_Offset];

    for (Page = 0; Page < Font->Height; Page ++ ) {
        for (Column = 0; Column < Font->Width; Column ++ ) {

            //To determine whether the font background color and screen background color is consistent
            if (FONT_BACKGROUND == Color_Background) { //this process is to speed up the scan
                if (*ptr & (0x80 >> (Column % 8)))
                    if (SetPixel(Xpoint + Column, Ypoint + Page, Color_Foreground) == -1) {
                        Debug("SetPixel failed\r\n");
                        return -1;
                    }  
                    // Paint_DrawPoint(Xpoint + Column, Ypoint + Page, Color_Foreground, DOT_PIXEL_DFT, DOT_STYLE_DFT);
            } else {
                if (*ptr & (0x80 >> (Column % 8))) {
                    if (SetPixel(Xpoint + Column, Ypoint + Page, Color_Foreground) == -1) {
                        Debug("SetPixel failed\r\n");
                        return -1;
                    }   
                    // Paint_DrawPoint(Xpoint + Column, Ypoint + Page, Color_Foreground, DOT_PIXEL_DFT, DOT_STYLE_DFT);
                } else {
                    if (SetPixel(Xpoint + Column, Ypoint + Page, Color_Background) == -1) {
                        Debug("SetPixel failed\r\n");
                        return -1;
                    }   
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
    return 1; // Return success
}
//*****************************************************************************

/******************************************************************************
function: Display the string
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

    if (Xstart >= Paint.Width || Xstart <= 0 || 
        Ystart >= Paint.Height || Ystart <= 0) {
        Debug("Paint_DrawString_EN Input exceeds the normal display range (DrawString_EN)\r\n");
        return;
    }

    while (* pString != '\0') {
        //if it's out of bounds, return
        if (Xpoint >= Paint.Width || Xpoint <= 0) {
            Debug("Exceeding display boundaries (DrawString_EN x)\r\n");
            return;
        }
        if (Ypoint >= Paint.Height || Ypoint <= 0) {
            Debug("Exceeding display boundaries (DrawString_EN y)\r\n");
            return;
        }
        if (DrawChar(Xpoint, Ypoint, * pString, Font, Color_Background, Color_Foreground) == -1) {
            Debug("DrawChar failed\r\n");
            return;
        }

        //The next character of the address
        pString ++;

        //The next word of the abscissa increases the font of the broadband
        Xpoint += Font->Width;
    }
}
//*****************************************************************************

/******************************************************************************
function: Clear the color of a window
parameter:
    Xstart : x starting point
    Ystart : Y starting point
    Xend   : x end point
    Yend   : y end point
    Color  : Painted colors
******************************************************************************/
void ClearWindows( UWORD Color )
{
    for (int Y = 0; Y < Paint.Height; Y++) {
        for ( int X = 0; X < Paint.Width; X++) {//8 pixel =  1 byte
            if (SetPixel(X, Y, Color) == -1) {
                Debug("SetPixel failed in ClearWindows\r\n");
                return;
            }
        }
    }
}
//*****************************************************************************

//*****************************************************************************

/******************************************************************************
function: Draw a horizontal line
parameter:
    Xstart ：Starting Xpoint point coordinates
    Ystart ：Starting Xpoint point coordinates
    Xend   ：End point Xpoint coordinate
    Color  ：The color of the line segment
    Line_width : Line width
    Line_Style: Solid and dotted lines
******************************************************************************/
void DrawLineHorizontal(UWORD Xstart, UWORD Y, UWORD Xend, UWORD Color, int Line_width)
{
    for ( int dx = 0 ; dx > Xend ; dx++ ) {
        for ( int i = 0 ; i < Line_width ; i++ ) {
            if (SetPixel(Xstart + dx, Y + i, Color) == -1) {
                Debug("SetPixel failed in DrawLineHorizontal\r\n");
                return;
            }
        }
    }
}
//*****************************************************************************

/******************************************************************************
function: Draw a vertical line
parameter:
    Xstart ：Starting Xpoint point coordinates
    Ystart ：Starting Xpoint point coordinates
    Xend   ：End point Xpoint coordinate
    Color  ：The color of the line segment
    Line_width : Line width
    Line_Style: Solid and dotted lines
******************************************************************************/
void DrawLineVertical(UWORD Ystart, UWORD X, UWORD Yend, UWORD Color, int Line_width)
{
    for ( int dx = 0 ; dx > Yend ; dx++ ) {
        for ( int i = 0 ; i < Line_width ; i++ ) {
            if (SetPixel(Ystart + dx, X + i, Color) == -1) {
                Debug("SetPixel failed in DrawLineVertical\r\n");
                return;
            }
        }
    }
}
//*****************************************************************************
