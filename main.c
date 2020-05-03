// Copyright (c) 2015-19, Joe Krachey
// All rights reserved.
//
// Redistribution and use in source or binary form, with or without modification, 
// are permitted provided that the following conditions are met:
//
// 1. Redistributions in source form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimer in 
//    the documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "main.h"
#include "project_hardware_init.h"
#include "movement.h"

volatile bool ALERT_SHIP = true;
volatile bool ALERT_ASTEROID = true;

//*****************************************************************************
//*****************************************************************************
void DisableInterrupts(void)
{
  __asm {
         CPSID  I
  }
}

//*****************************************************************************
//*****************************************************************************
void EnableInterrupts(void)
{
  __asm {
    CPSIE  I
  }
}


//*****************************************************************************
//*****************************************************************************

int 
main(void)
{
		  bool touch_start = false;
		  bool game_over = false;
		  init_hardware();
	    while(!touch_start) {
		    init_start_screen();
		    touch_start = touch_label();
	    }
	
	  EnableInterrupts();
	
	  while(!game_over)  {
			if(ALERT_SHIP)  {
					ALERT_SHIP = false;
					lcd_draw_image(SHIP_X_COORD, spaceship_WidthPixels, SHIP_Y_COORD, spaceship_HeightPixels, spaceship_Bitmaps, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
				game_over = check_game_over(SHIP_X_COORD, SHIP_Y_COORD, spaceship_HeightPixels,spaceship_WidthPixels,ASTEROID_1_X_COORD, ASTEROID_1_Y_COORD, asteriod_HeightPixels, asteriod_WidthPixels, ASTEROID_2_X_COORD, ASTEROID_2_Y_COORD, ASTEROID_3_X_COORD, ASTEROID_3_Y_COORD, ASTEROID_4_X_COORD, ASTEROID_4_Y_COORD, ASTEROID_5_X_COORD, ASTEROID_5_Y_COORD);
			}

		  if(ALERT_ASTEROID) {
          ALERT_ASTEROID = false;
          lcd_draw_image(ASTEROID_1_X_COORD,asteriod_WidthPixels,ASTEROID_1_Y_COORD,asteriod_HeightPixels,asteriod_Bitmaps, LCD_COLOR_GRAY,LCD_COLOR_BLACK); 
          lcd_draw_image(ASTEROID_2_X_COORD,asteriod_WidthPixels,ASTEROID_2_Y_COORD,asteriod_HeightPixels,asteriod_Bitmaps, LCD_COLOR_GRAY,LCD_COLOR_BLACK); 
          lcd_draw_image(ASTEROID_3_X_COORD,asteriod_WidthPixels,ASTEROID_3_Y_COORD,asteriod_HeightPixels,asteriod_Bitmaps, LCD_COLOR_GRAY,LCD_COLOR_BLACK); 
          lcd_draw_image(ASTEROID_4_X_COORD,asteriod_WidthPixels,ASTEROID_4_Y_COORD,asteriod_HeightPixels,asteriod_Bitmaps, LCD_COLOR_GRAY,LCD_COLOR_BLACK); 
          lcd_draw_image(ASTEROID_5_X_COORD,asteriod_WidthPixels,ASTEROID_5_Y_COORD,asteriod_HeightPixels,asteriod_Bitmaps, LCD_COLOR_GRAY,LCD_COLOR_BLACK); 

				game_over = check_game_over(SHIP_X_COORD, SHIP_Y_COORD, spaceship_HeightPixels,spaceship_WidthPixels,ASTEROID_1_X_COORD, ASTEROID_1_Y_COORD, asteriod_HeightPixels, asteriod_WidthPixels, ASTEROID_2_X_COORD, ASTEROID_2_Y_COORD, ASTEROID_3_X_COORD, ASTEROID_3_Y_COORD, ASTEROID_4_X_COORD, ASTEROID_4_Y_COORD, ASTEROID_5_X_COORD, ASTEROID_5_Y_COORD);
      }    
			clear_trail();
	}
	  while(1){}
	
}
