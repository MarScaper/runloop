/*
 * RunLoopHardwareTimer0.hpp
 *
 * Copyright (c) 2017 by Sebastien MARCHAND (Web:www.marscaper.com, Email:sebastien@marscaper.com)
 */
/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef RunLoopHardwareTimer0_hpp
#define RunLoopHardwareTimer0_hpp

// Model
#include "RunLoopObject.hpp"
#include "RunLoopHardwareTimer.hpp"

/*!
 * The class deals with the hardware Timer0 (8bits) of the arduino.
 *
 * "Timer0 is an 8-bit that counts from 0 to 255 and generates an interrupt 
 * it overflows. It uses a clock divisor of 64 by default to give us an 
 * interrupt rate of 976.5625 Hz (close enough to a 1KHz for our purposes).  
 * We won't mess with the freqency of Timer0, because that would break millis()!<br>
 * <br>
 * We'll set up a up a comparison register for Timer 0 (this register is known as 
 * OCR0A) to generate another interrupt somewhere in the middle of that count.  On 
 * every tick, the timer counter is compared with the comparison register and when 
 * they are equal an interrupt will be generated.<br>"
 * Source:"https://learn.adafruit.com/multi-tasking-the-arduino-part-2/timers"
 * <br>
 * There is three ways to use this class:
 * - Create a sublcass, inherit from RunLoopHardwareTimer0 and overwrite fire().
 * - Instantiate a RunLoopHardwareTimer0 object and use a delegate which conforms to RunLoopTimerDelegate protocol.
 * - Use attachInterrupt() to set a simple C function as call back.
 *
 *  @ingroup Model
 */
class RunLoopHardwareTimer0 : public RunLoopHardwareTimer
{
  
public:
  
#pragma mark -
#pragma mark Create and destroy
  
  RunLoopHardwareTimer0();
  ~RunLoopHardwareTimer0();
  
#pragma mark -
#pragma mark Usuals

#if RUN_LOOP_FULL || RUN_LOOP_INHERITANCE
  /*! Method executed each time delay is elapsed if delegate is not set. Subclasses need to overwrite this method. */
  virtual void fire() {};
#endif
  
  /*! Set delay in milliseconds. */
  void setDelay(unsigned long delay);
  
  /*! Set delay in microseconds. */
  void setMicroDelay(unsigned long delay);
  
  /*! Start or stop the loop. */
  void setIdle(bool state);
  
  /*! Global structure used internally by timers to store parameters. */
  TimerPreset timerPresetForMicroDelay(unsigned long delay);
  
  void setTimerPreset(TimerPreset *timer) {};
};

#endif
