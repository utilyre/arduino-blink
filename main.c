#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  DDRB |= 1 << DDB5; // set PORTB5 to OUTPUT

  while (1) {
    PORTB |= 1 << PORTB5; // turn PORTB on
    _delay_ms(1000);
    PORTB &= ~(1 << PORTB5); // turn PORTB off
    _delay_ms(1000);
  }
}
