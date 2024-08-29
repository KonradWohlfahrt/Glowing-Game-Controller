#ifndef FADER_h
#define FADER_h

class Fader : public ControllerEffect
{
  public:
    Fader() : ControllerEffect() { }

    void onStart()
    {
      pixels.setColor(getRandomColor());
      pixels.setMode(15);
      pixels.start();
    }
    void onUpdate(int& i) 
    {
      pixels.service();
    }

    private:
};

#endif