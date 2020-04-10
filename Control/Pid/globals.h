#ifndef GLOBALS_H
#define GLOBALS_H

//IRM Arduino workaround for GCC compilation in x86
#ifndef ARDUINO_H
    #define byte char 
#else
    #include "Arduino.h"    
#endif


#endif