#include <Gamepad.h>

/* EFFECTS */
#include "ControllerEffect.h"
#include "Chaser.h"
#include "Rainbow.h"
#include "RainbowFill.h"
#include "Filler.h"
#include "Randomizer.h"
#include "Scanner.h"
#include "Fader.h"
#include "Fireworks.h"
#include "Running.h"
#include "Sparkle.h"


const int effectsCount = 10;
ControllerEffect * effects[] = { new Fireworks(), new Rainbow(), new Sparkle(), new Running(), new Scanner(), new Fader(), new Randomizer(), new RainbowFill(), new Filler(), new Chaser() };
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
const int joystickMiddleMin[4] = { 412, 412, 412, 412 };
const int joystickMiddleMax[4] = { 612, 612, 612, 612 };

Gamepad controller = Gamepad(); // useZRx; default = false
bool isControllerActive = true;



/* BUTTON MATRIX */
const int rowPins[] = { 4, 7, 14, 16 };
const int rowCount = sizeof(rowPins)/sizeof(rowPins[0]);
const int columnPins[] = { A3, A2, A1, A0 };
const int columnCount = sizeof(columnPins)/sizeof(columnPins[0]);

bool buttonMatrix[rowCount][columnCount];
byte buttonIndexMatrix[rowCount][columnCount] = { { 4, 14, 13, 10}, { 6, 12, 15, 8 }, { 7, 3, 1, 9 }, { 5, 2, 0, 11 } };


void setup() 
{
  pixels.init();
  pixels.setBrightness(LEDBRIGHTNESS);
  pixels.setSpeed(200);

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
  if (!buttonMatrix[0][1] && !buttonMatrix[3][1])
  {
    isControllerActive = false;
    flashAnimation(RED);
    pixels.fill(RED, 0, NUMPIXELS);
    pixels.show();
  }
  // press the two up buttons (no trigger) to deactivate the leds
  else if (!buttonMatrix[1][1] && !buttonMatrix[2][1])
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
        if (value)
          pixels.trigger();
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