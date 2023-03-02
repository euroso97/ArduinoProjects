#include <Arduino.h>
#include <Pin.h>
#include <Safe.h>

// variables
int trial;
int combination = random(10000); //random number between 0000-9999
String inputcode;
int i_combination;
int first,second,third,fourth;
int i_first,i_second,i_third,i_fourth;

//classes
DigitalPin timer3(3); //timer 3
DigitalPin timer1(1); //timer 1
DigitalPin timer4(4); //timer 4
DigitalPin timer5(5); //timer 5
Safe safe;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));

  noInterrupts();

  timer3.initialize();
  timer1.initialize();
  timer4.initialize();
  timer5.initialize();
  interrupts();

  trial=4;
}

void loop() {
  if (trial>3){  
    digitalWrite(5,HIGH);
    digitalWrite(11,HIGH);
    digitalWrite(6,HIGH);
    digitalWrite(44,HIGH);
    delay(3000);

    combination = random(10000);
    first = combination/1000;
    second = (combination%1000)/100;
    third = (combination%100)/10;
    fourth = combination % 10;

    timer3.initialize();
    timer1.initialize();
    timer4.initialize();
    timer5.initialize();

    trial=1;
  }
  timer3.factor_OCR(trial);
  timer1.factor_OCR(trial);
  timer4.factor_OCR(trial);
  timer5.factor_OCR(trial);

  // prompt
  safe.generate_prompt(combination, trial); 
  while (Serial.available() == 0){}
  inputcode = Serial.readString();
  inputcode.trim();
  i_combination = inputcode.toInt();
  i_first = i_combination/1000;
  i_second = (i_combination%1000)/100;
  i_third = (i_combination%100)/10;
  i_fourth = i_combination % 10;

  //disable timers if each digit is correct
  if(i_first==first){
    TCCR3B=0;
    TIMSK3=0;
    digitalWrite(5,LOW);
  }
  if(i_second==second){
    TCCR1B=0;
    TIMSK1=0;
    digitalWrite(11,LOW);
  }
  if(i_third==third){
    TCCR4B=0;
    TIMSK4=0;
    digitalWrite(6,LOW);
  }
  if(i_fourth==fourth){
    TCCR5B=0;
    TIMSK5=0;
    digitalWrite(44,LOW);
  }
  if(i_first==first && i_second==second && i_third==third && i_fourth==fourth){
    Serial.println(" Correct Answer");
    trial=4;
  }
  else{
    Serial.println(" Incorrect");
    trial++;
  }
}

// timer interrupts 
ISR(TIMER3_COMPA_vect){
  digitalWrite(5,!digitalRead(5)); // Flips output value
}
ISR(TIMER1_COMPA_vect){
  digitalWrite(11,!digitalRead(11)); // Flips output value
}
ISR(TIMER4_COMPA_vect){
  digitalWrite(6,!digitalRead(6)); // Flips output value
}
ISR(TIMER5_COMPA_vect){
  digitalWrite(44,!digitalRead(44)); // Flips output value
}