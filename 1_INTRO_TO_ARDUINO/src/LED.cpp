#include <Arduino.h>
#include "LED.h"

LED::LED(int pin){
  pinMode(pin,OUTPUT);
  _pin = pin;
}

void LED::on(){
  digitalWrite(_pin,HIGH);
  delay(250);
}

void LED::off(){
  digitalWrite(_pin,LOW);
  delay(250);
}

void LED::blink(int x, int t_on, int t_off){
  for(int i=0; i<x; i++){
    digitalWrite(_pin,HIGH);
    delay(t_on);
    digitalWrite(_pin,LOW);
    delay(t_off);
  }
}