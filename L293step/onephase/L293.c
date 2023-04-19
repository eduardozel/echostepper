#include <avr/io.h>
#include <util/delay.h>

#define fosc 8000000


//#define debug
//#define debug_left



#define L293_ON   PORTB |= 0b00000001
#define L293_OFF  PORTB &= 0b11111110

#define DRV1_c   PORTC &= 0b11111100
#define DRV1_r   PORTC |= 0b00000001
#define DRV1_l   PORTC |= 0b00000010


#define DRV2_c   PORTC &= 0b11110011
#define DRV2_r   PORTC |= 0b00000100
#define DRV2_l   PORTC |= 0b00001000


void stepPulse( void)
{
//  L293_ON;
//  L293_OFF;
  _delay_ms(500);
}; // stepPulse


void DRV1Off(void)
{
	DRV1_c;
} // DRV1Off

void DRV1Right(void)
{
	DRV1_c;
	DRV1_r;
} // DRV1Right

void DRV1Left(void)
{
	DRV1_c;
	DRV1_l;
} // DRV1Left


// -----------------

void DRV2Off(void)
{
	DRV2_c;
} // DRV2Off

void DRV2Right(void)
{
	DRV2_c;
	DRV2_r;
} // DRV2Right

void DRV2Left(void)
{
	DRV2_c;
	DRV2_l;
} // DRV2Left

// =================

void stepLeft( void)
{
  L293_OFF;
  L293_ON;

  DRV1Left();
  DRV2Off();
  stepPulse();

  DRV1Off();
  DRV2Right();
  stepPulse();

  DRV1Right();
  DRV2Off();
  stepPulse();

  DRV1Off();
  DRV2Left();
  stepPulse();

}; // stepLeft
// -------------------------
void stepRight( void )
{
  L293_OFF;
  L293_ON;

  DRV1Right();
  DRV2Off();
  stepPulse();

  DRV1Off();
  DRV2Right();
  stepPulse();
  
  DRV1Left();
  DRV2Off();
  stepPulse();

  DRV1Off();
  DRV2Left();
  stepPulse();

}; // stepRight



int main(void)
{
#ifndef debug
  int step;
  int steps = 3;
#endif
  DDRB |= 1 << PINB0;
  PORTB = 0b11111110;
  L293_ON;
  
  DDRC  = ( 1 << DD0 ) | ( 1 << DD1 ) | ( 1 << DD2 )  | ( 1 << DD3 ) ;
  PORTC = 0b11110000;
  
  while (1){
#ifndef debug
	for ( step = 0; step < steps; step++) {
#endif
	stepRight();
#ifndef debug
	} // for 
#endif
	_delay_ms(1000);
	for ( step = 0; step < steps; step++) {
	  stepLeft();
	} // for 
    _delay_ms( 2000);
	//    L293_OFF;
  }; // while
} // main