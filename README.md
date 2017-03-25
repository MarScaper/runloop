# RunLoop
![Alt text](/RunLoop.jpg?raw=true "Optional Title")

Arduino parallelization library.


## Synopsis

A 100% C ++ library for parallelization with an Arduino...
![Alt text](/RunLoopClassHierarchy.jpg?raw=true "Optional Title")


## Features
- RunLoop objects with hierarchy, idle state, etc.
- Software timers.
- Hardware timers: Timer0, Timer1, Timer2, Timer3, Timer4, Timer5 (3,4,5 only availables with Arduino Mega).
- Software and hardware timers fully interchangeable.
- Hardware interrupts (pins supported according to your arduino board).
- Full C++ approach with inheritance or delegation paradigm for asynchronous callbacks with timers and interrupts.
- C compatiility with enhanced C function callbacks.

## Limitations

- PWM not implemented yet with hardware timers.

## Code Example

See sample code directory: https://github.com/MarScaper/runloop/tree/master/examples

Software timer with callback:
```
../..
RunLoopTimer *timer = new RunLoopTimer();
timer->attachInterrupt(fire);
timer->setDelay(1000);
this->addToRunLoop(timer);
../..
```

Timer0 (Hardware Timer) with delegate:
```
../..
RunLoopTimer *timer = new RunLoopHardwareTimer0();
timer->setTimerDelegate(this);
timer->setDelay(1000);
this->addToRunLoop(timer);
../..
```

Pin 2 Interrupt with delegate:
```
../..
RunLoopInterrupt *interruptPin2 = new RunLoopInterruptPin2(INPUT_PULLUP,RISING);
interruptPin2->setInterruptDelegate(this);
this->addToRunLoop(interruptPin2);
../..
```

## Motivation

This library is part of a personnal project to improve my EM10 Takahashi mount thanks to Arduino.

Click on this video to see buzzer, led, IR remote and lcd working together with the library...
[![Alt text for your video](https://img.youtube.com/vi/p8aKuSLS8uE/0.jpg)](https://www.youtube.com/watch?v=p8aKuSLS8uE)

## License

Copyright (c) 2017 by Sebastien MARCHAND 
Web:www.marscaper.com - Email:sebastien@marscaper.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
