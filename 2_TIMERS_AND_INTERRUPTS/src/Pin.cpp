#include <Arduino.h>
#include "Pin.h"

DigitalPin::DigitalPin(int timer){
  pinMode(timer,OUTPUT);
  _timer = timer;
}
void DigitalPin::initialize(){
  if(_timer==1){
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 = 0;
    TCNT1 = 0;
    OCR1A = 15624;
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS12) | (0 << CS11) | (1 << CS10);
    TIMSK1 |= (1 << OCIE1A);
  }
  else if(_timer==3){ 
    TCCR3A = 0;
    TCCR3B = 0;
    TIMSK3 = 0;
    TCNT3 = 0;
    OCR3A = 15624;
    TCCR3B |= (1<<WGM32);
    TCCR3B |= (1<<CS32) |(0<<CS31) |(1<<CS30);
    TIMSK3 |= (1<<OCIE3A);
  }
  else if(_timer==4){ 
    TCCR4A = 0;
    TCCR4B = 0;
    TIMSK4 = 0;
    TCNT4 = 0;
    OCR4A = 15624;
    TCCR4B |= (1<<WGM42);
    TCCR4B |= (1<<CS42) |(0<<CS41) |(1<<CS40);
    TIMSK4 |= (1<<OCIE4A);
  }
  else if(_timer==5){
    TCCR5A = 0;
    TCCR5B = 0;
    TIMSK5 = 0;
    TCNT5 = 0;
    OCR5A = 15624;
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