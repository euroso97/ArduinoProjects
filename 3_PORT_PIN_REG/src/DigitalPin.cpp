#include <Arduino.h>
#include "DigitalPin.h"

//use 16 bits timer 1,3,4,5
DigitalPin::DigitalPin(int timer){
  _timer = timer;
}

//initialize timer to 1Hz
void DigitalPin::initialize(){
  if(_timer==1){
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 = 0;
    TCNT1 = 0;
    OCR1A = 15624; // (16*10^6) / (1*1024) - 1 (must be <65536)
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS12) | (0 << CS11) | (1 << CS10);
    TIMSK1 |= (1 << OCIE1A);
  }
  else if(_timer==3){ 
    TCCR3A = 0;
    TCCR3B = 0;
    TIMSK3 = 0;
    TCNT3 = 0;
    OCR3A = 15624; // (16*10^6) / (1*1024) - 1 (must be <65536)
    TCCR3B |= (1<<WGM32);
    TCCR3B |= (1<<CS32) |(0<<CS31) |(1<<CS30);
    TIMSK3 |= (1<<OCIE3A);
  }
  else if(_timer==4){ 
    TCCR4A = 0;
    TCCR4B = 0;
    TIMSK4 = 0;
    TCNT4 = 0;
    OCR4A = 15624; // (16*10^6) / (1*1024) - 1 (must be <65536)
    TCCR4B |= (1<<WGM42);
    TCCR4B |= (1<<CS42) |(0<<CS41) |(1<<CS40);
    TIMSK4 |= (1<<OCIE4A);
  }
  else if(_timer==5){
    TCCR5A = 0;
    TCCR5B = 0;
    TIMSK5 = 0;
    TCNT5 = 0;
    OCR5A = 15624; // (16*10^6) / (1*1024) - 1 (must be <65536)
    TCCR5B |= (1 << WGM52);
    TCCR5B |= (1 << CS52) | (0 << CS51) | (1 << CS50);
    TIMSK5 |= (1 << OCIE5A);
  }
}

void DigitalPin::set_TCCRA(int wgm1, int wgm0){
  if(_timer==1){
    TCCR1A |= ((wgm1 << WGM11) | (wgm0 << WGM10));
  }
  else if(_timer==3){ 
    TCCR3A |= ((wgm1 << WGM31) | (wgm0 << WGM30));
  }
  else if(_timer==4){ 
    TCCR4A |= ((wgm1 << WGM41) | (wgm0 << WGM40));
  }
  else if(_timer==5){
    TCCR5A |= ((wgm1 << WGM51) | (wgm0 << WGM50));
  }
}
void DigitalPin::set_TCCRB(int icnc1, int ices1, int wgm3, int wgm2, int cs2, int cs1, int cs0){
  if(_timer==1){
    TCCR1B |= ((icnc1 << ICNC1) | (ices1 << ICES1));
    TCCR1B |= ((wgm3 << WGM13) | (wgm2 << WGM12));
    TCCR1B |= ((cs2 << CS12) | (cs1 << CS11) | (cs0 << CS10));
  }
  else if(_timer==3){
    TCCR3B |= ((icnc1 << ICNC3) | (ices1 << ICES3));
    TCCR3B |= ((wgm3 << WGM33) | (wgm2 << WGM32));
    TCCR3B |= ((cs2 << CS32) | (cs1 << CS31) | (cs0 << CS30));
  }
  else if(_timer==4){
    TCCR4B |= ((icnc1 << ICNC4) | (ices1 << ICES4));
    TCCR4B |= ((wgm3 << WGM43) | (wgm2 << WGM42));
    TCCR4B |= ((cs2 << CS42) | (cs1 << CS41) | (cs0 << CS40));
  }
  else if(_timer==5){
    TCCR5B |= ((icnc1 << ICNC5) | (ices1 << ICES5));
    TCCR5B |= ((wgm3 << WGM53) | (wgm2 << WGM52));
    TCCR5B |= ((cs2 << CS52) | (cs1 << CS51) | (cs0 << CS50));
  }
}
void DigitalPin::set_TCNT(int val){
  if(_timer==1){
    TCNT1=val;
  }
  else if(_timer==3){
    TCNT3=val;
  }
  else if(_timer==4){
    TCNT4=val;
  }
  else if(_timer==5){
    TCNT5=val;
  }
}
void DigitalPin::set_OCR(int ocr){
  //set to 1hz by default
  if(_timer==1){
    OCR1A=ocr;
  }
  else if(_timer==3){
    OCR3A=ocr;
  }
  else if(_timer==4){
    OCR4A=ocr;
  }
  else if(_timer==5){
    OCR5A=ocr;
  }
}
void DigitalPin::factor_OCR(int hz){
  if(_timer==1){
    OCR1A=(int)15625/hz - 1;
  }
  else if(_timer==3){
    OCR3A=(int)15625/hz - 1;
  }
  else if(_timer==4){
    OCR4A=(int)15625/hz - 1;
  }
  else if(_timer==5){
    OCR5A=(int)15625/hz - 1;
  }
}
void DigitalPin::set_TIMSK(int icie, int ocie_c, int ocie_b, int ocie_a, int toie){
  if(_timer==1){
    TIMSK1 |= (icie << ICIE1);
    TIMSK1 |= ((ocie_c << OCIE1C) | (ocie_b << OCIE1B) | (ocie_a << OCIE1A));
    TIMSK1 |= (toie << TOIE1);
  }
  else if(_timer==3){
    TIMSK3 |= (icie << ICIE3);
    TIMSK3 |= ((ocie_c << OCIE3C) | (ocie_b << OCIE3B) | (ocie_a << OCIE3A));
    TIMSK3 |= (toie << TOIE3);
  }
  else if(_timer==4){
    TIMSK4 |= (icie << ICIE4);
    TIMSK4 |= ((ocie_c << OCIE4C) | (ocie_b << OCIE4B) | (ocie_a << OCIE4A));
    TIMSK4 |= (toie << TOIE4);
  }
  else if(_timer==5){
    TIMSK5 |= (icie << ICIE5);
    TIMSK5 |= ((ocie_c << OCIE5C) | (ocie_b << OCIE5B) | (ocie_a << OCIE5A));
    TIMSK5 |= (toie << TOIE5);
  }
}


// digital pin number, port registry representation(in binary representation), and the complement of the port registry implementation
// pin 0 to 13
void DigitalPin::set_pin(int pin){
  switch(pin){
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

void DigitalPin::set_output_mode(int pin){
  switch(pin){
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

void DigitalPin::set_input_mode(int pin){
  switch(pin){
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
void DigitalPin::on(int pin){
  switch(pin){
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
void DigitalPin::off(int pin){
  switch(pin){
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
void DigitalPin::invert_pin(int pin){
  switch(pin){
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