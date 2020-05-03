#include "touchscreen.h"

#define START_LABEL_TOP 150
#define START_LABEL_BOTTOM 190
#define START_LABEL_RIGHT 170
#define START_LABEL_LEFT 70

bool touch_label(){
	uint8_t touch_event;
	uint16_t x_value;
	uint16_t y_value;
	
		touch_event = ft6x06_read_td_status();
		if(touch_event > 0 ) {
			x_value = ft6x06_read_x();
			y_value = ft6x06_read_y();
			printf("%d, %d\n", x_value, y_value);
			if(x_value < START_LABEL_RIGHT && x_value > START_LABEL_LEFT) {
				if(y_value > START_LABEL_TOP && y_value < START_LABEL_BOTTOM){
					lcd_clear_screen(LCD_COLOR_BLACK);
					game_screen();
					//break;
					return true;
				}
			}
		}
	return false;
}

void init_start_screen(){
		lcd_draw_image(120, titleLabel_WidthPixels, 110, titleLabel_HeightPixels, titleLabel_Bitmaps, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
    lcd_draw_image(120, startLabel_WidthPixels, 170, startLabel_HeightPixels, startLabel_Bitmaps, LCD_COLOR_GREEN, LCD_COLOR_BLACK);
		lcd_draw_image(SHIP_X_COORD, spaceship_WidthPixels, SHIP_Y_COORD, spaceship_HeightPixels, spaceship_Bitmaps, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
}

void game_screen() {
		lcd_draw_image(SHIP_X_COORD, spaceship_WidthPixels, SHIP_Y_COORD, spaceship_HeightPixels, spaceship_Bitmaps, LCD_COLOR_WHITE, LCD_COLOR_BLACK);	
		lcd_draw_image(ASTEROID_1_X_COORD,asteriod_WidthPixels,ASTEROID_1_Y_COORD,asteriod_HeightPixels,asteriod_Bitmaps, LCD_COLOR_GRAY,LCD_COLOR_BLACK); 
		lcd_draw_image(ASTEROID_2_X_COORD,asteriod_WidthPixels,ASTEROID_2_Y_COORD,asteriod_HeightPixels,asteriod_Bitmaps, LCD_COLOR_GRAY,LCD_COLOR_BLACK); 
		lcd_draw_image(ASTEROID_3_X_COORD,asteriod_WidthPixels,ASTEROID_3_Y_COORD,asteriod_HeightPixels,asteriod_Bitmaps, LCD_COLOR_GRAY,LCD_COLOR_BLACK); 
		lcd_draw_image(ASTEROID_4_X_COORD,asteriod_WidthPixels,ASTEROID_4_Y_COORD,asteriod_HeightPixels,asteriod_Bitmaps, LCD_COLOR_GRAY,LCD_COLOR_BLACK); 
		lcd_draw_image(ASTEROID_5_X_COORD,asteriod_WidthPixels,ASTEROID_5_Y_COORD,asteriod_HeightPixels,asteriod_Bitmaps, LCD_COLOR_GRAY,LCD_COLOR_BLACK); 
}
//Clear the trail of pixel left behind by the left side of the ship
void clear_trail() {
		lcd_draw_rectangle(SHIP_X_COORD-(spaceship_WidthPixels/2)-2, 2, SHIP_Y_COORD-(spaceship_HeightPixels/2), spaceship_HeightPixels, LCD_COLOR_BLACK);
}
