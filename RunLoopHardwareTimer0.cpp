/*
 * RunLoopHardwareTimer0.cpp
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

#include <avr/io.h>
#include <avr/interrupt.h>

#include "RunLoopConfig.hpp"
#include "RunLoopHardwareTimer0.hpp"

// Timer resolution
#define TIMER_RESOLUTION 256UL

// Prescale values
#define PRESCALE_0     B0000

// Generic defines for registers
#define TIMSK TIMSK0
#define OCRA  OCR0A

//  Global pointer needed to acces instance in ISR
static RunLoopHardwareTimer *__timerInstance = NULL;

#if ENABLE_RUNLOOP_TIMER_0_INTERRUPT
// Interrupt is called once a millisecond,
SIGNAL(TIMER0_COMPA_vect)
{
  // Timer0 work like a software timer so we
  // just need to use the standard loop.
  __timerInstance->RunLoopTimer::loop();
}
#endif

RunLoopHardwareTimer0::RunLoopHardwareTimer0()
{
  // Set local static instance for acces in ISR
  __timerInstance = this;
}

RunLoopHardwareTimer0::~RunLoopHardwareTimer0()
{
  __timerInstance = NULL;
}

void RunLoopHardwareTimer0::setDelay(unsigned long delay)
{
  RunLoopTimer::setDelay(delay);
  
  // Timer0 is already used for millis() - we'll just interrupt somewhere
  // in the middle and call the "Compare A" function below
  OCRA = 0x7F;
  TIMSK |= _BV(OCIE0A);
}

void RunLoopHardwareTimer0::setMicroDelay(unsigned long delay)
{
  this->setDelay(round(delay/1000.0));
}

void RunLoopHardwareTimer0::setIdle(bool state)
{
  this->RunLoopTimer::setIdle(state);
  
  if( _isIdle == true)
  {
    // Disable interruption
    TIMSK &= ~(_BV(OCIE0A));
  }
  else
  {
    // Enable interruption
    TIMSK |= _BV(OCIE0A);
  }
}

TimerPreset RunLoopHardwareTimer0::timerPresetForMicroDelay(unsigned long delay)
{
  TimerPreset timer;
  
  timer.clockSelectBits = 0;
  timer.counterReset    = 0;
  timer.outOfBounds     = 0;
  timer.shouldRiseCount = 0;
  
  return timer;
}
