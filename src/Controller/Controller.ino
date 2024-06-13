#include <Adafruit_NeoPixel.h>
#include <Gamepad.h>

#define RED 0xff0000
#define GREEN 0x00ff00
#define BLUE 0x0000ff

#define PIXELPIN 5
#define NUMPIXELS 11
#define LEDTIME 75
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIXELPIN, NEO_GRB + NEO_KHZ800);

#include "ControllerEffect.h"
#include "Rainbow.h"

ControllerEffect * effects[] = { new Rainbow() };
ControllerEffect * currentEffect = new Rainbow();
const int effectSize = 1;

unsigned long lastEffectUpdate;
int effectIndex;


#define JoystickLeftY A7
#define JoystickLeftX A8
#define JoystickRightY A9
#define JoystickRightX A10
Gamepad controller = Gamepad(); // useZRx; default = false
bool isControllerActive = true;


const int joystickMin = 5;
const int joystickMax = 1018;
const int joystickMiddleMin[4] = { 510, 510, 490, 560 };
const int joystickMiddleMax[4] = { 540, 540, 520, 585 };


// BUTTON MATRIX
const int rowPins[] = { 7, 4, 16, 14 };
const int rowCount = sizeof(rowPins)/sizeof(rowPins[0]);
const int columnPins[] = { A2, A1, A0 };
const int columnCount = sizeof(columnPins)/sizeof(columnPins[0]);

bool buttonMatrix[rowCount][columnCount];
byte buttonIndexMatrix[rowCount][columnCount] = { { 14, 13, 10}, { 4, 12, 15 }, { 1, 0, 11 }, { 5, 3, 2 } };


void setup() 
{
  pixels.begin();
  pixels.setBrightness(20);

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

  updateButtonMatrix(false);

  if (!buttonMatrix[0][0] && !buttonMatrix[3][2])
  {
    isControllerActive = false;
    flashAnimation(RED);
    pixels.fill(RED);
    pixels.show();
    while (true);
  }
  else
  {
    scrollAnimation(GREEN);
  }

  pixels.fill(0x9000ff);
  pixels.show();
}
void loop() 
{
  updateJoysticks();
  updateButtonMatrix(isControllerActive);

  if (millis() - lastEffectUpdate >= LEDTIME)
  {
    if (currentEffect)
      currentEffect->onUpdate(effectIndex);

    lastEffectUpdate = millis();
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
  
  /*
  for (int col = 0; col < 4; col++)
  {
    digitalWrite(columnPins[col], HIGH);
    for (int row = 0; row < 3; row++)
    {
      bool value = digitalRead(rowPins[row]);
      if (value != buttonMatrix[row][col]) 
      {
        buttonMatrix[row][col] = value;
        if (isControllerActive)
          controller.setButtonState(buttonIndexMatrix[row, col], value);
      }
    }
    digitalWrite(columnPins[col], LOW);
  }
  */
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

  // joystickMin - joystickMiddleMin[index];
  if (value <= joystickMiddleMin[index])
    return -map(value, joystickMin, joystickMiddleMin[index], -127, 0);
  // joystickMiddleMax[index] - joystickMax;
  else
    return -map(value, joystickMiddleMax[index], joystickMax, 0, 127);
}

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
      pixels.fill(color);
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