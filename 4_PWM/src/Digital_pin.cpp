#include <Arduino.h>
#include "Digital_pin.h" 
//use 16 bits timer 1,3,4,5
DigitalPin::DigitalPin(int pin){
  pinMode(pin,OUTPUT);
  _pin=pin;
}

void DigitalPin::set_TCCRA(uint8_t tccra){
  switch(_pin){
    case 13:
      TCCR0A = tccra;
    case 4:
      TCCR0A = tccra;
    case 11:
      TCCR1A = tccra;
    case 12:
      TCCR1A = tccra;
    case 10:
      TCCR2A = tccra;
    case 9:
      TCCR2A = tccra;
    case 5:
      TCCR3A = tccra;
    case 2:
      TCCR3A = tccra;
    case 3:
      TCCR3A = tccra;
    case 6:
      TCCR4A = tccra;
    case 7:
      TCCR4A = tccra;
    case 8:
      TCCR4A = tccra;
    case 44:
      TCCR5A = tccra;
    case 45:
      TCCR5A = tccra;
    case 46:
      TCCR5A = tccra;
  }
}
void DigitalPin::set_TCCRB(uint8_t tccrb){
  switch(_pin){
    case 13:
      TCCR0B = tccrb;
    case 4:
      TCCR0B = tccrb;
    case 11:
      TCCR1B = tccrb;
    case 12:
      TCCR1B = tccrb;
    case 10:
      TCCR2B = tccrb;
    case 9:
      TCCR2B = tccrb;
    case 5:
      TCCR3B = tccrb;
    case 2:
      TCCR3B = tccrb;
    case 3:
      TCCR3B = tccrb;
    case 6:
      TCCR4B = tccrb;
    case 7:
      TCCR4B = tccrb;
    case 8:
      TCCR4B = tccrb;
    case 44:
      TCCR5B = tccrb;
    case 45:
      TCCR5B = tccrb;
    case 46:
      TCCR5B = tccrb;
  }
}
void DigitalPin::set_TCNT(int tcnt){
  switch(_pin){
    case 13:
      TCNT0 = tcnt;
    case 4:
      TCNT0 = tcnt;
    case 11:
      TCNT1 = tcnt;
    case 12:
      TCNT1 = tcnt;
    case 10:
      TCNT2 = tcnt;
    case 9:
      TCNT2 = tcnt;
    case 5:
      TCNT3 = tcnt;
    case 2:
      TCNT3 = tcnt;
    case 3:
      TCNT3 = tcnt;
    case 6:
      TCNT4 = tcnt;
    case 7:
      TCNT4 = tcnt;
    case 8:
      TCNT4 = tcnt;
    case 44:
      TCNT5 = tcnt;
    case 45:
      TCNT5 = tcnt;
    case 46:
      TCNT5 = tcnt;
  }
}
void DigitalPin::set_OCR(int ocr){
  switch(_pin){
    case 13:
      OCR0A = ocr;
    case 4:
      OCR0B = ocr;
    case 11:
      OCR1A = ocr;
    case 12:
      OCR1B = ocr;
    case 10:
      OCR2A = ocr;
    case 9:
      OCR2B = ocr;
    case 5:
      OCR3A = ocr;
    case 2:
      OCR3B = ocr;
    case 3:
      OCR3C = ocr;
    case 6:
      OCR4A = ocr;
    case 7:
      OCR4B = ocr;
    case 8:
      OCR4C = ocr;
    case 44:
      OCR5A = ocr;
    case 45:
      OCR5B = ocr;
    case 46:
      OCR5C = ocr;
  }
}
void DigitalPin::factor_OCR(int factor){
  switch(_pin){
    case 13:
      OCR0A += factor;
    case 4:
      OCR0B += factor;
    case 11:
      OCR1A += factor;
    case 12:
      OCR1B += factor;
    case 10:
      OCR2A += factor;
    case 9:
      OCR2B += factor;
    case 5:
      OCR3A += factor;
    case 2:
      OCR3B += factor;
    case 3:
      OCR3C += factor;
    case 6:
      OCR4A += factor;
    case 7:
      OCR4B += factor;
    case 8:
      OCR4C += factor;
    case 44:
      OCR5A += factor;
    case 45:
      OCR5B += factor;
    case 46:
      OCR5C += factor;
  }
}
void DigitalPin::set_TIMSK(uint8_t timsk){
  switch(_pin){
    case 13:
      TIMSK0 = timsk;
    case 4:
      TIMSK0 = timsk;
    case 11:
      TIMSK1 = timsk;
    case 12:
      TIMSK1 = timsk;
    case 10:
      TIMSK2 = timsk;
    case 9:
      TIMSK2 = timsk;
    case 5:
      TIMSK3 = timsk;
    case 2:
      TIMSK3 = timsk;
    case 3:
      TIMSK3 = timsk;
    case 6:
      TIMSK4 = timsk;
    case 7:
      TIMSK4 = timsk;
    case 8:
      TIMSK4 = timsk;
    case 44:
      TIMSK5 = timsk;
    case 45:
      TIMSK5 = timsk;
    case 46:
      TIMSK5 = timsk;
  }
}

