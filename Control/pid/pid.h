//#ifndef
#define Pid_H

class Pid{

    public:

        //IRM Constructor and destructor
        Pid(float p, float i, float d, float minI, float maxI);
        ~Pid();

        //IRM Class-specific methods
        pidInit();

}

//#endif    