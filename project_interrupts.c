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
#include "project_interrupts.h"


static volatile uint16_t PS2_X_DATA = 0;
static volatile uint16_t PS2_Y_DATA = 0;
static volatile PS2_DIR_t PS2_DIR = PS2_DIR_CENTER;
static volatile push_button_t PB_DIR = PUSH_BUTTON_NONE;



//*****************************************************************************
// Returns the most current direction that was pressed.
//*****************************************************************************
PS2_DIR_t ps2_get_direction(void)
{
	//0xC00 = 2.4V
	if( PS2_X_DATA > 0xC00 )
	{
		return PS2_DIR_LEFT;
	}
	//0x400 = 0.85V
	if( PS2_X_DATA < 0x400 )
	{
		return PS2_DIR_RIGHT;
	}
	if( PS2_Y_DATA > 0xC00 )
	{
		return PS2_DIR_UP;
	}
	if( PS2_Y_DATA < 0x400 )
	{
		return PS2_DIR_DOWN;
	}
	if ( PS2_X_DATA > 0x400 && PS2_X_DATA < 0xC00 ) {
		return PS2_DIR_CENTER;
	}
	return PS2_DIR;
}

void TIMER0_Handler(void)
{
	if(debounce()){
		change_ship_color(PB_DIR);
	}
	//will need this somewhere: PB_DIR = 
	TIMER0->ICR |= TIMER_ICR_TATOCINT;
}
//*****************************************************************************
// TIMER2 ISR is used to determine when to move the ship
//*****************************************************************************
void TIMER2A_Handler(void)
{	
		bool contact = contact_edge(PS2_DIR,
																SHIP_X_COORD,
																SHIP_Y_COORD, 
																spaceship_HeightPixels, 
																spaceship_WidthPixels);
	
		if(!contact)
		{
				move_image(PS2_DIR,
									 &SHIP_X_COORD,
									 &SHIP_Y_COORD, 
									 spaceship_HeightPixels, 
									 spaceship_WidthPixels);
			
				ALERT_SHIP = true;
		}
    // Clear the interrupt
	TIMER2->ICR |= TIMER_ICR_TATOCINT;
}


//*****************************************************************************
// TIMER3 ISR is used to determine when to move the spaceship
//*****************************************************************************
void TIMER3A_Handler(void)
{}

//*****************************************************************************
// TIMER4 ISR is used to trigger the ADC
//*****************************************************************************
void TIMER4A_Handler(void)
{	
	
	ADC0->PSSI |= ADC_PSSI_SS2;
	// Clear the interrupt
	TIMER4->ICR |= TIMER_ICR_TATOCINT; 
}

//*****************************************************************************
// ADC0 SS2 ISR
//*****************************************************************************
void ADC0SS2_Handler(void)
{
	PS2_X_DATA = ADC0->SSFIFO2;
	PS2_Y_DATA = ADC0->SSFIFO2;
	PS2_DIR = ps2_get_direction();
  // Clear the interrupt
  ADC0->ISC |= ADC_ISC_IN2;
}