// digital pin number, port registry representation(in binary representation), and the complement of the port registry implementation
// pin 0 to 13
void DigitalPin::set_pin(){
  switch(_pin){
    case 0:
      DDRE = B00000000;
      PORTE = B00000000; // 0
    case 1:
      DDRE = B00000000;
      PORTE = B00000000; // 1
    case 2:
      DDRE = B00000000;
      PORTE = B00000000; // 4
    case 3:
      DDRE = B00000000;
      PORTE = B00000000; // 5
    case 4:
      DDRG = B00000000;
      PORTG = B00000000; // 5
    case 5:
      DDRE = B00000000;
      PORTE = B00000000; // 3
    case 6:
      DDRH = B00000000;
      PORTH = B00000000; // 3
    case 7:
      DDRH = B00000000;
      PORTH = B00000000; // 4
    case 8:
      DDRH = B00000000;
      PORTH = B00000000; // 5
    case 9:
      DDRH = B00000000;
      PORTH = B00000000; // 5
    case 10:
      DDRB = B00000000;
      PORTB = B00000000; // 4
    case 11:
      DDRB = B00000000;
      PORTB = B00000000; // 5
    case 12:
      DDRB = B00000000;
      PORTB = B00000000; // 6
    case 13:
      DDRB = B00000000;
      PORTB = B00000000; // 7
    case 44:
      DDRL = B00000000;
      PORTL = B00000000; // 5
  }
}

void DigitalPin::set_output_mode(){
  switch(_pin){
    case 0:
      DDRE |= B00000001; // 0
    case 1:
      DDRE |= B00000010; // 1
    case 2:
      DDRE |= B00010000; // 4
    case 3:
      DDRE |= B00100000; // 5
    case 4:
      DDRG |= B00100000; // 5
    case 5:
      DDRE |= B00001000; // 3
    case 6:
      DDRH |= B00001000; // 3
    case 7:
      DDRH |= B00010000; // 4
    case 8:
      DDRH |= B00100000; // 5
    case 9:
      DDRH |= B01000000; // 6
    case 10:
      DDRB |= B00010000; // 4
    case 11:
      DDRB |= B00100000; // 5
    case 12:
      DDRB |= B01000000; // 6
    case 13:
      DDRB |= B10000000; // 7
    case 44:
      DDRL |= B00100000; // 5
  }
}

void DigitalPin::set_input_mode(){
  switch(_pin){
    case 0:
      DDRE &= B11111110; // 0
    case 1:
      DDRE &= B11111101; // 1
    case 2:
      DDRE &= B11101111; // 4
    case 3:
      DDRE &= B11011111; // 5
    case 4:
      DDRG &= B11011111; // 5
    case 5:
      DDRE &= B11110111; // 3
    case 6:
      DDRH &= B11110111; // 3
    case 7:
      DDRH &= B11101111; // 4
    case 8:
      DDRH &= B11011111; // 5
    case 9:
      DDRH &= B10111111; // 6
    case 10:
      DDRB &= B11101111; // 4
    case 11:
      DDRB &= B11011111; // 5
    case 12:
      DDRB &= B10111111; // 6
    case 13:
      DDRB &= B01111111; // 7
    case 44:
      DDRL &= B11011111; // 5
  }
}

