
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "notes.h"
#include "Sound.h"
#include "greensleeves.h"
#include "Heartbeat.h"

unsigned long M;
extern unsigned long check1;
unsigned long check2;

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode
//stuff
//Establish struct for song
struct music  {
	unsigned long notename;
	unsigned long notelength;
};
//Make song
typedef const struct music MTyp;
unsigned long M;
unsigned long i;
MTyp Green[38]={
	{9, qtr}, {13, half}, {2, qtr}, {12, half}, {8, qtr}, {12, qtr}, {2, half}, {1, qtr}, {10, qtr}, {9, qtr}, {1, qtr}, {13, half},
	{9, qtr}, {9, qtr}, {10, qtr}, {9, qtr}, {1, half}, {10, qtr}, {4, half}, {9, qtr}, {13, half}, {2, qtr}, {12, half}, {8, qtr}, 
  {12, qtr},{2, half}, {1, qtr}, {10, qtr}, {9, qtr}, {1, qtr}, {13, qtr}, {1, qtr}, {9, qtr}, {10, qtr}, {11, qtr}, {10, qtr}, 
  {9, qtr},{9, half}};

//Initialize song buttons
void song_init(void){long sr;
//enable timer
  sr = StartCritical(); 
  SYSCTL_RCGCTIMER_R |= 0x01;   // 0) activate TIMER0
  TIMER0_CTL_R = 0x00000000;    // 1) disable TIMER0A during setup
  TIMER0_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER0_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER0_TAILR_R = ((80000000/16)-1);    // 4) reload value
  TIMER0_TAPR_R = 0;            // 5) bus clock resolution
  TIMER0_ICR_R = 0x00000001;    // 6) clear TIMER0A timeout flag
  TIMER0_IMR_R = 0x00000000;    // 7) arm timeout interrupt
  NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x80000000; // 8) priority 4
// interrupts enabled in the main program after all devices initialized
// vector number 35, interrupt number 19
  NVIC_EN0_R = 1<<19;           // 9) enable IRQ 19 in NVIC
  TIMER0_CTL_R = 0x00000001;    // 10) enable TIMER0A
  EndCritical(sr);
}
void song_play(void){
    TIMER0_IMR_R = 0x00000001;
		
}
void song_stop(void){
	if((GPIO_PORTE_DATA_R & 0x20) == 0){
	//do nothing
     }
	else{
		TIMER0_IMR_R = 0x000000000;
	//button pressed, stop song
	//disable interrupts
	}	//return to 
}

//Check to play song or not
void song_check(void){long read_song;
	read_song = (GPIO_PORTA_DATA_R & 0x0C);
	if(read_song == 12){
		song_play();
	}
}
//Play song

//Play Greensleeves
void Timer0A_Handler(void){
	TIMER0_ICR_R = TIMER_ICR_TATOCINT;// acknowledge timer0A timeout	
	check1 = (Green[M].notename);
	//check2 = (Green[M].notelength);
	Sound_Play(Green[M].notename);
	TIMER0_TAILR_R = 75000*(Green[M].notelength);
	M = (M+1)%38;
	Heartbeat();
}
