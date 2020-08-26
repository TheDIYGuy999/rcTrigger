# rcTrigger Arduino library

This is an Arduino library for RC vehicles

## Features:
- Allows to trigger multiple actions per analog RC channel
- For example: 3 position rocker switch, 4 push buttons
- two toggle functions per button (depending on push time)
- RC PWM servo signals are usually coming in in Microseconds, this is the base for this library
- momentary() true as long as in range (impulse)
- toggle() toggling true / false (latching), if in range shorter than "duration"
- toggleLong() toggling true / false (latching), if in range longer than "duration"

## New in V 1.0
- Initial commit

## New in V 1.1
- Slight optimizations for ESP32 Sound & Light Controller

## Usage

Code examples
![](https://github.com/TheDIYGuy999/rcTrigger/blob/master/codeExamples.png)

Transmitter analog channel wiring (instead of a potentiometer)
![](https://github.com/TheDIYGuy999/rcTrigger/blob/master/2Buttons.jpg)

![](https://github.com/TheDIYGuy999/rcTrigger/blob/master/3Buttons.jpg)

See [example](https://github.com/TheDIYGuy999/rcTrigger/blob/master/examples/rcTrigger/rcTrigger.ino).

(c) 2020 TheDIYGuy999
