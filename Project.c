#include "hw3.h"

volatile uint16_t SHIP_X_COORD = 190;
volatile uint16_t SHIP_Y_COORD = 270;
volatile uint16_t INVADER_X_COORD = 50;
volatile uint16_t INVADER_Y_COORD = 40;
volatile bool ALERT_SPACE_SHIP = true;
volatile bool ALERT_INVADER = true;
char STUDENT_NAME[] = "Avi Silverman & Sanders Hang";

typedef struct
{
    int top;
    int bottom;
    int left;
    int right;
} Rectangle;

//*****************************************************************************
// Determines if any part of the image would be off the screen if the image
// is moved in the specified direction.
//*****************************************************************************
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
			if(y_coord - (image_height/2) - 1 > 0)
				return false;
			break;
		}
		case PS2_DIR_DOWN: {
			if(y_coord + (image_height/2) + 1 < 320)
				return false;
			break;
		}
		case PS2_DIR_LEFT: {
			if(x_coord - (image_width/2) - 1 > 0)
				return false;
			break;
		}
		case PS2_DIR_RIGHT: {
			if(x_coord + (image_width/2) + 1 < 240)
				return false;
			break;
		}
	}
	return true;
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
			*y_coord = *y_coord - 1;
			break;
			}
		case PS2_DIR_DOWN: {
			*y_coord = *y_coord + 1;
			break;
			}
		case PS2_DIR_LEFT: {
			*x_coord = *x_coord - 1;
			break;
			}
		case PS2_DIR_RIGHT: {
			*x_coord = *x_coord + 1;
			break;
			}
	}
   return;
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
        volatile uint16_t invader_x_coord, 
        volatile uint16_t invader_y_coord, 
        uint8_t invader_height, 
        uint8_t invader_width
)
{
	// Define the sides of the ship and invader
	uint16_t ship_top = ship_y_coord - ship_height/2;
	uint16_t ship_bottom = ship_y_coord + ship_height/2;
	uint16_t ship_left = ship_x_coord - ship_width/2;
	uint16_t ship_right = ship_x_coord + ship_width/2;
	
	uint16_t invader_top = invader_y_coord - invader_height/2;
	uint16_t invader_bottom = invader_y_coord + invader_height/2;
	uint16_t invader_left = invader_x_coord - invader_width/2;
	uint16_t invader_right = invader_x_coord + invader_width/2;
	
	//Returns false if images are not touching
	if(ship_bottom < invader_top || ship_top > invader_bottom || ship_left > invader_right || ship_right < invader_left)
		return false;
	
	return true;
}
