/*
 * RunLoopHardwareTimer5.hpp
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
#ifndef RunLoopHardwareTimer5_hpp
#define RunLoopHardwareTimer5_hpp

// Timer only available with Arduino Mega
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)

// Model
#include "RunLoopObject.hpp"
#include "RunLoopHardwareTimer.hpp"

/*!
 * The class manages the hardware Timer5 (16bits) available with the <b>Arduino Mega only</b>.
 * Hardware timers are much more accurate so we can use micro seconds delay.
 *
 * There is three ways to use this class:
 * - Create a sublcass, inherit from RunLoopHardwareTimer0 and overwrite fire().
 * - Instantiate a RunLoopHardwareTimer0 object and use a delegate which conforms to RunLoopTimerDelegate protocol.
 * - Use attachInterrupt() to set a simple C function as call back.
 *
 *  @ingroup Model
 */
class RunLoopHardwareTimer5 : public RunLoopHardwareTimer
{
  
public:
  
#pragma mark -
#pragma mark Create and destroy
  
  RunLoopHardwareTimer5();
  ~RunLoopHardwareTimer5();
  
#pragma mark -
#pragma mark Usuals
  
  /*! Method executed each time delay is elapsed if delegate is not set. Subclasses need to overwrite this method. */
  virtual void fire() {};
  
  /*! Set delay in milliseconds. */
  void setDelay(unsigned long delay);
  
  /*! Set delay in microseconds. */
  void setMicroDelay(unsigned long delay);
  
  /*! Start or stop the loop. */
  void setIdle(bool state);
};
#endif

#endif