#ifndef RAINBOWFILL_h
#define RAINBOWFILL_h

class RainbowFill : public ControllerEffect
{
  public:
    RainbowFill() : ControllerEffect() { }

    void onStart()
    {
      
    }
    void onUpdate(int& i) 
    {
      pixels.fill(pixels.ColorHSV(hue), 0, NUMPIXELS);
      pixels.show();
      hue += 256;
    }

    private:
      int hue = 0;
};

#endif