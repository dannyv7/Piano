// Lab6.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a 4-key digital piano
// MOOC lab 13 or EE319K lab6 starter
// Program written by: put your names here
// Date Created: 1/24/2015 
// Last Modified: 3/6/2015 
// Section 1-2pm     TA: Wooseok Lee
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********
//dac out to pd3 no headphones in
//
//clockspeed/(notefreq*dacdependent) 
unsigned long check1;

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "TExaS.h"
#include "Heartbeat.h"
#include "notes.h"
#include "Instrument_Select.h"
#include "song.h"

unsigned long* instrument;
unsigned long InstSel;
//unsigned long InstrumentSet[5] = {&bassoon[0], &flute[0], &horn[0], &trumpet[0], &piano[0]};
// basic functions defined at end of startup.s
void DisableInterrupts(void);							//Disable interrupts
void EnableInterrupts(void);							//Enable interrupts
unsigned long note_input;								//Initalize variable for synth input
//Create the note array
//unsigned long note[16] = {0, A, C, 0, D, 0, 0, Eb, 0, 0, 0, 0, 0, 0,0, 0};				//Change to all combos

//Create the instrument arrays
unsigned long bassoon[64] = {	
  7,8,8,8,8,8,8,8,7,7,6,	
  7,8,10,14,15,12,7,2,0,0,2,	
  3,5,7,9,11,11,10,9,7,5,	
  3,2,2,3,5,7,9,10,9,7,	
  6,5,5,5,5,5,6,6,7,7,	
  7,8,8,9,9,8,8,8,8,8,7,7	
};
unsigned long flute[64] = {  
  6,7,9,9,10,11,12,13,13,14,15,	
  15,15,15,15,14,13,13,12,11,10,9,	
  8,7,7,6,6,5,5,5,5,4,	
  4,4,4,4,4,3,3,3,3,3,	
  2,2,1,1,1,1,0,0,0,0,	
  0,0,1,1,1,2,2,3,3,4,4,5	
};
unsigned long horn[64] = {
  7,8,8,8,8,9,10,12,15,15,15,	
  13,10,7,4,3,3,3,3,3,3,3,	
  4,4,4,4,5,6,7,8,8,9,	
  9,10,11,11,12,13,13,12,12,13,	
  14,12,11,9,8,6,3,2,1,1,	
  0,1,1,1,2,2,3,4,4,6,7,7	
};
unsigned long trumpet[64] = {
  10,10,11,11,11,12,12,11,10,9,8,
  5,3,2,1,3,8,11,14,15,15,13,
  12,11,10,10,10,10,11,11,10,10,
  10,10,10,10,10,10,10,10,10,10,
  10,10,10,11,11,11,11,11,11,11,
  11,11,11,11,11,10,10,10,10,10,10,10
};
unsigned long piano[64] = {
  32,35,38,41,44,47,49,52,54,56,58,				
  59,61,62,62,63,63,63,62,62,61,59,				
  58,56,54,52,49,47,44,41,38,35,				
  32,29,26,23,20,17,15,12,10,8,				
  6,5,3,2,2,1,1,1,2,2,3,				
  5,6,8,10,12,15,17,20,23,26,29				
};
unsigned long * InstrumentSet[5] = {&bassoon[0], &flute[0], &horn[0], &trumpet[0], &piano[0]};		//Create the array for instrument addresses


int main(void){      
  TExaS_Init(SW_PIN_PE3210,DAC_PIN_PB3210,ScopeOn);    	//Bus clock at 80 MHz
  Instrument_Init();												//Initialize the switches for selecting the instrument
  Piano_Init();															//Initalize the instrument driver
  Sound_Init(0);														//Initalize the sound driver
	song_init();
  //song_init();														//Initalize the SysTick timer
  Heartbeat_Init();													//Initalize the heartbeat function
  // other initialization
  EnableInterrupts();												
  while(1){
	InstSel = Instrument_Select();						//Determine the inst\\Lab6\Lab6.c\note_inputrument to be used
	instrument = InstrumentSet[InstSel];			//Set the global variable instrument
	song_check();															//Check for song activation and enable timer interrupts
	song_stop();															//Check for song terminate and disable timer interrupts
	note_input = Piano_In();									//Read the synth input into a note
	if (TIMER0_IMR_R != 0x00000001){
		Sound_Play(note_input);	
		}
								//Play the sound that corresponds to note fq if timer interrupts are disabled
	//song_check();         
	}
}

