#ifndef RAINBOW_h
#define RAINBOW_h

class Rainbow : public ControllerEffect
{
  public:
    Rainbow() : ControllerEffect() { }

    void onStart()
    {
      
    }
    void onUpdate(int& i) 
    {
      if (firstPixelHue >= 5*65536)
        firstPixelHue = 0;
      pixels.rainbow(firstPixelHue);
      pixels.show();
      firstPixelHue += 256;
    }

    private:
      long firstPixelHue = 0;
};

#endif