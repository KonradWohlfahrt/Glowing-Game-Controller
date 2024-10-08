# Game Controller
Ever wanted to build your own controller/gamepad? Well, with the electronics nowadays is really simple! In this repository you'll find the project files for my diy controller based on the Arduino Leonardo (Arduino Pro Micro). It's a simple first project for soldering (smd components, e.g. the leds, are voluntary) and getting started with the arduino software!
![Controller v1](https://github.com/KonradWohlfahrt/Arduino-Leonardo-Game-Controller/blob/main/images/Controller.jpg)


***
# Preparing the Hardware
You don't have to use the smd components, but the Neopixels make it look so much better! 

**Materials v1:**<br>

| Component | Amount | Silkscreen label |
|:----------|:------:|-----------------:|
| custom pcb | 1 (2 for backplate) | - |
| Arduino Pro Micro | 1 | U3 |
| PS4 joystick + caps | 2 | U1,U2 |
| tactile switch 12x12mm + caps | 8 | B1-B8 |
| tactile switch 6x6mm 90 degree bend | 2 | B9,B10 |
| schottky diode (I've used 1N5817) | 12 | D1-D12 |
| 220R | 1 | R1 |
| 10uF/100uF | 1 | C1 |
| --- SMD --- | --- SMD --- | --- SMD --- |
| WS2812B LEDs (Neopixel) | 11 | LED1-LED11 |
| 100nF 0805 | 11 | C2-C12 |

**Materials v2:**<br>

| Component | Amount | Silkscreen label |
|:----------|:------:|-----------------:|
| custom pcb | 1 (2 for backplate) | - |
| Arduino Pro Micro | 1 | U3 |
| PS4 joystick + caps | 2 | U1,U2 |
| tactile switch 12x12mm + caps | 8 | B1-B8 |
| tactile switch 6x6mm 90 degree bend | 4 | B9-B12 |
| tactile switch 6x6mm | 2 | B13, B14 |
| schottky diode (I've used 1N5817) | 16 | D1-D16 |
| 220R | 1 | R1 |
| 10uF/100uF | 1 | C1 |
| --- SMD --- | --- SMD --- | --- SMD --- |
| WS2812B LEDs (Neopixel) | 13 | LED1-LED13 |
| 100nF 0805 | 13 | C2-C14 |
| tactile smd switch | 1 | SW1 |

**Soldering:**<br>
Solder the components as indicated in the table and images. You should start from the smallest components.
![PCB Front v1](https://github.com/KonradWohlfahrt/Arduino-Leonardo-Game-Controller/blob/main/images/PCB_Front.jpg)
Version 2 features more buttons and a smaller design. The buttons B9 and B11 should be soldered from the bottom.


***
# Programming
In the `src/` folder you'll find the source code. Open `ControllerVx.ino` and install the `Adafruit Neopixel`, `WS2812b FX` and [`Gamepad`](https://github.com/GAMELASTER/ArduinoGamepad) libraries.
Then select the proper board (in my case: `Arduino Leonardo`), its corresponding port and upload the sketch!
You may want to test the joysticks first. Open up the corresponding sketch and take a look at the analog values.
Depending on your readings you should adjust the deadzones accordingly.


***
# The end
With that you've got yourself your own controller!
You can simply add new effects or functionality.
I've already tested it on some game and not every game supports the controller!
Take a look at [this instructable](https://www.instructables.com/Arduino-LeonardoMicroATMega32u4-As-GamepadGame-Con/) to learn more about using the ATmega32U4 as a controller.
Currently, there is no case! If you like to protect the solder joints, add another pcb to the bottom like this:
![PCB Case v1](https://github.com/KonradWohlfahrt/Arduino-Leonardo-Game-Controller/blob/main/images/Controller_Case.jpg)
**When plugging in the controller:**<br>
If you press the outer two buttons (left/right), the controller flashes red and won't transmit any input.
If you press the two up buttons (not triggers), the leds will be disabled.

![Controller on v1](https://github.com/KonradWohlfahrt/Arduino-Leonardo-Game-Controller/blob/main/images/Controller_On.jpg)
![Controller off v1](https://github.com/KonradWohlfahrt/Arduino-Leonardo-Game-Controller/blob/main/images/Controller_Off.jpg)