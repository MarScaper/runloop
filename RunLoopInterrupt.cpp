/*
 * RunLoopInterrupt.cpp
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

#include "arduino.h"

#include "RunLoopInterrupt.hpp"

// Small hack to avoid naming conflict between class method end C function for attachInterrupt(...).
void _attachInterrupt(uint8_t interruptNum, void (*userFunc)(void), int mode)
{
  attachInterrupt(interruptNum, userFunc, mode);
}

// Small hack to avoid naming conflict between class method end C function for detachInterrupt(...).
void _detachInterrupt(uint8_t interruptNum)
{
  detachInterrupt(interruptNum);
}

#pragma mark -
#pragma mark Memory management

RunLoopInterrupt::RunLoopInterrupt()
{
}

RunLoopInterrupt::~RunLoopInterrupt()
{
}

#pragma mark -
#pragma mark Interrupt management

void RunLoopInterrupt::setInterruptDelegate(RunLoopInterruptDelegate *delegate)
{
  _interruptDelegate = delegate;
}

void RunLoopInterrupt::attachInterrupt(void (*isr)(RunLoopInterrupt*))
{
  _interruptCallback = isr;
}

void RunLoopInterrupt::detachInterrupt()
{
  _interruptCallback = NULL;
}

void RunLoopInterrupt::hardwareLoop()
{
  // Take care to ancestors state if exist cause we do not deal with "official run loop"
  if( !this->areAncestorsIdle() )
  {
    //
    // Fire according to callback, delegate, or inheritance
    //
    
    if( _interruptCallback )
    {
      // Send the work to callback
      _interruptCallback(this);
    }
    else if( _interruptDelegate )
    {
      // Send the work to delegate
      _interruptDelegate->interrupt(this);
    }
    else
    {
      // Do the work within the class or subclass
      this->interrupt();
    }
    
    // Execute sub objects if availables
    RunLoopObject::loop();
  }
}
