#ifndef RUNNING_h
#define RUNNING_h

class Running : public ControllerEffect
{
  public:
    Running() : ControllerEffect(100) { }

    void onStart()
    {
      pixels.setColor(getRandomColor());
      pixels.setMode(18);
      pixels.start();
    }
    void onUpdate(int& i) 
    {
      pixels.service();
    }

    private:
      long firstPixelHue = 0;
};

#endif