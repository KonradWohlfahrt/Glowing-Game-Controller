#ifndef SPARKLE_h
#define SPARKLE_h

class Sparkle : public ControllerEffect
{
  public:
    Sparkle() : ControllerEffect(100) { }

    void onStart()
    {
      pixels.setColor(getRandomColor());
      pixels.setMode(55);
      pixels.start();
    }
    void onUpdate(int& i) 
    {
      pixels.service();
    }

    private:
};

#endif