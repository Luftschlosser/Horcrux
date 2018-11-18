#include <avr/io.h>


//Forward-Declarations:
inline void disableAnalogPeriphery();
inline void setClock128kHz();

//Main
int main( void )
{
	disableAnalogPeriphery();
	setClock128kHz();


	DDRB = (1 << DDB2);
	while (1)
	{
		PORTB = ~PORTB;
		for (uint16_t i = 0; i < 1000; i++)
		{
			asm volatile ("nop\n");
		}
	}
}

//Subroutines
inline void disableAnalogPeriphery()
{
	PRR = (1 << PRADC);						//Disable ADC.
	DIDR0 = ((1 << ADC0D) | (1 << ADC1D));	//Disable digital Inputs on analog Comparator-Pins.
	ACSR = (1 << ACD);						//Disable Analog Comparator.
}
inline void setClock128kHz()
{
	CCP = 0xD8;					//Write Configuration Change Protection Register signature.
	CLKMSR = (1 << CLKMS0);		//Set Clocksource to Internal 128 kHz Oscillator (WDT Oscillator).
	CLKPSR = 0;					//Set Clock-Prescale 0.
}
