#include <Adafruit_NeoPixel.h>
#include <Gamepad.h>

/* NEOPIXEL */
#define RED 0xff0000
#define GREEN 0x00ff00
#define BLUE 0x0000ff

#define PIXELPIN 5
#define NUMPIXELS 11
#define LEDTIME 75
#define LEDBRIGHTNESS 20
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIXELPIN, NEO_GRB + NEO_KHZ800);


/* EFFECTS */
#include "ControllerEffect.h"
#include "Chaser.h"
#include "Rainbow.h"
#include "RainbowFill.h"
#include "Filler.h"
#include "Randomizer.h"

const int effectsCount = 5;
ControllerEffect * effects[] = { new RainbowFill(), new Filler(), new Randomizer(), new Chaser(), new Rainbow() };
ControllerEffect * currentEffect;

bool ledsEnabled = true;
unsigned long lastEffectRefresh;
unsigned long lastEffectUpdate;
int effectIndex;


/* JOYSTICK */
#define JoystickLeftY A7
#define JoystickLeftX A8
#define JoystickRightY A9
#define JoystickRightX A10

const int joystickMin = 5;
const int joystickMax = 1018;
const int joystickMiddleMin[4] = { 500, 500, 485, 550 };
const int joystickMiddleMax[4] = { 560, 560, 535, 600 };

Gamepad controller = Gamepad(); // useZRx; default = false
bool isControllerActive = true;



/* BUTTON MATRIX */
const int rowPins[] = { 7, 4, 16, 14 };
const int rowCount = sizeof(rowPins)/sizeof(rowPins[0]);
const int columnPins[] = { A2, A1, A0 };
const int columnCount = sizeof(columnPins)/sizeof(columnPins[0]);

bool buttonMatrix[rowCount][columnCount];
byte buttonIndexMatrix[rowCount][columnCount] = { { 14, 13, 10}, { 4, 12, 15 }, { 1, 0, 11 }, { 5, 3, 2 } };


void setup() 
{
  pixels.begin();
  pixels.setBrightness(LEDBRIGHTNESS);

  // JOYSTICKS
  pinMode(JoystickLeftY, INPUT);
  pinMode(JoystickLeftX, INPUT);
  pinMode(JoystickRightY, INPUT);
  pinMode(JoystickRightX, INPUT);

  // ROWS
  for (int i = 0; i < rowCount; i++)
    pinMode(rowPins[i], INPUT);
  // COLUMNS
  for (int i = 0; i < columnCount; i++)
    pinMode(columnPins[i], INPUT_PULLUP);

  // press outer two buttons (left & right) to deactivate input transmission
  updateButtonMatrix(false);
  if (!buttonMatrix[0][0] && !buttonMatrix[3][2])
  {
    isControllerActive = false;
    flashAnimation(RED);
    pixels.fill(RED);
    pixels.show();
  }
  // press the two up buttons (no trigger) to deactivate the leds
  else if (!buttonMatrix[1][1] && !buttonMatrix[3][1])
  {
    flashAnimation(RED, 5);
    ledsEnabled = false;
    pixels.clear();
    pixels.show();
  }
  else
    scrollAnimation(GREEN);

  if (ledsEnabled)
  { 
    currentEffect = effects[0];
    currentEffect->onStart();
  }
}
void loop() 
{
  updateJoysticks();
  updateButtonMatrix(isControllerActive);

  if (isControllerActive && ledsEnabled && currentEffect)
  {
    if (millis() - lastEffectRefresh >= currentEffect->getSpeed())
    {
      currentEffect->onUpdate(effectIndex);
      lastEffectRefresh = millis();
    }
    else if (effectsCount > 1 && millis() - lastEffectUpdate >= currentEffect->getDuration())
    {
      int i;
      do {
        i = random(effectsCount);
      } while (effects[i] == currentEffect);
      currentEffect = effects[i];
      currentEffect->onStart();
      lastEffectUpdate = millis();
    }
  }
}

void updateButtonMatrix(bool send)
{
  for (int col = 0; col < columnCount; col++)
  {
    pinMode(columnPins[col], OUTPUT);
		digitalWrite(columnPins[col], LOW);
    for (int row = 0; row < rowCount; row++)
    {
      pinMode(rowPins[row], INPUT_PULLUP);
      bool value = digitalRead(rowPins[row]);

      if (value != buttonMatrix[row][col]) 
      {
        buttonMatrix[row][col] = value;
        if (send)
          controller.setButtonState(buttonIndexMatrix[row][col], !value);
      }

			pinMode(rowPins[row], INPUT);
    }
    pinMode(columnPins[col], INPUT);
  }
}
void updateJoysticks()
{
  if (!isControllerActive)
    return;

  controller.setLeftYaxis(convertAnalogRead(analogRead(JoystickLeftY), 0));
  controller.setLeftXaxis(convertAnalogRead(analogRead(JoystickLeftX), 1));
  
  controller.setRightYaxis(convertAnalogRead(analogRead(JoystickRightY), 2));
  controller.setRightXaxis(convertAnalogRead(analogRead(JoystickRightX), 3));
}

// values from -127 to 127; 0 is center
int8_t convertAnalogRead(int value, int index)
{
  if (value <= joystickMin)
    return 127;
  if (value >= joystickMax)
    return -127;
  if (joystickMiddleMin[index] <= value && value <= joystickMiddleMax[index])
    return 0;

  // range from joystickMin - joystickMiddleMin[index];
  if (value <= joystickMiddleMin[index])
    return -map(value, joystickMin, joystickMiddleMin[index], -127, 0);
  // range from joystickMiddleMax[index] - joystickMax;
  else
    return -map(value, joystickMiddleMax[index], joystickMax, 0, 127);
}