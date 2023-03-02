#include <Arduino.h>
#include "LED.h"

// Create Variables
const unsigned int MAX_LENGTH = 50;
static int pin_int;
static int x;
static int y;
static int z;

char pin_color[6];
char pin_mode[6];
char pin_x[3];
char pin_y[3];
char pin_z[3];

char *token;

const char s[2] = ","; // seperator

void setup() {
 Serial.begin(9600);
}

void loop() {
  while (Serial.available() > 0){
    static char message[MAX_LENGTH];
    static unsigned int message_pos = 0;
    char inByte = Serial.read();
    if ( inByte != '\n' && (message_pos < MAX_LENGTH - 1) ){
      message[message_pos] = inByte;
      message_pos++;
    }
    // If message received
    else{
      x=0;
      y=0;
      z=0;

      //Add null character to string
      message[message_pos] = '\0';
      
      // pin color setup
      token = strtok(message,s);
      strcpy(pin_color,token);

      if(strcmp(pin_color,"red")==0){
        pin_int = 8;
      }
      else if(strcmp(pin_color,"yellow")==0){
        pin_int = 7;
      }
      else if(strcmp(pin_color,"green")==0){
        pin_int = 6;
      }
      else if(strcmp(pin_color,"blue")==0){
        pin_int = 5;
      }
      else{
        Serial.println("Invalid pin!!"); // invalid input
      }

      token = strtok(NULL, s);
      strcpy(pin_mode, token);

      if(strcmp(pin_mode,"on")==0){
        LED led(pin_int);
        led.on();
      }
      else if(strcmp(pin_mode,"off")==0){
        LED led(pin_int);
        led.off();
      }
      else if(strcmp(pin_mode,"blink")==0){
        token = strtok(NULL, s);
        x = atoi(token);
        token = strtok(NULL, s);
        y = atoi(token);
        token = strtok(NULL, s);
        z = atoi(token);
        LED led(pin_int);
        led.blink(x,y,z);
      }
      //Reset
      message_pos = 0;
      }
    }
  }