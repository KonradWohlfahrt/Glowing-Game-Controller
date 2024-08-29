#ifndef CONTROLLEREFFECT_h
#define CONTROLLEREFFECT_h

#include <WS2812FX.h>

/* NEOPIXEL */

#define PIXELPIN 5
#define NUMPIXELS 11
#define LEDTIME 75
#define LEDBRIGHTNESS 20
WS2812FX pixels = WS2812FX(NUMPIXELS, PIXELPIN, NEO_GRB + NEO_KHZ800);


void scrollAnimation(uint32_t color)
{
  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, color);
    pixels.show();
    delay(LEDTIME);
  }
  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, 0, 0, 0);
    pixels.show();
    delay(LEDTIME);
  }
}
void flashAnimation(uint32_t color)
{
  for (int i = 0; i < 10; i++)
  {
    if (i % 2 == 0)
      pixels.fill(color, 0, NUMPIXELS);
    else
      pixels.clear();
    
    pixels.show();
    delay(LEDTIME);
  }
}
void flashAnimation(uint32_t color, int n)
{
  for (int i = 0; i < 10; i++)
  {
    if (i % 2 == 0)
      pixels.setPixelColor(n, color);
    else
      pixels.setPixelColor(n, 0);
    
    pixels.show();
    delay(LEDTIME);
  }
}

byte shiftByte(byte c)
{
  byte shift = c / 2;
  if (c > 127)
    shift = (-(int)c + 255) / 2;

  if (c < 25)
    return c + shift;
  else if (c > 230)
    return c - shift;
  else
    return c + (random(2) == 0 ? shift : -shift);
}
uint32_t getRandomColor() { return pixels.ColorHSV(random(65536)); }
uint32_t getSimilarColor(uint32_t color) { return pixels.gamma32(pixels.Color(shiftByte((byte)(color >> 16)), shiftByte((byte)(color >> 8)), shiftByte((byte)color))); }


class ControllerEffect 
{
    public:
        ControllerEffect(int effectSpeed = 25, unsigned long effectDuration = 30000) : _effectSpeed(effectSpeed), _effectDuration(effectDuration) {}
        virtual void onStart() = 0;
        virtual void onUpdate(int& i) = 0;
        int getSpeed() { return _effectSpeed; }
        unsigned long getDuration () { return _effectDuration; }

    private:
        int _effectSpeed;
        unsigned long _effectDuration;
};

#endif