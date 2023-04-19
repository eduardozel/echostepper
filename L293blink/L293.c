#include <avr/io.h>
#include <util/delay.h>

#define fosc 8000000



#define L293_ON   PORTB |= 0b00000001
#define L293_OFF  PORTB &= 0b11111110

#define DRV1_c   PORTC &= 0b11111100
#define DRV1_r   PORTC |= 0b00000001
#define DRV1_l   PORTC |= 0b00000010


#define DRV2_c   PORTC &= 0b11110011
#define DRV2_r   PORTC |= 0b00000100
#define DRV2_l   PORTC |= 0b00001000



void RightOff(void)
{
    L293_OFF;
	DRV1_c;
	L293_ON;
} // RightOff

void RightYellow(void)
{
    L293_OFF;
	DRV1_c;
	DRV1_r;
	L293_ON;
} // RightRed

void RightRed(void)
{
    L293_OFF;
	DRV1_c;
	DRV1_l;
	L293_ON;
} // RightRed


// -----------------

void LeftOff(void)
{
    L293_OFF;
	DRV2_c;
	L293_ON;
} // LeftOff

void LeftYellow(void)
{
    L293_OFF;
	DRV2_c;
	DRV2_r;
	L293_ON;
} // LeftYellow

void LeftRed(void)
{
    L293_OFF;
	DRV2_c;
	DRV2_l;
	L293_ON;
} // LeftRed

// =================

int main(void)
{
  DDRB |= 1 << PINB0;
  PORTB = 0b11111110;

  DDRC  = ( 1 << DD0 ) | ( 1 << DD1 ) | ( 1 << DD2 )  | ( 1 << DD3 ) ;
  PORTC = 0b11110000;
  
  while (1){
    LeftRed();
    _delay_ms(1000);
    LeftOff();
    _delay_ms(500);
    LeftYellow();
    _delay_ms(500);
    LeftOff();
    _delay_ms(500);
    LeftYellow();
    _delay_ms(500);
    LeftOff();
    _delay_ms(1000);
    RightRed();
    _delay_ms(1000);
    RightRed();
    _delay_ms(1000);
    RightRed();
    _delay_ms(1000);
    RightYellow();
    _delay_ms(1000);
    RightOff();
    _delay_ms(1000);
  }; // while
} // main