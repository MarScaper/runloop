/*
 * RunLoopTimer.cpp
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

#include <stdlib.h>
#include <Arduino.h>

#include "RunLoopTimer.hpp"

RunLoopTimer::RunLoopTimer()
{
}

RunLoopTimer::~RunLoopTimer()
{
}

void RunLoopTimer::setDelay(unsigned long delay)
{
  _delay = delay;
  _startTime = millis();
  
  if( !_isIdle )
  {
    //
    // Fire immediately
    //
    
    // Reset the timer
    _startTime = millis();
    
    this->railSwitchingFire();
  }
}

void RunLoopTimer::setMicroDelay(unsigned long delay)
{
  this->setDelay(delay/1000);
}

#if RUN_LOOP_FULL || RUN_LOOP_DELEGATE
void RunLoopTimer::setTimerDelegate(RunLoopTimerDelegate *delegate)
{
  _timerDelegate = delegate;
  
  if( _timerDelegate )
  {
    timerMode = RunLoopTimerModeDelegate;
  }
  else
  {
    timerMode = RunLoopTimerModeInheritance;
  }
}
#endif

void RunLoopTimer::loop()
{
  // Take care to ancestor state if exists cause we do not deal with "official run loop"
  if( (!this->ancestor() || !this->ancestor()->isIdle()) && _isIdle == false )
  {
    if (millis() >= _startTime+_delay )
    {
      // Reset the timer
      _startTime = millis();
      
      this->railSwitchingFire();
    }
  }
}

void RunLoopTimer::railSwitchingFire()
{
  
#if 0
#if RUN_LOOP_FULL
  
  if( _fireCallback )
  {
    // Send the work to callback
    _fireCallback(this);
  }
  else if( _timerDelegate )
  {
    // Send the work to delegate
    _timerDelegate->fire(this);
  }
  else
  {
    // Do the work within the class or subclass
    this->fire();
  }
  
#else
  
#if RUN_LOOP_CALLBACK
  
  if( _fireCallback )
  {
    // Send the work to callback
    _fireCallback(this);
  }
#if RUN_LOOP_INHERITANCE
  else
  {
    // Do the work within the class or subclass
    this->fire();
  }
#endif
  
#endif
  
#if RUN_LOOP_DELEGATE
  
  if( _timerDelegate )
  {
    // Send the work to delegate
    _timerDelegate->fire(this);
  }
#if RUN_LOOP_INHERITANCE
  else
  {
    // Do the work within the class or subclass
    this->fire();
  }
#endif
  
#endif
  
#if RUN_LOOP_INHERITANCE && !RUN_LOOP_CALLBACK && !RUN_LOOP_DELEGATE
  
  // Do the work within the class or subclass
  this->fire();
  
#endif
  
#endif
  
#endif
  
  switch (timerMode)
  {
#if RUN_LOOP_FULL || RUN_LOOP_CALLBACK
    case RunLoopTimerModeCallback:
      // Send the work to callback
      _fireCallback(this);
      break;
#endif
      
#if RUN_LOOP_FULL || RUN_LOOP_DELEGATE
    case RunLoopTimerModeDelegate:
      // Send the work to delegate
      _timerDelegate->fire(this);
      break;
#endif
      
#if RUN_LOOP_FULL || RUN_LOOP_INHERITANCE
    default:
      // Do the work within the class or subclass
      this->fire();
      break;
#else
    default:
      break;
#endif
      
  }
  
  // Speed optimization (2.6us)
  if( _runLoopObjectCount )
  {
    // Execute sub objects if availables
    RunLoopObject::loop();
  }
}

#if RUN_LOOP_FULL || RUN_LOOP_CALLBACK
void RunLoopTimer::attachInterrupt(void (*isr)(RunLoopTimer*))
{
  _fireCallback = isr;
  
  timerMode = RunLoopTimerModeCallback;
}

void RunLoopTimer::detachInterrupt()
{
  _fireCallback = NULL;
  
  timerMode = RunLoopTimerModeInheritance;
}
#endif
