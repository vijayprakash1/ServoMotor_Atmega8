/*
 *ServoMotor_Atmega8.c
 *
 * Created: 11-03-2016 11.44.58 AM
 * Author : Vijay
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
volatile unsigned int pulse=0;

ISR(INT0_vect)
{
	PORTB=0x08;
	_delay_ms(1);
	PORTB=0x00;
	_delay_ms(1);
	pulse++;
}



int main(void)
{
	DDRB=0xFF;
	DDRD=0xFB;
	PORTD=0x04;
	GICR|=(1<<INT0);
	MCUCR|=(1<<ISC01)|(1<<ISC00);
	sei();
	ICR1=26665;
	TCCR1A|=(1<<COM1A1)|(1<<WGM11);
	TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS10);
	
	while (1)
	{
		
		if (pulse==5)
		{
			pulse=0;
			PORTC|= (1<<PORTC1);
			_delay_ms(100);
			OCR1A=1950;         // you can set as per your angle needs 
			_delay_ms(200);
			OCR1A=1000;        // zero angle or position
			_delay_ms(200);
			PORTC&= ~(1<<PORTC1);
			_delay_ms(100);
		}
}
}
