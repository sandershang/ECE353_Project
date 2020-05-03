#ifndef _PUSHBUTTONS_H_
#define _PUSHBUTTONS_H_


#include "launchpad_io.h"
#include "lcd.h"
#include "io_expander.h"
#include "images.h"
#include "main.h"
#include "project_interrupts.h"

typedef enum{
  PUSH_BUTTON_UP,
	PUSH_BUTTON_DOWN,
	PUSH_BUTTON_LEFT,
	PUSH_BUTTON_RIGHT,
	PUSH_BUTTON_NONE
} push_button_t;

typedef enum 
{
  DEBOUNCE_ONE,
  DEBOUNCE_1ST_ZERO,
  DEBOUNCE_2ND_ZERO,
  DEBOUNCE_PRESSED
} DEBOUNCE_STATES;

void change_ship_color(push_button_t push_dir);
bool check_button_press();
bool debounce();
#endif