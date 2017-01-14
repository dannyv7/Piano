//Heartbeat software
#include <stdint.h>
#include "tm4c123gh6pm.h"

unsigned long delay;

//*************Heartbeat_Init***************
//Initialize the onboard LED, called once
//Input: None
//Output: None
void Heartbeat_Init(void){
	SYSCTL_RCGC2_R |= 0x20;				//Initalize System Clock for PortF
	delay = SYSCTL_RCGC2_R;				//Allow clock core to settle
	GPIO_PORTF_DIR_R |= 0x04;				//PF1 as output
	GPIO_PORTF_DEN_R |= 0x04;				//Enable digital interfacing on PF1
}
//************Heartbeat*********************
//Toggle the LED for the Heartbeat
//Input: None
//Output: None
void Heartbeat(void){
	GPIO_PORTF_DATA_R ^= 0x04;				//Toggle LED light
}
