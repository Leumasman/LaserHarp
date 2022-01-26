# LaserHarp
A midi sound controler built on an Arduino Uno with a laser split by a rotating mirror as the midi controller stimulus. 

There are three main components in this system; a MIDI controller for the sound, stepper motor for fanning out the laser into multiple discrete sources and the laser controller to turn it on and off in between movements. 

## MIDI Controller

The MIDI controller uses the default serial port in the Arduino examples to push midi controller commands back up to the PC through a MIDI to USB cable.

## Stepper Motor and Stepper Motor Driver

The stepper motor driver is an off the shelf adafruit model. The code was developed of sample code from the adafruit website as a referenece. 

## Laser and Laser Controller

The laser and controller utilize a genric green laser pointer that was hacked a bit in order to add a MOSFET control to turn the laser on and off in syncronization with the movement of the stepper motor. 