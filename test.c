#include "dac.h"
#include "TExaS.h"
int main(void){       
  unsigned long Data; // 0 to 15 DAC output
  TExaS_Init(SW_PIN_PE3210,DAC_PIN_PB3210,ScopeOn);    	//Bus clock at 80 MHz
  DAC_Init();
  for(;;) {
    DAC_Out(Data);
    Data = 0x0F&(Data+1); // 0,1,2...,14,15,0,1,2,...
  }
}
