#ifndef PID_H
#define PID_H

#include "globals.h"

class Pid{

    /*
    ===============================
    Class-specific global variables
    ===============================
    */

    float kP; float kI; float kD;
    float minInt; float maxInt;
    float integrator; float diff; //IRM Diff stands for differentiation
    float error;
    float setPoint;



    public:

        //IRM Constructor and destructor
        Pid(float p, float i, float d, float minI, float maxI);
        ~Pid();



        /*
        ===========================================
        IRM Class-specific public method prototypes
        ===========================================
        */
        void  pidInit(float p, float i, float d, float minI, float maxI);
        void  pidSetPoint(float sp);
        float pidUpdate(float currentValue);

    private:

        //IRM encapsulated method prototypes
        void __resetIDvalues();
        void __accumulateIntegration(float e);


        //IRM private setters
        void __setErrorValue(float e);
        void __setIntegratorValue(float i);
        void __setDiffValue(float d);
        

        //IRM private getters
        float __getErrorvalue();
        float __getKp();
        float __getKi();
        float __getKd();
        float __getMinInt();
        float __getMaxInt();

        float __getIntegratorValue();
        float __getDiffValue();

};

#endif
