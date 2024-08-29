#ifndef CHASER_h
#define CHASER_h

class Chaser : public ControllerEffect
{
  public:
    Chaser() : ControllerEffect(75) { }

    void onStart()
    {
      _c = getRandomColor();
    }
    void onUpdate(int& i) 
    {
      if (i >= NUMPIXELS)
      {
        _c = getRandomColor();
        i = 0;
      }
      
      pixels.setPixelColor(i, _c);
      pixels.show();

      i++;
    }

    private:
      uint32_t _c; 
};

#endif