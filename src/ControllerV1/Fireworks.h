#ifndef FIREWORKS_h
#define FIREWORKS_h

class Fireworks : public ControllerEffect
{
  public:
    Fireworks() : ControllerEffect(150) { }

    void onStart()
    {
      pixels.setColor(getRandomColor());
      pixels.setMode(46);
      pixels.start();
    }
    void onUpdate(int& i) 
    {
      pixels.service();
    }

    private:
};

#endif