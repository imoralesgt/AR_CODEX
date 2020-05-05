#ifndef ARGPIO_H
#define ARGPIO_H

#include "Arduino.h"

//Hardware GPIO abstraction layer
class argpio{
    public:
        
        argpio();
        ~argpio();

        void initIOs(void);

        void pSetup(uint8_t pin, uint8_t mode);
        void dWrite(uint8_t pin, int value);
        int dRead(uint8_t pin);

    private:

};


#endif