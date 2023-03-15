#ifndef Digital_pin_h 
#define Digital_pin_h 
#include <Arduino.h> 

class DigitalPin { 
    public: 
        DigitalPin(int pin); 
        void set_TCCRA(uint8_t tccra); 
        void set_TCCRB(uint8_t tccrb); 
        void set_TCNT(int tcnt); 
        void set_OCR(int ocr); 
        void factor_OCR(int factor); 
        void set_TIMSK(uint8_t timsk); 
        void set_pin();
        void set_output_mode();
        void set_input_mode();
        void on();
        void off();
        void invert_pin();
        void set_ICR(int icr);
        void set_duty_cycle(float cycle);
    private: 
    int _pin;
}; 

#endif