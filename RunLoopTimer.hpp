/*
 * RunLoopTimer.hpp
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
#ifndef RunLoopTimer_hpp
#define RunLoopTimer_hpp

// Model
#include "RunLoopObject.hpp"


class RunLoopTimer;

/*!
 *  The class RunLoopHardwareTimerDelegate is used to define delegation paradigm for timers.
 *
 *  @ingroup Protocol
 */
class RunLoopTimerDelegate
{
  
public:
  
  /*! This method is called when timer requests an interrupt. */
  virtual void fire(RunLoopTimer *sender) = 0;
  
};

/*!
 * The class manages a software timer. Unlike hardware timers, you can create as many software timers as you want (or
 * as your memory will allow).
 *
 * There is three ways to use this class:
 * - Create a sublcass, inherit from RunLoopHardwareTimer0 and overwrite fire().
 * - Instantiate a RunLoopHardwareTimer0 object and use a delegate which conforms to RunLoopTimerDelegate protocol.
 * - Use attachInterrupt() to set a simple C function as call back.
 *
 *  @ingroup Model
 */
class RunLoopTimer : public RunLoopObject
{
  
public:
  
#pragma mark -
#pragma mark Create and destroy

  RunLoopTimer();  
  ~RunLoopTimer();
  
#pragma mark -
#pragma mark Virtual methods for subclass overwrite
  
  /*! Method executed each time delay is elapsed. User should overwrite this method when subclassing RunLoopTimer. */
  virtual void fire() {};

  /*! Set the timer delay in milliseconds. */
  virtual void setDelay(unsigned long delay);
  
  /*! Set delay in microseconds (millis/1000) for compatibility with hardware timers. */
  virtual void setMicroDelay(unsigned long delay);
  
  /*! Overwrite virtual method of RunLoopObject. Hardware timers overwrite this method too. */
  virtual void loop();
  
#pragma mark -
#pragma mark Usuals
  
  /*! Set delegate for asynchronous feedback. If not set, fire() method is call. */
  void setTimerDelegate(RunLoopTimerDelegate *delegate);
  
  /*! Get delegate for asynchronous feedback. */
  inline RunLoopTimerDelegate *timerDelegate() {return _timerDelegate;};
  
  /*! Get last starting time of timer.*/
  inline unsigned long startTime() {return _startTime;};
  
  /*! Set call back function for C backward compatibility if needed. */
  void attachInterrupt(void (*fire)(RunLoopTimer*));
  
  /*! Unset call back function for C backward compatibility if needed. */
  void detachInterrupt();
  
  
protected:
  
  /*! Delay in milliseconds. */
  unsigned long _delay = 0;
  
  /*! Start time of the last fire. */
  unsigned long _startTime = 0;
  
  /*! Call back function for C backward compatibility if needed. */
  void (*_fireCallback)(RunLoopTimer*) = NULL;
  
  /*! Fire according to callback, delegate, or inheritance. */
  void railSwitchingFire();
  
private:
  
  /*! Delegate for feedback. */
  RunLoopTimerDelegate *_timerDelegate = NULL;
};

#endif