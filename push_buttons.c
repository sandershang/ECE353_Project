#include "push_buttons.h"

//changes the color of the ship
void change_ship_color(push_button_t push_dir) {
	switch(push_dir)
		{
			case PUSH_BUTTON_UP:
			{
				lcd_draw_image(SHIP_X_COORD, spaceship_WidthPixels, SHIP_Y_COORD, spaceship_HeightPixels, spaceship_Bitmaps, LCD_COLOR_RED, LCD_COLOR_BLACK);;
				break;
			}
			case PUSH_BUTTON_DOWN:
			{
				lcd_draw_image(SHIP_X_COORD, spaceship_WidthPixels, SHIP_Y_COORD, spaceship_HeightPixels, spaceship_Bitmaps, LCD_COLOR_GREEN, LCD_COLOR_BLACK);;
				break;
			}
			case PUSH_BUTTON_LEFT:
			{
				lcd_draw_image(SHIP_X_COORD, spaceship_WidthPixels, SHIP_Y_COORD, spaceship_HeightPixels, spaceship_Bitmaps, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
				break;
			}	
			case PUSH_BUTTON_RIGHT:
			{
				lcd_draw_image(SHIP_X_COORD, spaceship_WidthPixels, SHIP_Y_COORD, spaceship_HeightPixels, spaceship_Bitmaps, LCD_COLOR_WHITE, LCD_COLOR_BLACK);;
				break;
			}	
			default: {}
		}
}

//checks if a button is being pushed
bool debounce()
{
  static DEBOUNCE_STATES state = DEBOUNCE_ONE;
  bool pin_up, pin_down, pin_left, pin_right;

  
  pin_up = lp_io_read_pin(DIR_BTN_UP_PIN);
	pin_down = lp_io_read_pin(DIR_BTN_DOWN_PIN);
	pin_left = lp_io_read_pin(DIR_BTN_LEFT_PIN);
	pin_right = lp_io_read_pin(DIR_BTN_RIGHT_PIN);
	
  
  switch (state)
  {
    case DEBOUNCE_ONE:
    {
      if(pin_up|pin_down|pin_left|pin_right)
      {
        state = DEBOUNCE_ONE;
      }
      else
      {
        state = DEBOUNCE_1ST_ZERO;
      }
      break;
    }
    case DEBOUNCE_1ST_ZERO:
    {
      if(pin_up|pin_down|pin_left|pin_right)
      {
        state = DEBOUNCE_ONE;
      }
      else
      {
        state = DEBOUNCE_2ND_ZERO;
      }
      break;
    }
    case DEBOUNCE_2ND_ZERO:
    {
      if(pin_up|pin_down|pin_left|pin_right)
      {
        state = DEBOUNCE_ONE;
      }
      else
      {
        state = DEBOUNCE_PRESSED;
      }
      break;
    }
    case DEBOUNCE_PRESSED:
    {
      if(pin_up|pin_down|pin_left|pin_right)
      {
        state = DEBOUNCE_ONE;
      }
      else
      {
        state = DEBOUNCE_PRESSED;
      }
      break;
    }
    default:
    {
      while(1){};
    }
  }
  
  if(state == DEBOUNCE_2ND_ZERO )
  {
    return true;
  }
  else
  {
    return false;
  }
}