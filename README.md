# FitnessInputConverterArduino
This is the Arduino Leonardo Code accompanying [Flappy Cycling](https://github.com/amplejoe/FlappyCycling) and [Quake 3 Fitness Edition](https://github.com/amplejoe/Q3AErgo), which have been part of a master thesis study conducted at the [Alpen-Adria University](https://www.aau.at/) (AAU), Klagenfurt. The sketch converts Ergometer, Pulse Handle and Pulse Sensor input to Keybard presses and features two modes, one for each game.

This work is licensed under the [Creative Commons Attribution-NonCommercial 4.0 International License](http://creativecommons.org/licenses/by-nc/4.0/).

## Requirements
* A suitable ergometer -- for developing [Ultrasport F-Bike 150/200B](http://tinyurl.com/jlqnbna) was used.
* Pulse Sensor from [pulsesensor.com](http://pulsesensor.com/).
* An Arduino device -- the files are configured for [Arduino Leonardo](https://www.arduino.cc/en/Main/ArduinoBoardLeonardo), but can be reconfigured (see below).
* A breadboard to build the circuit on.
* Cables, plugs and soldering tools to connect the ergometer to the breadboard -- for [Ultrasport F-Bike 150/200B](http://tinyurl.com/jlqnbna) a female TS and TSR jack were attached to the two male output jacks. Optionally the rather short cable of the pulse sensor can be extended.

## How To
1. Set up following circuit and plug in ergometer as well as pulse sensor:
![alt tag](https://raw.githubusercontent.com/amplejoe/FitnessInputConverterArduino/master/img/RPM_HANDLES_BPM_sensor.png)
2. Plug in a contact breaker cable from digital PIN 4 to GND, in order to enable manual interruption of the keyboard functionality (key presses can be disturbing when games are not running). 
3. Change interruptSetup() in ([Interrupt.ino](https://github.com/amplejoe/FitnessInputConverterArduino/blob/master/InputConverter/Interrupt.ino)) to work with your Arduino -- setup instructions can be found in ([Timer_Interrupt_Notes.ino](https://github.com/amplejoe/FitnessInputConverterArduino/blob/master/InputConverter/Timer_Interrupt_Notes.ino)).
4. Configure the sketch to work with [Flappy Cycling](https://github.com/amplejoe/FlappyCycling) or [Quake 3 Fitness Edition](https://github.com/amplejoe/Q3AErgo) by changing the cfg variable in [InputConverter.ino](https://github.com/amplejoe/FitnessInputConverterArduino/blob/master/InputConverter/InputConverter.ino).
5. Compile and Upload code to Arduino

## Flappy Cycling Mode
// - presses 'x' key on every ergometer pedal cycle or 'z'/'c' keys on pulse handle touch
// Quake 3 Arena Mode:
// - presses 'x' key on every ergometer pedal cycle or 'h' key on puls sensor heart beat

