#include <Arduino.h>
#include "Safe.h"

Safe::Safe(){
}

void Safe::generate_prompt(int combination, int trial){
  Serial.print("User input (answer: ");
  if(combination<10){
    Serial.print("000");
  }
  else if(combination<100){
    Serial.print("00");
  }
  else if(combination<1000){
    Serial.print("0");
  }
  Serial.print(combination);
  Serial.print(")) (Attempt ");
  Serial.print(trial);
  Serial.print("): ");
} 