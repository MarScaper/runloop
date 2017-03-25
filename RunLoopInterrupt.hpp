/*
 * RunLoopInterrupt.hpp
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
#ifndef RunLoopInterrupt_hpp
#define RunLoopInterrupt_hpp

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "Arduino.h"

// Small hack to avoid naming conflict between class method end C function for
// attachInterrupt(...) and detachInterrupt(...).
extern void _attachInterrupt(uint8_t interruptNum, void (*userFunc)(void), int mode);
extern void _detachInterrupt(uint8_t interruptNum);

#endif

/*

 Board	Digital Pins Usable For Interrupts
 
 Uno, Nano, Mini, other 328-based	2, 3
 
 Mega, Mega2560, MegaADK	2, 3, 18, 19, 20, 21
 Micro, Leonardo, other 32u4-based	0, 1, 2, 3, 7
 Zero	all digital pins, except 4
 MKR1000 Rev.1	0, 1, 4, 5, 6, 7, 8, 9, A1, A2
 Due	all digital pins
 101	all digital pins
 
 */


// Model
#include "RunLoopObject.hpp"

class RunLoopInterrupt;

/*!
 *  The class RunLoopHardwareinterruptDelegate is used to define delegation paradigm for interrupts.
 *
 *  @ingroup Protocol
 */
class RunLoopInterruptDelegate
{
  
public:
  
  /*! This method is called when an interrupt rise. */
  virtual void interrupt(RunLoopInterrupt *sender) = 0;
  
};

/*!
 * The class manages common interrupts behaviour.
 *
 *  @ingroup Model
 */
class RunLoopInterrupt : public RunLoopObject
{
  
public:
  
#pragma mark -
#pragma mark Create and destroy
  
  RunLoopInterrupt();
  ~RunLoopInterrupt();
  
#pragma mark -
#pragma mark Virtual methods for subclass overwrite
  
  /*! Method executed each time delay is elapsed. User should overwrite this method when subclassing RunLoopTimer. */
  virtual void interrupt() = 0;
  
#pragma mark -
#pragma mark Usuals
  
  /*! Set delegate for asynchronous feedback. If not set, fire() method is call. */
  void setInterruptDelegate(RunLoopInterruptDelegate *delegate);
  
  /*! Get delegate for asynchronous feedback. */
  inline RunLoopInterruptDelegate *interruptDelegate() {return _interruptDelegate;};

  /*! Set call back function for C backward compatibility if needed. */
  void attachInterrupt(void (*interrupt)(RunLoopInterrupt*));
  
  /*! Unset call back function for C backward compatibility if needed. */
  void detachInterrupt();
  
#pragma mark -
#pragma mark Internal use but needed as public for direct timer access in ISR
  
  /*! Real loop replacing software loop. */
  void hardwareLoop();
  
protected:
  
  /*! Call back function for C backward compatibility if needed. */
  void (*_interruptCallback)(RunLoopInterrupt*) = NULL;

private:
  
  /*! Delegate for feedback. */
  RunLoopInterruptDelegate *_interruptDelegate = NULL;
  
  /*! Interrupt need to avoid software loop cause job will be redirected to hardwareLoop(). */
  void loop() {};
};

#endif
