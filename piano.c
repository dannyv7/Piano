// Piano.c
// This software configures the off-board piano keys
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 8/25/2014 
// Last Modified: 3/6/2015 
// Section 1-2pm     TA: Wooseok Lee
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data
#include <stdint.h>
#include "tm4c123gh6pm.h"


unsigned long read_keys;
extern unsigned long delay;

// **************Piano_Init*********************
// Initialize piano key inputs, called once 
// Input: none 
// Output: none
void Piano_Init(void){
	SYSCTL_RCGC2_R |= 0x01;					//Initalize System Clock for PortA
	delay = SYSCTL_RCGC2_R;					//Allow clock core to settle
	GPIO_PORTA_DIR_R &= ~ 0x3C;					//Set PA2-PA5 as inputs
	GPIO_PORTA_AFSEL_R &= ~ 0x3C;					//Disable alternate functions on PA2-PA5
	GPIO_PORTA_DEN_R |= 0x3C;					//Enable digital interfacing on PA2-PA5
}

// **************Piano_In*********************
// Input from piano key inputs 
// Input: none 
// Output: 0 to 8
// 0x01 is just Key0, 0x02 is just Key1, 0x04 is just Key2
uint32_t Piano_In(void){
	read_keys = GPIO_PORTA_DATA_R;				//Set the frequency for the note
	read_keys >>= 2;									//Transform input into 4bit number
	return read_keys; 							// replace this line with actual code
}
