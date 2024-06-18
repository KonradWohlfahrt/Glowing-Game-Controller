/* JOYSTICK */
#define JoystickLeftY A7
#define JoystickLeftX A8
#define JoystickRightY A9
#define JoystickRightX A10

/* CHANGE THESE VALUES ACCORDING TO YOUR MEASUREMENTS */
const int joystickMin = 5;
const int joystickMax = 1018;
// my analog readings: 528, 532, 502, 579
const int joystickMiddleMin[4] = { 500, 500, 485, 550 };
const int joystickMiddleMax[4] = { 560, 560, 535, 600 };


void setup() 
{
  Serial.begin(9600);

  // JOYSTICKS
  pinMode(JoystickLeftY, INPUT);
  pinMode(JoystickLeftX, INPUT);
  pinMode(JoystickRightY, INPUT);
  pinMode(JoystickRightX, INPUT);
}
void loop() 
{
  ///* pure analog values
  Serial.print(analogRead(JoystickLeftY));
  Serial.print("\t");
  Serial.print(analogRead(JoystickLeftX));
  Serial.print("\t");
  Serial.print(analogRead(JoystickRightY));
  Serial.print("\t");
  Serial.println(analogRead(JoystickRightX));
  //*/

  /* the converted range from -127 to 127
  Serial.print(convertAnalogRead(analogRead(JoystickLeftY), 0));
  Serial.print("\t");
  Serial.print(convertAnalogRead(analogRead(JoystickLeftX), 1));
  Serial.print("\t");
  Serial.print(convertAnalogRead(analogRead(JoystickRightY), 2));
  Serial.print("\t");
  Serial.println(convertAnalogRead(analogRead(JoystickRightX), 3));
  */
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