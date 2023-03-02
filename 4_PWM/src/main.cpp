#include <Arduino.h>
#include <Digital_pin.h>
#include <Analog_pin.h> 

int photo_vin;
int led_vin;
int record;
AnalogPin apin;

void setup() {
  pinMode(6,OUTPUT);
  //timer for LED flash
  pinMode(5,OUTPUT);
  noInterrupts();
  TCCR3A=0;
  TCCR3B=0;
  TCNT3=0;
  TCCR3A=0b10000010;
  TCCR3B=0b00010011;  
  OCR3A=5000;
  ICR3=5000;
  
  // timer for measuring
  TCCR4A=0;
  TCCR4B=0;
  TCNT4=0;
  TCCR4A=0b10000010;
  TCCR4B=0b00010011;  
  TIMSK4 |= (1<<OCIE4A);
  OCR4A=5000;
  ICR4=5000;

  interrupts();
  apin.adc_init();
  Serial.begin(9600);
}

void loop() {
  for(int i=5; i<=100;i+=5){
    ICR3 = (int)5000.0/i*100.0; // change duty cycle
    delay(2000); // wait time before measuring
    record = 1; 
    Serial.print("Duty Cycle (%):  ");
    Serial.println(i);
    delay(1000); //measurment period
    record = 0;
  }
}

ISR(TIMER4_COMPA_vect){
  if(record==1){
    photo_vin = apin.read_adc(0);
    Serial.println((int)photo_vin*5.0/1023.0);
  }
}