// set to HIGH
void DigitalPin::on(){
  switch(_pin){
    case 0:
      PORTE |= B00000001; // 0
    case 1:
      PORTE |= B00000010; // 1
    case 2:
      PORTE |= B00010000; // 4
    case 3:
      PORTE |= B00100000; // 5
    case 4:
      PORTG |= B00100000; // 5
    case 5:
      PORTE |= B00001000; // 3
    case 6:
      PORTH |= B00001000; // 3
    case 7:
      PORTH |= B00010000; // 4
    case 8:
      PORTH |= B00100000; // 5
    case 9:
      PORTH |= B01000000; // 6
    case 10:
      PORTB |= B00010000; // 4
    case 11:
      PORTB |= B00100000; // 5
    case 12:
      PORTB |= B01000000; // 6
    case 13:
      PORTB |= B10000000; // 7
    case 44:
      PORTL |= B00100000; // 5
  }
}
// set to LOW
void DigitalPin::off(){
  switch(_pin){
    case 0:
      PORTE &= B11111110; // 0
    case 1:
      PORTE &= B11111101; // 1
    case 2:
      PORTE &= B11101111; // 4
    case 3:
      PORTE &= B11011111; // 5
    case 4:
      PORTG &= B11011111; // 5
    case 5:
      PORTE &= B11110111; // 3
    case 6:
      PORTH &= B11110111; // 3
    case 7:
      PORTH &= B11101111; // 4
    case 8:
      PORTH &= B11011111; // 5
    case 9:
      PORTH &= B10111111; // 5
    case 10:
      PORTB &= B11101111; // 4
    case 11:
      PORTB &= B11011111; // 5
    case 12:
      PORTB &= B10111111; // 6
    case 13:
      PORTB &= B01111111; // 7
    case 44:
      PORTL &= B11011111; // 5
  }
}
// set to invert
// digitalWrite(pin,!digitalRead(pin));
void DigitalPin::invert_pin(){
  switch(_pin){
    case 0:
      PORTE = ~PORTE; // 0
    case 1:
      PORTE = ~PORTE; // 1
    case 2:
      PORTE = ~PORTE; // 4
    case 3:
      PORTE = ~PORTE; // 5
    case 4:
      PORTG = ~PORTG; // 5
    case 5:
      PORTE = ~PORTE; // 3
    case 6:
      PORTH = ~PORTH; // 3
    case 7:
      PORTH = ~PORTH; // 4
    case 8:
      PORTH = ~PORTH; // 5
    case 9:
      PORTH = ~PORTH; // 6
    case 10:
      PORTB = ~PORTB; // 4
    case 11:
      PORTB = ~PORTB; // 5
    case 12:
      PORTB = ~PORTB; // 6
    case 13:
      PORTB = ~PORTB; // 7
    case 44:
      PORTL = ~PORTL; // 5
  }
}

// This sets the ICR value in the register for the respective pin.
void DigitalPin::set_ICR(int icr){
  switch(_pin){
    case 11:
      ICR1 = icr;
    case 12:
      ICR1 = icr;
    case 5:
      ICR3 = icr;
    case 2:
      ICR3 = icr;
    case 3:
      ICR3 = icr;
    case 6:
      ICR4 = icr;
    case 7:
      ICR4 = icr;
    case 8:
      ICR4 = icr;
    case 44:
      ICR5 = icr;
    case 45:
      ICR5 = icr;
    case 46:
      ICR5 = icr;
  }
}
// This sets the duty cycle for the pin of interest.
// duty cycle = OCRA/ICR, set by modifying ICR
void DigitalPin::set_duty_cycle(float cycle){
  switch(_pin){
    case 11:
      ICR1 = (int)OCR1A/cycle;
    case 12:
      ICR1 = (int)OCR1B/cycle;
    case 5:
      ICR3 = (int)OCR3A/cycle;
    case 2:
      ICR3 = (int)OCR3B/cycle;
    case 3:
      ICR3 = (int)OCR3C/cycle;
    case 6:
      ICR4 = (int)OCR4A/cycle;
    case 7:
      ICR4 = (int)OCR4B/cycle;
    case 8:
      ICR4 = (int)OCR4C/cycle;
    case 44:
      ICR5 = (int)OCR5A/cycle;
    case 45:
      ICR5 = (int)OCR5B/cycle;
    case 46:
      ICR5 = (int)OCR5C/cycle;
  }
}