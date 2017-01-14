#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "notes.h"
#include "Sound.h"

struct music  {
	unsigned long notename;
	unsigned long notelength;
};
//Make song
typedef const struct music Mtyp;
unsigned long M;
unsigned long i;
Mtyp Green[40]={
	
};

void Greensleeves_Play(void){M = 0;
	for (i=0; i<40; i++){
		timer = Green[M].notelength;
		Sound_Play(Green[M].notename);
		M++;
	}
}