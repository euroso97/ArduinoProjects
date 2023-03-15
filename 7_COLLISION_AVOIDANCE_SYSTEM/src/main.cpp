#include <Arduino.h>

const int trigPin = 11;
const int echoPin = 12;
long duration;
float distance;

const int forward=7;
const int backward=5;
int outval=0;
char temp;
String instr="Input Value: ";
String outstr=", Output Value: ";
String rotation="";

void setup(){
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(forward,OUTPUT);
    pinMode(backward,OUTPUT);
    Serial.begin(9600);
}

void loop(){
  if(outval>0){
    analogWrite(backward,0);
    analogWrite(forward,outval);
  }
  if(outval==0){
    analogWrite(backward,0);
    analogWrite(forward,0);
  }
  if(outval<0){
    analogWrite(forward,0);
    analogWrite(backward,-outval);
  }
  
  digitalWrite(trigPin, LOW);
  delay(100);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2.0;
  Serial.print("Distance: ");
  Serial.println(distance);
  if(distance>=30){
    outval=255;
  }
  else if(distance<30 && distance>10){
    outval=(distance-10)*105/20+150;
  }
  else{
    outval=0;
  }

  //Green LED
  if(distance<30){ //if not already on
    digitalWrite(8, HIGH); // turn on
  }
  else{ //otherwise
    digitalWrite(8, LOW);
  }
  //Yellow LED
  if(distance<20){
    digitalWrite(9,HIGH);
  }
  else{
    digitalWrite(9,LOW);
  }
  //Red LED
  if(distance<10){
    digitalWrite(10,HIGH);
  }
  else{
    digitalWrite(10,LOW);
  }
}