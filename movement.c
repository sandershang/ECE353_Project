#include "movement.h"

volatile uint16_t SHIP_X_COORD = 120;
volatile uint16_t SHIP_Y_COORD = 290;

volatile uint16_t ASTEROID_1_X_COORD = 60;
volatile uint16_t ASTEROID_1_Y_COORD = 230;

volatile uint16_t ASTEROID_2_X_COORD = 60;
volatile uint16_t ASTEROID_2_Y_COORD = 180;

volatile uint16_t ASTEROID_3_X_COORD = 60;
volatile uint16_t ASTEROID_3_Y_COORD = 130;

volatile uint16_t ASTEROID_4_X_COORD = 60;
volatile uint16_t ASTEROID_4_Y_COORD = 80;

volatile uint16_t ASTEROID_5_X_COORD = 60;
volatile uint16_t ASTEROID_5_Y_COORD = 30;

bool contact_edge(
    volatile PS2_DIR_t direction,
    volatile uint16_t x_coord, 
    volatile uint16_t y_coord, 
    uint8_t image_height, 
    uint8_t image_width
)
{
	//Returns true if an edge has been contacted
	switch(direction) {
		case PS2_DIR_UP: {
			if(y_coord - (image_height/2) - 1 < 1)
				return true;
			break;
		}
		case PS2_DIR_DOWN: {
			if(y_coord + (image_height/2) + 1 > 319)
				return true;
			break;
		}
		case PS2_DIR_LEFT: {
			if(x_coord - (image_width/2) - 1 < 1)
				return true;
			break;
		}
		case PS2_DIR_RIGHT: {
			if(x_coord + (image_width/2) + 1 > 239)
				return true;
			break;
		}
		default: {}
	}
	return false;
}

//*****************************************************************************
// Moves the image by one pixel in the provided direction.  The second and 
// third parameter should modify the current location of the image (pass by
// reference)
//*****************************************************************************
void move_image(
        volatile PS2_DIR_t direction,
        volatile uint16_t *x_coord, 
        volatile uint16_t *y_coord, 
        uint8_t image_height, 
        uint8_t image_width
)
{
	switch(direction) {
		case PS2_DIR_UP: {
			*y_coord = *y_coord - 2;
			break;
			}
		case PS2_DIR_DOWN: {
			*y_coord = *y_coord + 2;
			break;
			}
		case PS2_DIR_LEFT: {
			*x_coord = *x_coord - 2;
			break;
			}
		case PS2_DIR_RIGHT: {
			*x_coord = *x_coord + 2;
			break;
			}
		default: {}
	}
   return;
}

bool check_game_over_each(
        volatile uint16_t ship_x_coord, 
        volatile uint16_t ship_y_coord, 
        uint8_t ship_height, 
        uint8_t ship_width,
        volatile uint16_t asteroid_x_coord, 
        volatile uint16_t asteroid_y_coord, 
        uint8_t asteroid_height, 
        uint8_t asteroid_width
)
{
	// Define the sides of the ship and asteroid
	uint16_t ship_top = ship_y_coord - ship_height/2;
	uint16_t ship_bottom = ship_y_coord + ship_height/2;
	uint16_t ship_left = ship_x_coord - ship_width/2;
	uint16_t ship_right = ship_x_coord + ship_width/2;
	
	uint16_t asteroid_top = asteroid_y_coord - asteroid_height/2;
	uint16_t asteroid_bottom = asteroid_y_coord + asteroid_height/2;
	uint16_t asteroid_left = asteroid_x_coord - asteroid_width/2;
	uint16_t asteroid_right = asteroid_x_coord + asteroid_width/2;
	
	//Returns false if images are not touching
	if(ship_bottom < asteroid_top || ship_top > asteroid_bottom || ship_left > asteroid_right || ship_right < asteroid_left)
		return false;
	
	return true;
}

