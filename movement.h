#ifndef __MOVEMENT_H__
#define __MOVEMENT_H__ 
#include "gpio_port.h"
#include "ps2.h"
#include "lcd.h"
#include "timers.h"

 extern volatile uint16_t SHIP_X_COORD;
 extern volatile uint16_t SHIP_Y_COORD;
 
extern volatile uint16_t ASTEROID_1_X_COORD;
extern volatile uint16_t ASTEROID_1_Y_COORD;

extern volatile uint16_t ASTEROID_2_X_COORD;
extern volatile uint16_t ASTEROID_2_Y_COORD;

extern volatile uint16_t ASTEROID_3_X_COORD;
extern volatile uint16_t ASTEROID_3_Y_COORD;

extern volatile uint16_t ASTEROID_4_X_COORD;
extern volatile uint16_t ASTEROID_4_Y_COORD;

extern volatile uint16_t ASTEROID_5_X_COORD;
extern volatile uint16_t ASTEROID_5_Y_COORD;
 
 
typedef enum{
  PS2_DIR_UP,
  PS2_DIR_DOWN,
  PS2_DIR_LEFT,
  PS2_DIR_RIGHT,
  PS2_DIR_CENTER,
  PS2_DIR_INIT,
} PS2_DIR_t;

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
);

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
);
				
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
);
				
#endif