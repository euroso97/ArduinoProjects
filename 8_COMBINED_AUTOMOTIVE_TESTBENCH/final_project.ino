#include <LiquidCrystal.h>
#include <DHT.h>
#include <IRremote.hpp>
#include <MFRC522.h>


#define DHTTYPE DHT11   // DHT 11
#define DHTPIN 37
#define IR_RECEIVE_PIN  46  // IR Remote pin
#define WLSENSORPIN A5

#define RST_PIN         1
#define SS_PIN          53

/*IR Remote Commands*/
#define IR_BDOWN 7
#define IR_BUP 9
#define IR_BUTTON_1 12
#define IR_BUTTON_2 24
#define IR_BUTTON_3 94
#define IR_BUTTON_7 66
#define IR_BUTTON_8 82
#define IR_BUTTON_9 74
#define LED_1 26
#define LED_2 27


// UltraSonic Sensor pins & variables declaration
const int trigPin = 6;
const int echoPin = 7;
long duration;
float distance;

// Montor Control pins & variables declaration
const int forward=9;
const int backward=8;
int outval=0;
char temp;
String instr="Input Value: ";
String outstr=", Output Value: ";
String spdcool="";
String tempscreen="";

int detect=1;
int warning=0;

int motor_speed_control=0;

int led1=0;
int led2=0;


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// initialize temperature sensor
DHT dht(DHTPIN, DHTTYPE);

// Create MFRC522 instance
MFRC522 mfrc522(SS_PIN, RST_PIN);  
unsigned long uid;
unsigned long hex_num=0;

void setup(){
  pinMode(38, OUTPUT); // water level sensor
  digitalWrite(38,HIGH); // water level sensor

  pinMode(23,OUTPUT); // green led
  pinMode(24,OUTPUT); // yellow led
  pinMode(25,OUTPUT); // red led  
  pinMode(trigPin, OUTPUT); // Ultrasonic trigger pin
  pinMode(echoPin, INPUT); // Ultrasonic echo pin
  pinMode(forward,OUTPUT); // Motor forward pin
  pinMode(backward,OUTPUT); // Motor backward pin

  Serial.begin(9600);
  dht.begin();
  IrReceiver.begin(IR_RECEIVE_PIN); // Start the receiver

  while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	delay(400);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop(){
  if(mfrc522.PICC_IsNewCardPresent()){
    uid = getID();
    // delay(200);
    if(uid != 0){
      Serial.print("Card detected, UID: "); Serial.println(uid);
      if(uid==4294959115){
        Serial.println("ALERT Unauthorized User!!");
        for(int i=0; i<3; i++){
          tone(10,2000);
          delay(100);
          noTone(10);
          delay(100);
        }
        outval=0;
        analogWrite(backward,0);
        analogWrite(forward,0);
      }
      else if(uid==15621){
        Serial.println("WELCOME Authorized User");
        tone(10,1000);
        delay(200);
        noTone(10);
      }     
    }
  }

  spdcool="";
  tempscreen="";
  float f = dht.readTemperature(true); // read in F

  analogWrite(backward,0);
  analogWrite(forward,outval-(11*motor_speed_control));
  /*##########################
  #### Ultrasonic Reading ####
  ##########################*/
  digitalWrite(trigPin, LOW);
  delay(100);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2.0;
  
  /* Motor Speed Control */
  if(distance>=13){
    detect=0;
    outval=255;
  }
  else if(distance<13 && distance>1){
    detect=1;
    outval=map(distance,3,13,70,255);
  }
  else{
    detect=1;
    outval=0;
  }
  
  /*###################
  #### LED Control ####
  ###################*/
  //Green LED
  if(distance<33){ //if not already on
    digitalWrite(23, HIGH); // turn on
  }
  else{ //otherwise
    digitalWrite(23, LOW);
  }
  //Yellow LED
  if(distance<23){
    digitalWrite(24,HIGH);
  }
  else{
    digitalWrite(24,LOW);
  }
  //Red LED
  if(distance<13){
    digitalWrite(25,HIGH);
  }
  else{
    digitalWrite(25,LOW);
  }

  /*##################################
  #### Water Level Sensor Control ####
  ##################################*/
  int sensorValue = analogRead(WLSENSORPIN);
  // Serial.print("\tWater level: ");
  // Serial.println(sensorValue);
  if(sensorValue<100){
    warning=1;
  }
  else{
    warning=0;
  }

  /*###################
  #### LCD Control ####
  ###################*/
  tempscreen.concat("Temp:");
  tempscreen.concat(f);
  tempscreen.concat("*F");
  spdcool.concat("Spd:");
  spdcool.concat(map(outval,70,255,0,100));
  

  spdcool.concat("  Cool:");
  if(warning==0){
    spdcool.concat("Y");
  }
  if(warning==1){
    spdcool.concat("N");
  }

  lcd.begin(16,2);
  lcd.print(tempscreen);
  lcd.setCursor(0, 1);
  lcd.print(spdcool);

  if (IrReceiver.decode()) {
    //Serial.println(IrReceiver.decodedIRData.command); // Print "old" raw data
    switch(IrReceiver.decodedIRData.command){
      case IR_BDOWN:
        if(outval-(motor_speed_control*11)>11 && detect==0){
          motor_speed_control += 1;
        }

        break;
      case IR_BUP:
        if(outval-(motor_speed_control*11)<244 && detect==0){
          motor_speed_control -=1;
        }

        break;
      case IR_BUTTON_1:
        led1=0;
        break;

      case IR_BUTTON_2:
        led1=150;
        break;

      case IR_BUTTON_3:
        led1=255;
        break;

      case IR_BUTTON_7:
        led2=0;
        break;

      case IR_BUTTON_8:
        led2=150;
        break;

      case IR_BUTTON_9:
        led2=255;
        break;
      default:
        break;

    }
    IrReceiver.resume(); // Enable receiving of the next value
  }

  analogWrite(LED_1,led1);
  analogWrite(LED_2,led2);

  Serial.print(distance);
  Serial.print(",");
  Serial.print(map(outval-(motor_speed_control*11),70,255,0,100)); // speed
  Serial.print(",");
  Serial.print(f); // temp
  Serial.print(",");
  Serial.print(warning); // coolant warning
  Serial.print(",");
  Serial.print(led1);
  Serial.print(",");
  Serial.println(led2);


}

unsigned long getID(){
  if (!mfrc522.PICC_ReadCardSerial()) {
    delay(50);
    return 0;
  }
  hex_num =  mfrc522.uid.uidByte[0] << 24;
  hex_num += mfrc522.uid.uidByte[1] << 16;
  hex_num += mfrc522.uid.uidByte[2] <<  8;
  hex_num += mfrc522.uid.uidByte[3];
  mfrc522.PICC_HaltA(); // Stop reading
  return hex_num;
}