/**
  ******************************************************************************
  * @file    Font8.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-February-2014
  * @brief   This file provides text Font8 for STM32xx-EVAL's LCD driver. 
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "fonts.h"

// 
//  Font data for Courier New 12pt
// 

const uint8_t Font8_Table[] = 
{
	// @0 ' ' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x00, //      
	0x00, //      
	0x00, //      
	0x00, //      
	0x00, //      
	0x00, //      

	// @8 '!' (5 pixels wide)
	0x00, //   #  
	0x00, //   #  
	0xF4, //   #  
	0x00, //   #  
	0x00, //      
	0x00, //   #  
	0x00, //      
	0x00, //      

	// @16 '"' (5 pixels wide)
	0x00, //  # # 
	0xC0, //  # # 
	0x00, //      
	0xC0, //      
	0x00, //      
	0x00, //      
	0x00, //      
	0x00, //      

	// @24 '#' (5 pixels wide)
	0x2A, //   # #
	0x7C, //  # # 
	0xAA, // #####
	0x7C, //  # # 
	0xA8, // #####
	0x00, //  # # 
	0x00, // # #  
	0x00, //      

	// @32 '$' (5 pixels wide)
	0x00, //   #  
	0x24, //   ## 
	0xF6, //  ##  
	0x58, //   ## 
	0x00, //    # 
	0x00, //  ##  
	0x00, //   #  
	0x00, //      

	// @40 '%' (5 pixels wide)
	0x00, //   #  
	0x10, //   #  
	0xD0, //    ##
	0x2C, //  ##  
	0x20, //    # 
	0x00, //    # 
	0x00, //      
	0x00, //      

	// @48 '&' (5 pixels wide)
	0x00, //      
	0x1C, //   ###
	0x74, //   #  
	0x4C, //  ##  
	0x44, //  # # 
	0x00, //  ####
	0x00, //      
	0x00, //      

	// @56 ''' (5 pixels wide)
	0x00, //   #  
	0x00, //   #  
	0xE0, //   #  
	0x00, //      
	0x00, //      
	0x00, //      
	0x00, //      
	0x00, //      

	// @64 '(' (5 pixels wide)
	0x00, //    # 
	0x00, //   #  
	0x7C, //   #  
	0x82, //   #  
	0x00, //   #  
	0x00, //   #  
	0x00, //    # 
	0x00, //      

	// @72 ')' (5 pixels wide)
	0x00, //  #   
	0x82, //   #  
	0x7C, //   #  
	0x00, //   #  
	0x00, //   #  
	0x00, //   #  
	0x00, //  #   
	0x00, //      

	// @80 '*' (5 pixels wide)
	0x00, //   #  
	0x50, //  ### 
	0xE0, //   #  
	0x50, //  # # 
	0x00, //      
	0x00, //      
	0x00, //      
	0x00, //      

	// @88 '+' (5 pixels wide)
	0x10, //      
	0x10, //   #  
	0x7C, //   #  
	0x10, // #####
	0x10, //   #  
	0x00, //   #  
	0x00, //      
	0x00, //      

	// @96 ',' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x06, //      
	0x08, //      
	0x00, //    # 
	0x00, //   #  
	0x00, //   #  
	0x00, //      

	// @104 '-' (5 pixels wide)
	0x00, //      
	0x10, //      
	0x10, //      
	0x10, //  ### 
	0x00, //      
	0x00, //      
	0x00, //      
	0x00, //      

	// @112 '.' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x04, //      
	0x00, //      
	0x00, //      
	0x00, //   #  
	0x00, //      
	0x00, //      

	// @120 '/' (5 pixels wide)
	0x02, //    # 
	0x0C, //   #  
	0x70, //   #  
	0x80, //   #  
	0x00, //  #   
	0x00, //  #   
	0x00, // #    
	0x00, //      

	// @128 '0' (5 pixels wide)
	0x00, //   #  
	0x78, //  # # 
	0x84, //  # # 
	0x78, //  # # 
	0x00, //  # # 
	0x00, //   #  
	0x00, //      
	0x00, //      

	// @136 '1' (5 pixels wide)
	0x04, //  ##  
	0x84, //   #  
	0xFC, //   #  
	0x04, //   #  
	0x04, //   #  
	0x00, // #####
	0x00, //      
	0x00, //      

	// @144 '2' (5 pixels wide)
	0x00, //   #  
	0x4C, //  # # 
	0xB4, //   #  
	0x44, //   #  
	0x00, //  #   
	0x00, //  ### 
	0x00, //      
	0x00, //      

	// @152 '3' (5 pixels wide)
	0x00, //   #  
	0x44, //  # # 
	0x94, //    # 
	0x68, //   #  
	0x00, //    # 
	0x00, //  ##  
	0x00, //      
	0x00, //      

	// @160 '4' (5 pixels wide)
	0x00, //    # 
	0x30, //   ## 
	0x54, //  # # 
	0xFC, //  ####
	0x14, //    # 
	0x00, //   ###
	0x00, //      
	0x00, //      

	// @168 '5' (5 pixels wide)
	0x00, //  ### 
	0xE8, //  #   
	0xA4, //  ##  
	0x98, //    # 
	0x00, //  # # 
	0x00, //   #  
	0x00, //      
	0x00, //      

	// @176 '6' (5 pixels wide)
	0x00, //   ## 
	0x7C, //  #   
	0xA4, //  ##  
	0x98, //  # # 
	0x00, //  # # 
	0x00, //  ##  
	0x00, //      
	0x00, //      

	// @184 '7' (5 pixels wide)
	0x00, //  ### 
	0xC0, //  # # 
	0x9C, //    # 
	0xE0, //   #  
	0x00, //   #  
	0x00, //   #  
	0x00, //      
	0x00, //      

	// @192 '8' (5 pixels wide)
	0x00, //   #  
	0x58, //  # # 
	0xA4, //   #  
	0x58, //  # # 
	0x00, //  # # 
	0x00, //   #  
	0x00, //      
	0x00, //      

	// @200 '9' (5 pixels wide)
	0x00, //   ## 
	0x64, //  # # 
	0x94, //  # # 
	0xF8, //   ## 
	0x00, //    # 
	0x00, //  ##  
	0x00, //      
	0x00, //      

	// @208 ':' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x24, //   #  
	0x00, //      
	0x00, //      
	0x00, //   #  
	0x00, //      
	0x00, //      

	// @216 ';' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x04, //    # 
	0x28, //      
	0x00, //    # 
	0x00, //   #  
	0x00, //      
	0x00, //      

	// @224 '<' (5 pixels wide)
	0x10, //      
	0x10, //    # 
	0x28, //   #  
	0x44, // ##   
	0x00, //   #  
	0x00, //    # 
	0x00, //      
	0x00, //      

	// @232 '=' (5 pixels wide)
	0x00, //      
	0x50, //  ### 
	0x50, //      
	0x50, //  ### 
	0x00, //      
	0x00, //      
	0x00, //      
	0x00, //      

	// @240 '>' (5 pixels wide)
	0x00, //      
	0x44, //  #   
	0x28, //   #  
	0x10, //    ##
	0x10, //   #  
	0x00, //  #   
	0x00, //      
	0x00, //      

	// @248 '?' (5 pixels wide)
	0x00, //   #  
	0x40, //  # # 
	0x94, //    # 
	0x60, //   #  
	0x00, //      
	0x00, //   #  
	0x00, //      
	0x00, //      

	// @256 '@' (5 pixels wide)
	0x00, //   ## 
	0x7C, //  #  #
	0x82, //  #  #
	0x92, //  # ##
	0x7A, //  #  #
	0x00, //  #   
	0x00, //   ###
	0x00, //      

	// @264 'A' (5 pixels wide)
	0x0C, //  ##  
	0xB4, //   #  
	0xD0, //  # # 
	0x34, //  ### 
	0x0C, // #   #
	0x00, // ## ##
	0x00, //      
	0x00, //      

	// @272 'B' (5 pixels wide)
	0x84, // #### 
	0xFC, //  #  #
	0xA4, //  ### 
	0xA4, //  #  #
	0x58, //  #  #
	0x00, // #### 
	0x00, //      
	0x00, //      

	// @280 'C' (5 pixels wide)
	0x00, //  ### 
	0xF8, //  # # 
	0x84, //  #   
	0xC4, //  #   
	0x00, //  #   
	0x00, //   ## 
	0x00, //      
	0x00, //      

	// @288 'D' (5 pixels wide)
	0x84, // #### 
	0xFC, //  #  #
	0x84, //  #  #
	0x84, //  #  #
	0x78, //  #  #
	0x00, // #### 
	0x00, //      
	0x00, //      

	// @296 'E' (5 pixels wide)
	0x84, // #####
	0xFC, //  #  #
	0xA4, //  ##  
	0x84, //  #   
	0xCC, //  #  #
	0x00, // #####
	0x00, //      
	0x00, //      

	// @304 'F' (5 pixels wide)
	0x84, // #####
	0xFC, //  #  #
	0xA4, //  ##  
	0x80, //  #   
	0xC0, //  #   
	0x00, // ###  
	0x00, //      
	0x00, //      

	// @312 'G' (5 pixels wide)
	0x00, //  ### 
	0xF8, //  #   
	0x84, //  #   
	0x9C, //  # ##
	0x10, //  # # 
	0x00, //   ## 
	0x00, //      
	0x00, //      

	// @320 'H' (5 pixels wide)
	0x84, // ### #
	0xFC, //  #  #
	0xA4, //  ####
	0x20, //  #  #
	0xFC, //  #  #
	0x00, // ### #
	0x00, //      
	0x00, //      

	// @328 'I' (5 pixels wide)
	0x00, //  ### 
	0x84, //   #  
	0xFC, //   #  
	0x84, //   #  
	0x00, //   #  
	0x00, //  ### 
	0x00, //      
	0x00, //      

	// @336 'J' (5 pixels wide)
	0x00, //   ###
	0x18, //    # 
	0x84, //    # 
	0xF8, //  # # 
	0x80, //  # # 
	0x00, //   #  
	0x00, //      
	0x00, //      

	// @344 'K' (5 pixels wide)
	0x84, // ## ##
	0xFC, //  # # 
	0x30, //  ##  
	0xDC, //  ### 
	0x84, //  # # 
	0x00, // ## ##
	0x00, //      
	0x00, //      

	// @352 'L' (5 pixels wide)
	0x84, // ###  
	0xFC, //  #   
	0x84, //  #   
	0x04, //  #   
	0x0C, //  #  #
	0x00, // #####
	0x00, //      
	0x00, //      

	// @360 'M' (5 pixels wide)
	0xFC, // ## ##
	0xE4, // ## ##
	0x10, // ## ##
	0xE4, // # # #
	0xFC, // #   #
	0x00, // ## ##
	0x00, //      
	0x00, //      

	// @368 'N' (5 pixels wide)
	0x84, // ## ##
	0xFC, //  ## #
	0x64, //  ## #
	0x98, //  # ##
	0xFC, //  # ##
	0x00, // ### #
	0x00, //      
	0x00, //      

	// @376 'O' (5 pixels wide)
	0x00, //   ## 
	0x78, //  #  #
	0x84, //  #  #
	0x84, //  #  #
	0x78, //  #  #
	0x00, //   ## 
	0x00, //      
	0x00, //      

	// @384 'P' (5 pixels wide)
	0x84, // #### 
	0xFC, //  #  #
	0x94, //  #  #
	0x90, //  ### 
	0x60, //  #   
	0x00, // ###  
	0x00, //      
	0x00, //      

	// @392 'Q' (5 pixels wide)
	0x00, //   ## 
	0x78, //  #  #
	0x84, //  #  #
	0x86, //  #  #
	0x7A, //  #  #
	0x00, //   ## 
	0x00, //    ##
	0x00, //      

	// @400 'R' (5 pixels wide)
	0x84, // #### 
	0xFC, //  #  #
	0x94, //  #  #
	0x90, //  ### 
	0x6C, //  #  #
	0x00, // ### #
	0x00, //      
	0x00, //      

	// @408 'S' (5 pixels wide)
	0x00, //  ### 
	0xCC, //  # # 
	0xA4, //   #  
	0xDC, //    # 
	0x00, //  # # 
	0x00, //  ### 
	0x00, //      
	0x00, //      

	// @416 'T' (5 pixels wide)
	0xC0, // #####
	0x84, // # # #
	0xFC, //   #  
	0x84, //   #  
	0xC0, //   #  
	0x00, //  ### 
	0x00, //      
	0x00, //      

	// @424 'U' (5 pixels wide)
	0x80, // ## ##
	0xF8, //  #  #
	0x04, //  #  #
	0x84, //  #  #
	0xF8, //  #  #
	0x00, //   ## 
	0x00, //      
	0x00, //      

	// @432 'V' (5 pixels wide)
	0xC0, // ## ##
	0xB8, // #   #
	0x04, //  #  #
	0x9C, //  # # 
	0xE0, //  # # 
	0x00, //   ## 
	0x00, //      
	0x00, //      

	// @440 'W' (5 pixels wide)
	0xF8, // ## ##
	0x84, // #   #
	0x38, // # # #
	0x84, // # # #
	0xF8, // # # #
	0x00, //  # # 
	0x00, //      
	0x00, //      

	// @448 'X' (5 pixels wide)
	0x84, // ## ##
	0xCC, //  # # 
	0x30, //   #  
	0xCC, //   #  
	0x84, //  # # 
	0x00, // ## ##
	0x00, //      
	0x00, //      

	// @456 'Y' (5 pixels wide)
	0xC0, // ## ##
	0xA4, // #   #
	0x1C, //  # # 
	0xA4, //   #  
	0xC0, //   #  
	0x00, //  ### 
	0x00, //      
	0x00, //      

	// @464 'Z' (5 pixels wide)
	0x00, //  ####
	0xCC, //  #  #
	0x94, //    # 
	0xA4, //   #  
	0xCC, //  #  #
	0x00, //  ####
	0x00, //      
	0x00, //      

	// @472 '[' (5 pixels wide)
	0x00, //   ## 
	0x00, //   #  
	0xFE, //   #  
	0x82, //   #  
	0x00, //   #  
	0x00, //   #  
	0x00, //   ## 
	0x00, //      

	// @480 '\' (5 pixels wide)
	0x80, // #    
	0x60, //  #   
	0x1C, //  #   
	0x02, //   #  
	0x00, //   #  
	0x00, //   #  
	0x00, //    # 
	0x00, //      

	// @488 ']' (5 pixels wide)
	0x00, //  ##  
	0x82, //   #  
	0xFE, //   #  
	0x00, //   #  
	0x00, //   #  
	0x00, //   #  
	0x00, //  ##  
	0x00, //      

	// @496 '^' (5 pixels wide)
	0x00, //   #  
	0x20, //   #  
	0xC0, //  # # 
	0x20, //      
	0x00, //      
	0x00, //      
	0x00, //      
	0x00, //      

	// @504 '_' (5 pixels wide)
	0x01, //      
	0x01, //      
	0x01, //      
	0x01, //      
	0x01, //      
	0x00, //      
	0x00, //      
	0x00, // #####

	// @512 '`' (5 pixels wide)
	0x00, //   #  
	0x00, //    # 
	0x80, //      
	0x40, //      
	0x00, //      
	0x00, //      
	0x00, //      
	0x00, //      

	// @520 'a' (5 pixels wide)
	0x00, //      
	0x0C, //      
	0x2C, //   ## 
	0x3C, //    # 
	0x04, //  ### 
	0x00, //  ####
	0x00, //      
	0x00, //      

	// @528 'b' (5 pixels wide)
	0x84, // ##   
	0xFC, //  #   
	0x24, //  ### 
	0x24, //  #  #
	0x18, //  #  #
	0x00, // #### 
	0x00, //      
	0x00, //      

	// @536 'c' (5 pixels wide)
	0x00, //      
	0x3C, //      
	0x24, //  ### 
	0x24, //  #   
	0x00, //  #   
	0x00, //  ### 
	0x00, //      
	0x00, //      

	// @544 'd' (5 pixels wide)
	0x00, //    ##
	0x18, //     #
	0x24, //   ###
	0xA4, //  #  #
	0xFC, //  #  #
	0x00, //   ###
	0x00, //      
	0x00, //      

	// @552 'e' (5 pixels wide)
	0x00, //      
	0x38, //      
	0x34, //  ### 
	0x34, //  ### 
	0x00, //  #   
	0x00, //   ## 
	0x00, //      
	0x00, //      

	// @560 'f' (5 pixels wide)
	0x00, //    # 
	0x24, //   #  
	0x7C, //  ### 
	0xA4, //   #  
	0x00, //   #  
	0x00, //  ### 
	0x00, //      
	0x00, //      

	// @568 'g' (5 pixels wide)
	0x00, //      
	0x18, //      
	0x25, //   ###
	0x25, //  #  #
	0x3E, //  #  #
	0x00, //   ###
	0x00, //     #
	0x00, //   ## 

	// @576 'h' (5 pixels wide)
	0x84, // ##   
	0xFC, //  #   
	0x24, //  ### 
	0x20, //  #  #
	0x1C, //  #  #
	0x00, // ### #
	0x00, //      
	0x00, //      

	// @584 'i' (5 pixels wide)
	0x00, //   #  
	0x24, //      
	0xBC, //  ##  
	0x04, //   #  
	0x00, //   #  
	0x00, //  ### 
	0x00, //      
	0x00, //      

	// @592 'j' (5 pixels wide)
	0x00, //   #  
	0x21, //      
	0xA1, //  ### 
	0x3F, //    # 
	0x00, //    # 
	0x00, //    # 
	0x00, //    # 
	0x00, //  ### 

	// @600 'k' (5 pixels wide)
	0x84, // ##   
	0xFC, //  #   
	0x10, //  # ##
	0x3C, //  ### 
	0x24, //  # # 
	0x00, // ## ##
	0x00, //      
	0x00, //      

	// @608 'l' (5 pixels wide)
	0x00, //  ##  
	0x84, //   #  
	0xFC, //   #  
	0x04, //   #  
	0x00, //   #  
	0x00, //  ### 
	0x00, //      
	0x00, //      

	// @616 'm' (5 pixels wide)
	0x3C, //      
	0x20, //      
	0x1C, // ## # 
	0x20, // # # #
	0x1C, // # # #
	0x00, // # # #
	0x00, //      
	0x00, //      

	// @624 'n' (5 pixels wide)
	0x24, //      
	0x3C, //      
	0x20, // #### 
	0x20, //  #  #
	0x1C, //  #  #
	0x00, // ##  #
	0x00, //      
	0x00, //      

	// @632 'o' (5 pixels wide)
	0x00, //      
	0x18, //      
	0x24, //   ## 
	0x24, //  #  #
	0x18, //  #  #
	0x00, //   ## 
	0x00, //      
	0x00, //      

	// @640 'p' (5 pixels wide)
	0x21, //      
	0x3F, //      
	0x25, // #### 
	0x24, //  #  #
	0x18, //  #  #
	0x00, //  ### 
	0x00, //  #   
	0x00, // ###  

	// @648 'q' (5 pixels wide)
	0x00, //      
	0x18, //      
	0x24, //   ###
	0x25, //  #  #
	0x3F, //  #  #
	0x00, //   ###
	0x00, //     #
	0x00, //    ##

	// @656 'r' (5 pixels wide)
	0x00, //      
	0x24, //      
	0x3C, //  ####
	0x24, //   #  
	0x20, //   #  
	0x00, //  ### 
	0x00, //      
	0x00, //      

	// @664 's' (5 pixels wide)
	0x00, //      
	0x04, //      
	0x34, //   ## 
	0x28, //   #  
	0x00, //    # 
	0x00, //  ##  
	0x00, //      
	0x00, //      

	// @672 't' (5 pixels wide)
	0x20, //      
	0x78, //  #   
	0x24, // #### 
	0x24, //  #   
	0x08, //  #  #
	0x00, //   ## 
	0x00, //      
	0x00, //      

	// @680 'u' (5 pixels wide)
	0x20, //      
	0x38, //      
	0x04, // ## ##
	0x24, //  #  #
	0x3C, //  #  #
	0x00, //   ###
	0x00, //      
	0x00, //      

	// @688 'v' (5 pixels wide)
	0x20, //      
	0x30, //      
	0x0C, // ##  #
	0x0C, //  #  #
	0x30, //   ## 
	0x00, //   ## 
	0x00, //      
	0x00, //      

	// @696 'w' (5 pixels wide)
	0x38, //      
	0x24, //      
	0x18, // ## ##
	0x24, // # # #
	0x38, // # # #
	0x00, //  # # 
	0x00, //      
	0x00, //      

	// @704 'x' (5 pixels wide)
	0x00, //      
	0x24, //      
	0x18, //  #  #
	0x18, //   ## 
	0x24, //   ## 
	0x00, //  #  #
	0x00, //      
	0x00, //      

	// @712 'y' (5 pixels wide)
	0x20, //      
	0x39, //      
	0x07, // ## ##
	0x38, //  # # 
	0x20, //  # # 
	0x00, //   #  
	0x00, //   #  
	0x00, //  ##  

	// @720 'z' (5 pixels wide)
	0x00, //      
	0x34, //      
	0x2C, //  ####
	0x34, //  # # 
	0x2C, //   # #
	0x00, //  ####
	0x00, //      
	0x00, //      

	// @728 '{' (5 pixels wide)
	0x00, //    # 
	0x10, //   #  
	0x7C, //   #  
	0x82, //  ##  
	0x00, //   #  
	0x00, //   #  
	0x00, //    # 
	0x00, //      

	// @736 '|' (5 pixels wide)
	0x00, //   #  
	0x00, //   #  
	0xFE, //   #  
	0x00, //   #  
	0x00, //   #  
	0x00, //   #  
	0x00, //   #  
	0x00, //      

	// @744 '}' (5 pixels wide)
	0x00, //  #   
	0x82, //   #  
	0x7C, //   #  
	0x10, //   ## 
	0x00, //   #  
	0x00, //   #  
	0x00, //  #   
	0x00, //      

	// @752 '~' (5 pixels wide)
	0x00, //      
	0x08, //      
	0x10, //      
	0x08, //   # #
	0x10, //  # # 
	0x00, //      
	0x00, //      
	0x00, //      
};

sFONT Font8 = {
  Font8_Table,
  5, /* Width */
  8, /* Height */
};

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
