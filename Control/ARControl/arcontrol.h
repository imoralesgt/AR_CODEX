#ifndef ARCONTROL_H
#define ARCONTROL_H


class arcontrol{

    public:

        /*
        ======================
        Global class variables
        ======================
        */

       /*
        Sensor and set-point values must be given
        in base SI units. e.g. [Volume] = m³,
        [Pressure] = Pa, [Air Flow] = m³/s.

        Special variables must be strictly commented,
        such as [Respirations per minutes] = 1/(minutes)
       */

        //IRM Sensor-related variables
        float pressure = 0.0;
        float airFlow  = 0.0;
        float volume   = 0.0;

        //IRM GUI-related input set-point variables
        float spPressure = 0.0; //Pressure set-point
        float spVolMin   = 0.0; //Minimum volume set-point
        float spVolMax   = 0.0; //Maximum volume set-point
        float spRPM      = 0.0; //Respirations-per-minute set-point
        float spIEratio  = 0.0; //I:E ratio set-point

        //IRM initialization (set-point) parameters received from GUI FLAG
        unsigned int initParametersReceived;



        /*
        ====================
        Global class methods
        ====================
        */

        //AR_CODEX Main control class module
        arcontrol();
        
        ~arcontrol();


        //IRM Public methods

        //IRM Gets init parameters from GUI I2C Controller, which are set as working set-points. Returns 0 if everything ok
        int setInitParameters(float pressure, float minVol, float maxVol, float rpm, float ieRatio);

    private:


        /*
        ====================
        Encapsulated methods
        ====================
        */

        //Compute respiratory period (in seconds) form respiratory rate (in minutes)
        float __computeRespirationPeriod(float rpm);

        //Compute inspiration duration (in seconds), based on RPM and I:E Ratio 
        float __computeIDuration(float rpm, float ieRatio);

        //Compute expiration duration (in seconds), based on RPM and I:E Ratio 
        float __computeEDuration(float rpm, float ieRatio);

        //Compute Inspiration rate (slope). Dependent variable: Volume, Independent var: time (inspiration time) 
        //A positive value is expected
        float __computeISlope(float rpm, float ieRatio, float minVol, float maxVol);
        
        //Compute Expiration rate (slope). Dependent variable: Volume, Independent var: time (expiration time) 
        //Expected negative slope
        float __computeESlope(float rpm, float ieRatio, float minVol, float maxVol);




        /*
        ================================
        Encapsulated Setters and getters
        ================================
        */

        //Set max working pressure value, to protect patient's lungs
        void __setSpPressure(float press);

        //Set min opetariontal volume set-point, to avoid negative pressure
        void __setSpMinVol(float minVol);

        //Set max opetariontal volume set-point, to protect patient's lungs
        void __setSpMaxVol(float maxVol);

        //Set respirations per minute set-point (respiration period)
        void __setSpRPM(float rpm);

        //Set Inspiration:Espiration ratio (respiration duty cycle)
        void __setSpIeRatio(float ie);

        //Set or reset Init Parameters Already Received Flag
        void __setInitParametersFlag();
        void __resetInitParametersFlag();



        //Get Init parameters flag
        int __getInitParametersFlag();

        //Get max working pressure value, to protect patient's lungs
        float __getSpPressure();

        //Get min opetariontal volume set-point, to avoid negative pressure
        float __getSpMinVol();

        //Get max opetariontal volume set-point, to protect patient's lungs
        float __getSpMaxVol();

        //Get respirations per minute set-point (respiration period)
        float __getSpRPM();

        //Get Inspiration:Espiration ratio (respiration duty cycle)
        float __getSpIeRatio();

};


#endif