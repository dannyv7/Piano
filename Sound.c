// Sound.c
// This module contains the SysTick ISR that plays sound
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
#include "dac.h"
#include "tm4c123gh6pm.h"
#include "notes.h"
#include "Heartbeat.h"
#include "SysTickInts.h"

#define NVIC_ST_CTRL_CLK_SRC    0x00000004  // Clock Source
#define NVIC_ST_CTRL_INTEN      0x00000002  // Interrupt enable
#define NVIC_ST_CTRL_ENABLE     0x00000001  // Counter mode
extern unsigned long* instrument;
unsigned long idx = 0;

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

//Create the note array
unsigned long note[16] = {0, A, C, 0, D, 0, 0, 0, Eb, G, FShp, E, D5, Bb,0, 0};	

// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Called once, with sound initially off
// Input: interrupt period
//           Units to be determined by YOU
//           Maximum to be determined by YOU
//           Minimum to be determined by YOU
// Output: none
void Sound_Init(uint32_t period){
	long sr;
	//SysTick_Init(80000);
  sr = StartCritical();
  NVIC_ST_CTRL_R = 0;        					 // disable SysTick during setup
  NVIC_ST_RELOAD_R = 80000-1;					// reload value
  NVIC_ST_CURRENT_R = 0;      					// any write to current clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000; // priority 2
												// enable SysTick with core clock and interrupts
  NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE+NVIC_ST_CTRL_CLK_SRC+NVIC_ST_CTRL_INTEN;
  EndCritical(sr);
  DAC_Init();
}



// **************Sound_Play*********************
// Start sound output, and set Systick interrupt period 
// Input: interrupt period
//           Units to be determined by YOU
//           Maximum to be determined by YOU
//           Minimum to be determined by YOU
//         input of zero disable sound output
// Output: none
void Sound_Play(uint32_t period){unsigned long checker;				//Set the sound frequency
	NVIC_ST_RELOAD_R = note[period];
	checker = note[period];
}
void SysTick_Handler(void){						//Create the function to be executed on periodic interrupt
	//TIMER0_ICR_R = TIMER_ICR_TATOCINT;
	DAC_Out(instrument[idx]);
	Heartbeat();
	idx = (idx+1)%64;
}
