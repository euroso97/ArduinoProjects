#ifndef LED_h 
#define LED_h 

#include <Arduino.h> 

class LED { 
    public: 
        LED(int pin); 
        void on(); 
        void off();
        void blink(int x, int t_on, int t_off);
    private: 
    int _pin;
}; 

#endif