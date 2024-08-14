#include <avr/io.h>
#include <util/delay.h>

// Define CPU frequency for delay
#define F_CPU 16000000UL
// Define baud rate
#define BAUD 9600
// Calculate UBRR value
#define MY_UBRR F_CPU/16/BAUD-1

void USART_Init(unsigned int ubrr) {
  // Set baud rate
  UBRR0H = (unsigned char)(ubrr >> 8);
  UBRR0L = (unsigned char)ubrr;

  // Enable receiver and transmitter
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);

  // Set frame format: 8data, 2stop bit
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void USART_Transmit(unsigned char data) {
  // Wait for empty transmit buffer
  while (!(UCSR0A & (1 << UDRE0)));

  // Put data into buffer, sends the data
  UDR0 = data;
}

void USART_PrintString(const char* str) {
  while (*str) {
    USART_Transmit(*str++);
  }
}

int main(void) {
  // Initialize USART
  USART_Init(MY_UBRR);

  // Main loop
  while (1) {
    // Send a string to the terminal
    USART_PrintString("Hello, Embedded C!\r\n");

    // Wait for a second
    _delay_ms(1000);
  }
}
