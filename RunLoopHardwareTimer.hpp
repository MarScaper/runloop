/*
 * RunLoopHardwareTimer.hpp
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
#ifndef RunLoopHardwareTimer_hpp
#define RunLoopHardwareTimer_hpp

// Model
#include "RunLoopTimer.hpp"

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*
 *  Global structure used internally by timers to store parameters.
 */
struct TimerPreset
{
  unsigned char  clockSelectBits;
  unsigned short counterReset;
  unsigned long  outOfBounds;
  unsigned long  shouldRiseCount;
};
#endif


/*!
 * The class is a virtual superclass to manage hardware timers of the arduino.
 * Its purpose is to regroup all the common functions of hardware timers like
 * managing the hardware loop, calculate clock select bits, counter reset or
 * prescale.
 *
 *  @ingroup Model
 */
class RunLoopHardwareTimer : public RunLoopTimer
{
  
public:
  
#pragma mark -
#pragma mark Create and destroy
  
  RunLoopHardwareTimer();
  ~RunLoopHardwareTimer();
  
#pragma mark -
#pragma mark Virtual methods for subclass overwrite
  
#if RUN_LOOP_FULL || RUN_LOOP_INHERITANCE
  /*! Method executed each time delay is elapsed if delegate is not set. Subclasses need to overwrite this method. */
  virtual void fire() = 0;
#endif
  
  /*! Set the timer delay in milli seconds (us x 1000) for compatibility with software timers. */
  virtual void setDelay(unsigned long delay) = 0;
  
  /*! Set micro delay in micro seconds. */
  virtual void setMicroDelay(unsigned long delay) = 0;
  
  /*! Start or stop the loop. */
  virtual void setIdle(bool state) = 0;
  
#pragma mark -
#pragma mark Internal use but needed as public for direct timer access in ISR
  
  /*! Real loop replacing software loop. */
  void hardwareLoop();
  
  /*! Global structure used internally by timers to store parameters. */
  inline TimerPreset *timerPreset() {return &_timerPreset;};
  
  /*! Global structure used internally by timers to store parameters. */
  inline TimerPreset timerPresetForDelay(unsigned long delay) { return this->timerPresetForMicroDelay(delay*1000); };
  
  /*! Global structure used internally by timers to store parameters. */
  inline virtual TimerPreset timerPresetForMicroDelay(unsigned long delay) = 0;
  
  /*! Global structure used internally by timers to store parameters. */
  inline virtual void setTimerPreset(TimerPreset *timerPreset) = 0;
  
protected:
  
  /*! Global structure used internally by timers to store parameters. */
  TimerPreset _timerPreset;
  
  /*! Delay expressed in micro seconds. */
  unsigned long _microDelay=0;
  
  /*! Calculate timer parameters. */
  bool clockSelectBitsCounterResetAndPrescaleForDelayAndResolution(unsigned long delay, unsigned long resolution, unsigned char *clockSelectBits, unsigned short *counterReset, unsigned short *prescale, float interruptCoast=0);
  
private:
  
  /*! Hardware timers need to avoid software loop cause job will be redirected to hardwareLoop(). */
  void loop() {};
};

#endif
