#ifndef Pin_h 
#define Pin_h 
#include <Arduino.h> 

class DigitalPin { 
    public: 
        DigitalPin(int pin); 
        void initialize();
        void set_TCCRA(int wgm1, int wgm0); 
        void set_TCCRB(int icnc1, int ices1, int wgm3, int wgm2, int cs2, int cs1, int cs0); 
        void set_TCNT(int val); 
        void set_OCR(int ocr); 
        void factor_OCR(int hz); 
        void set_TIMSK(int icie, int ocie_c, int ocie_b, int ocie_a, int toie); 
    private: 
    int _timer;
    int _factor;
}; 

#endif