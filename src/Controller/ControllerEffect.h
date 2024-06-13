#ifndef CONTROLLEREFFECT_h
#define CONTROLLEREFFECT_h

class ControllerEffect 
{
    public:
        ControllerEffect() {}
        virtual void onStart() = 0;
        virtual void onUpdate(int& i) = 0;

    private:
        
};

#endif