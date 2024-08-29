#ifndef RANDOMIZER_h
#define RANDOMIZER_h

class Randomizer : public ControllerEffect
{
  public:
    Randomizer() : ControllerEffect(250) { }

    void onStart()
    {
      pixels.setColor(getRandomColor());
      pixels.setMode(10);
      pixels.start();
    }
    void onUpdate(int& i) 
    {
      pixels.service();
    }

    private:
};

#endif