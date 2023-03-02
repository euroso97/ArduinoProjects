#include <Arduino.h>
#include <DigitalPin.h>
#include <Safe.h>

// variables
int trial;
int combination = random(10000); //random number between 0-9999
String inputcode;
int i_combination;
int first,second,third,fourth; // for combination digits
int i_first,i_second,i_third,i_fourth; // for user inputs

//classes
DigitalPin timer3(3); //timer 3
DigitalPin timer1(1); //timer 1
DigitalPin timer4(4); //timer 4
DigitalPin timer5(5); //timer 5
Safe safe;
 
void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));

  timer3.set_output_mode(5);
  timer1.set_output_mode(11);
  timer4.set_output_mode(6);
  timer5.set_output_mode(44);

  noInterrupts();
  // declare Pin class for each timers
  timer3.initialize();
  timer1.initialize();
  timer4.initialize();
  timer5.initialize();
  interrupts();
  trial=4;
}

void loop() {
  if (trial>3){  
    timer3.initialize();
    timer1.initialize();
    timer4.initialize();
    timer5.initialize();
    timer3.set_pin(5); // red
    timer1.set_pin(11); // yellow
    timer4.set_pin(6); // green
    timer5.set_pin(44); // blue

    timer3.on(5); // red
    timer1.on(11); // yellow
    timer4.on(6); // green
    timer5.on(44); // blue
    delay(5000);

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
  // serial input by user
  while (Serial.available() == 0){}
  inputcode = Serial.readString();  //read Serial input until timeout
  inputcode.trim();
  i_combination = inputcode.toInt();
  i_first = i_combination/1000;
  i_second = (i_combination%1000)/100;
  i_third = (i_combination%100)/10;
  i_fourth = i_combination % 10;

  Serial.print(inputcode);

  //disable timers if each digit is correct
  if(i_first==first){
    TCCR3B=0;
    TIMSK3=0;
    timer3.off(5); // red
  }
  if(i_second==second){
    TCCR1B=0;
    TIMSK1=0;
    timer1.off(11); // yellow
  }
  if(i_third==third){
    TCCR4B=0;
    TIMSK4=0;
    timer4.off(6); // green
  }
  if(i_fourth==fourth){
    TCCR5B=0;
    TIMSK5=0;
    timer5.off(44); // blue
  }
  //reset all if all input digits are correct
  if(i_first==first && i_second==second && i_third==third && i_fourth==fourth){ // if correct
    Serial.println(" -> Correct!!");
    trial=4;
  }
  else{ // if incorrect
    Serial.println(" -> Incorrect");
    trial++; // increment trial
  }
}

// for timer interrupts 
ISR(TIMER3_COMPA_vect){
  PORTE = ~PORTE;
}
ISR(TIMER1_COMPA_vect){
  PORTB = ~PORTB;
}
ISR(TIMER4_COMPA_vect){
  PORTH = ~PORTH;
}
ISR(TIMER5_COMPA_vect){
  PORTL = ~PORTL;
}