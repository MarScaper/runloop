/*
 * RunLoopInterruptPin1.hpp
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
#ifndef RunLoopInterruptPin1_hpp
#define RunLoopInterruptPin1_hpp

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "Arduino.h"
#endif

// Model
#include "RunLoopInterrupt.hpp"

/*!
 * The class manages interrupts on pin 1 of the Arduino.
 *
 *  @ingroup Model
 */
class RunLoopInterruptPin1 : public RunLoopInterrupt
{
  
public:
  
#pragma mark -
#pragma mark Create and destroy
  
  /*!
   Input Mode: INPUT, INPUT_PULLUP.
   Interrupt Mode: LOW, CHANGE, RISING,FALLING, HIGH (Arduino Due, Zero, MKR1000 only).
   */
  RunLoopInterruptPin1(uint8_t inputMode,int interruptMode);
  ~RunLoopInterruptPin1();
  
#pragma mark -
#pragma mark Virtual methods for subclass overwrite
  
  /*! Method executed each time delay is elapsed. User should overwrite this method when subclassing RunLoopTimer. */
  virtual void interrupt() {};
};

#endif
