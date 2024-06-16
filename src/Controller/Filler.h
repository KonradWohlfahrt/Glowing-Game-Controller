#ifndef FILLER_h
#define FILLER_h

class Filler : public ControllerEffect
{
  public:
    Filler() : ControllerEffect(100) { }

    void onStart()
    {
      _c = getRandomColor();
    }
    void onUpdate(int& i) 
    {
      if (i >= NUMPIXELS * 2)
      {
        _c = getRandomColor();
        i = 0;
      }
      
      if (i >= NUMPIXELS)
        pixels.setPixelColor(NUMPIXELS - (i - NUMPIXELS), 0);
      else
        pixels.setPixelColor(i, getSimilarColor(_c));
      pixels.show();
      i++;
    }

    private:
      uint32_t _c; 
};

#endif