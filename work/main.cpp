/*
 * Feuertopf.cpp
 *
 * Created: 10.11.2016 15:47:03
 * Author : tobid
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <iso646.h>
#include <avr/interrupt.h>

unsigned char PWM_val_gelb = 100;
unsigned char PWM_val_rot = 100;
unsigned char i = 0;
unsigned char n = 10;
unsigned char flacker[20] = {10,20,-30,-10,20,40,20,10,5,-10,20,40,20,10,5,10,20,-30,-10,20};

void init(){
	DDRB   |= (1 << PB1);	// output on PB2 PIN-14 - LED Gelb
	DDRB   |= (1 << PB0);	// output on PD5 PIN-9 - LED Rot
	
	
	TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);  // phase correct PWM mode
	
	OCR0A = 100;		//Set Grund
	OCR0B = 100;
}

int main(void)
{
   	init();
   	
   	
   	
   	TCCR0B |= (1 << CS01);			// clock source = CLK/8, start PWM
   	
   	while(1) {
	   	if(i<20)
	   		i=i+1;
	   	else
	   		i=0;
			   
	   	if(n<20)
	   		n=n+1;
	   	else
			n=0;
			
	   	OCR0A = (PWM_val_gelb + flacker[i]);
	   	OCR0B = (PWM_val_rot + flacker[n]);
	   	
	   	_delay_ms(50);
   	}
   	return 1;
}

