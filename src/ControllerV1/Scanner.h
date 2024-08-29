#ifndef SCANNER_h
#define SCANNER_h

class Scanner : public ControllerEffect
{
  public:
    Scanner() : ControllerEffect(100) { }

    void onStart()
    {
      pixels.setColor(getRandomColor());
      pixels.setMode(43);
      pixels.start();
    }
    void onUpdate(int& i) 
    {
      pixels.service();
    }

    private:
};

#endif