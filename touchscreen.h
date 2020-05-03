#ifndef __SCREEN_H__
#define __SCREEN_H__ 
#include "ft6x06.h"
#include "lcd.h"
#include "images.h"
#include "movement.h"

bool touch_label();

void init_start_screen();

void game_screen();
void clear_trail();

#endif