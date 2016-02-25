# FitnessInputConverterArduino
This is the Arduino Leonardo Code accompanying [Flappy Cycling](https://github.com/amplejoe/FlappyCycling) and [Quake 3 Fitness Edition](https://github.com/amplejoe/Q3AErgo). It converts Ergometer, Pulse Handle and Pulse Sensor input to Keybard presses and features two modes, one for each game.

## Requirements
* A suitable ergometer -- for developing [Ultrasport F-Bike 150/200B](http://tinyurl.com/jlqnbna) was used.
* Pulse Sensor from [pulsesensor.com](http://pulsesensor.com/).
* An Arduino device -- the files are configured for [Arduino Leonardo](https://www.arduino.cc/en/Main/ArduinoBoardLeonardo), but can be reconfigured (see below).
* A breadboard to build the circuit on.
* Cables and soldering tools to connect the ergometer to the breadboard -- for [Ultrasport F-Bike 150/200B](http://tinyurl.com/jlqnbna) a female TS and TSR jack were attached to the two male output jacks. Optionally the rather short cable of the pulse sensor can be extended.

## How to
1. Set up following circuit and plug in 
2. Connect a suitable a suitable ergometer .
3. 
2. Change interruptSetup() in ([Interrupt.ino](https://github.com/amplejoe/FitnessInputConverterArduino/blob/master/InputConverter/Interrupt.ino)) to work with your Arduino -- setup instructions can be found in ([Timer_Interrupt_Notes.ino](https://github.com/amplejoe/FitnessInputConverterArduino/blob/master/InputConverter/Timer_Interrupt_Notes.ino)).

## Flappy Cycling Mode
// - presses 'x' key on every ergometer pedal cycle or 'z'/'c' keys on pulse handle touch
// Quake 3 Arena Mode:
// - presses 'x' key on every ergometer pedal cycle or 'h' key on puls sensor heart beat



This work is licensed under the [Creative Commons Attribution-NonCommercial 4.0 International License](http://creativecommons.org/licenses/by-nc/4.0/).
