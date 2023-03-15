#ifndef Analog_pin_h 
#define Analog_pin_h 
#include <Arduino.h> 

class AnalogPin { 
    public: 
        AnalogPin(); 
        void init();
        void adc_init(void);
        uint16_t read_adc(uint8_t channel);
    private: 
}; 

#endif