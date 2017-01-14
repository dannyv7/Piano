//**********Instrument_Select**********
#include <stdint.h>
#include "tm4c123gh6pm.h"

unsigned long read_select;
unsigned long selected;
extern unsigned long delay;

#define bassoon 0
#define flute		1
#define horn		2
#define trumpet	3
#define piano		4

//**********Instrument_Init**********
void Instrument_Init(void){
	SYSCTL_RCGC2_R |= 0x10;				//Initialize System Clock for PortE
	delay = SYSCTL_RCGC2_R;				//Allow system core to settle
	GPIO_PORTE_DIR_R &= ~ 0x3F;			//Set PE0 - PE5 as inputs
	GPIO_PORTE_AFSEL_R &= ~ 0x3F;			//Disable alternate functions on PE0 - PE5
	GPIO_PORTE_DEN_R |= 0x3F;			//Enable digital interfacing on PE0 - PE5
	selected = piano;					//Set the inital selected instrument to the piano
}

//*********Instrument_Select**********
unsigned long Instrument_Select(void){
	read_select = GPIO_PORTE_DATA_R & 0x1F ;	//Read user input for instrument
	switch (read_select){
		case 1:
			selected = bassoon;
			break;
		case 2:
			selected = flute;
			break;
		case 4:
			selected = horn;
			break;
		case 8:
			selected = trumpet;
			break;
		case 16:
			selected = piano;
			break;
		default:
			selected = selected;
			break;	
	}
	return selected;
}
