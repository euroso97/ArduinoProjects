#ifndef Safe_h 
#define Safe_h 

#include <Arduino.h> 

class Safe { 
    public: 
        Safe();  
        void generate_prompt(int combination, int trial);
    private: 
    int _combination;
}; 

#endif