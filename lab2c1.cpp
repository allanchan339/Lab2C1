#include "lab2c1.h"
#include <avr/io.h>

void counting(){
    OCR0A = 1;
    TCCR0A = 0x02; // CTC mode
    TCCR0B = 0b00000110; //count as falling edge
    while (!(TIFR0 & ( 1 << OCF0A))); // wait until OCF0A O.F.
    TCCR0A = 0; //reset everyting
    TCCR0B = 0;
    TIFR0 = 0x02; //set OCF0A to 1 ro reset
}
void delay_1ms(){
    OCR0A = 0xFA; //250
    TCCR0A = 0x02; //
    TCCR0B = 0b00000011;
    while (!(TIFR0 & ( 1 << OCF0A))); // wait until OCF0A O.F.
    TCCR0A = 0; //reset everyting
    TCCR0B = 0;
    TIFR0 = 0x02;
}
void delay(int time){
    int maxS = time / 1E-3;
    for (int i = 0; i < maxS; ++i) {
        delay_1ms();
    }
}
int main(void)
{
    PORTD = 0;
    DDRC = 0xFF;
    int state = 0;
    while (1)
    {
        for (int i = 0; i < 3; ++i) {
            counting();
            delay(250E-3);
        }
        if(state == 0){
            state = 1;
            PORTC = 0xFF;
        }
        else if(state == 1){
            state = 0;
            PORTC = 0 ; //set PORTC = 0
        }
    }
}