//*****************************************************************************
// Determines is any portion of the two images are overlapping.  An image is
// considered to be overlapping if the two rectangles determined by the image
// height and widths are overlapping.  An overlap occurs even if the area that
// overlaps are portions of the images where the pixels do not display on the
// screen.
//*****************************************************************************
bool check_game_over(
        volatile uint16_t ship_x_coord, 
        volatile uint16_t ship_y_coord, 
        uint8_t ship_height, 
        uint8_t ship_width,
				volatile uint16_t asteroid_1_x_coord, 
        volatile uint16_t asteroid_1_y_coord, 
				uint8_t asteroid_height, 
        uint8_t asteroid_width,
				volatile uint16_t asteroid_2_x_coord, 
        volatile uint16_t asteroid_2_y_coord, 
				volatile uint16_t asteroid_3_x_coord, 
        volatile uint16_t asteroid_3_y_coord, 
				volatile uint16_t asteroid_4_x_coord, 
        volatile uint16_t asteroid_4_y_coord, 
				volatile uint16_t asteroid_5_x_coord, 
        volatile uint16_t asteroid_5_y_coord
)
{
	// Define the sides of the ship and asteroid
	uint16_t ship_top = ship_y_coord - ship_height/2;
	uint16_t ship_bottom = ship_y_coord + ship_height/2;
	uint16_t ship_left = ship_x_coord - ship_width/2;
	uint16_t ship_right = ship_x_coord + ship_width/2;
	
	uint16_t asteroid_1_top = asteroid_1_y_coord - asteroid_height/2;
	uint16_t asteroid_1_bottom = asteroid_1_y_coord + asteroid_height/2;
	uint16_t asteroid_1_left = asteroid_1_x_coord - asteroid_width/2;
	uint16_t asteroid_1_right = asteroid_1_x_coord + asteroid_width/2;
	
	uint16_t asteroid_2_top = asteroid_2_y_coord - asteroid_height/2;
	uint16_t asteroid_2_bottom = asteroid_2_y_coord + asteroid_height/2;
	uint16_t asteroid_2_left = asteroid_2_x_coord - asteroid_width/2;
	uint16_t asteroid_2_right = asteroid_2_x_coord + asteroid_width/2;
	
	uint16_t asteroid_3_top = asteroid_3_y_coord - asteroid_height/2;
	uint16_t asteroid_3_bottom = asteroid_3_y_coord + asteroid_height/2;
	uint16_t asteroid_3_left = asteroid_3_x_coord - asteroid_width/2;
	uint16_t asteroid_3_right = asteroid_3_x_coord + asteroid_width/2;
	
	uint16_t asteroid_4_top = asteroid_4_y_coord - asteroid_height/2;
	uint16_t asteroid_4_bottom = asteroid_4_y_coord + asteroid_height/2;
	uint16_t asteroid_4_left = asteroid_4_x_coord - asteroid_width/2;
	uint16_t asteroid_4_right = asteroid_4_x_coord + asteroid_width/2;
	
	uint16_t asteroid_5_top = asteroid_5_y_coord - asteroid_height/2;
	uint16_t asteroid_5_bottom = asteroid_5_y_coord + asteroid_height/2;
	uint16_t asteroid_5_left = asteroid_5_x_coord - asteroid_width/2;
	uint16_t asteroid_5_right = asteroid_5_x_coord + asteroid_width/2;
	
	
	//Returns false if images are not touching
//	if(ship_bottom < asteroid_1_top || ship_top > asteroid_1_bottom || ship_left > asteroid_1_right || ship_right < asteroid_1_left)
//		return false;
//	if(ship_bottom < asteroid_2_top || ship_top > asteroid_2_bottom || ship_left > asteroid_2_right || ship_right < asteroid_2_left)
//		return false;
//	if(ship_bottom < asteroid_3_top || ship_top > asteroid_3_bottom || ship_left > asteroid_3_right || ship_right < asteroid_3_left)
//		return false;
//	if(ship_bottom < asteroid_4_top || ship_top > asteroid_4_bottom || ship_left > asteroid_4_right || ship_right < asteroid_4_left)
//		return false;
//	if(ship_bottom < asteroid_5_top || ship_top > asteroid_5_bottom || ship_left > asteroid_5_right || ship_right < asteroid_5_left)
//		return false;

//	if(ship_bottom < asteroid_1_top || ship_top > asteroid_1_bottom || ship_left > asteroid_1_right || ship_right < asteroid_1_left || 
//		ship_bottom < asteroid_2_top || ship_top > asteroid_2_bottom || ship_left > asteroid_2_right || ship_right < asteroid_2_left  ||
//	  ship_bottom < asteroid_3_top || ship_top > asteroid_3_bottom || ship_left > asteroid_3_right || ship_right < asteroid_3_left  ||
//	  ship_bottom < asteroid_4_top || ship_top > asteroid_4_bottom || ship_left > asteroid_4_right || ship_right < asteroid_4_left  ||
//	  ship_bottom < asteroid_5_top || ship_top > asteroid_5_bottom || ship_left > asteroid_5_right || ship_right < asteroid_5_left)
//		return false;
//	else 
//	  return true;
	
//	if(ship_bottom < asteroid_1_top && ship_top > asteroid_1_bottom && ship_left > asteroid_1_right && ship_right < asteroid_1_left && 
//		ship_bottom < asteroid_2_top && ship_top > asteroid_2_bottom && ship_left > asteroid_2_right && ship_right < asteroid_2_left  &&
//	  ship_bottom < asteroid_3_top && ship_top > asteroid_3_bottom && ship_left > asteroid_3_right && ship_right < asteroid_3_left  &&
//	  ship_bottom < asteroid_4_top && ship_top > asteroid_4_bottom && ship_left > asteroid_4_right && ship_right < asteroid_4_left  &&
//	  ship_bottom < asteroid_5_top && ship_top > asteroid_5_bottom && ship_left > asteroid_5_right && ship_right < asteroid_5_left)
//		return true;
//	else 
//	  return false;

	//Returns false if images are not touching
//	if(ship_bottom < asteroid_1_top && ship_top > asteroid_1_bottom && ship_left > asteroid_1_right && ship_right < asteroid_1_left)
//		return true;

//		return false;

	if((ship_bottom < asteroid_1_top || ship_top > asteroid_1_bottom || ship_left > asteroid_1_right || ship_right < asteroid_1_left) && 
		(ship_bottom < asteroid_2_top || ship_top > asteroid_2_bottom || ship_left > asteroid_2_right || ship_right < asteroid_2_left)  &&
	  (ship_bottom < asteroid_3_top || ship_top > asteroid_3_bottom || ship_left > asteroid_3_right || ship_right < asteroid_3_left)  &&
	  (ship_bottom < asteroid_4_top || ship_top > asteroid_4_bottom || ship_left > asteroid_4_right || ship_right < asteroid_4_left)  &&
	  (ship_bottom < asteroid_5_top || ship_top > asteroid_5_bottom || ship_left > asteroid_5_right || ship_right < asteroid_5_left))
		return false;
	else 
	  return true;
}

