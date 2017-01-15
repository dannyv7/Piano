# Piano
Software written for TI TM4C123 Launchpad attached to a 6-bit DAC to emulate a 4 key piano.
Soundwave values were create from Octave, exported to Excel files and used in arrays.
Output sound depended on the frequency of the SysTick interrupt, which serviced an Interrupt Service Routine that wrote the appropriate 
soundwave value to the Digital to Analog Converter (DAC). Playing the song uses a second Interrupt Service, Timer0 in conjunction with 
SysTick interrupts.
  
Features of the Piano include:  
- 9 Distinct notes mapped to piano "key"/key combinations      
- Ability to switch between 5 instrument voices: Bassoon, Flute, French Horn, Trumpet, and Piano  
- Pressing the play song key will automatically loop Greensleeves (disables piano keys however) until it is pressed again  

Hardware used:  
- 4x Buttons - "piano keys" (mapped to PortA2-PortA5)
- 6x Buttons - instrument selection and song start/stop (mapped to PortE0-PortE5)
- 6x Resistors (1:2:4:8:16:32 ratio) - 6-bit Digital to Analog Converter (mapped to PortB0-PortB5)
