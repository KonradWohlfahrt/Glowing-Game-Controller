#ifndef RANDOMIZER_h
#define RANDOMIZER_h

class Randomizer : public ControllerEffect
{
  public:
    Randomizer() : ControllerEffect(200) { }

    void onStart()
    {
      pixels.fill(getRandomColor());
      pixels.show();
    }
    void onUpdate(int& i) 
    {
      pixels.setPixelColor(random(NUMPIXELS), getRandomColor());
      pixels.show();
    }

    private:
};

#endif