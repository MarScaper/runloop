/*
 * RunLoopHardwareTimer2.cpp
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

#include "RunLoopHardwareTimer2.hpp"

// Timer resolution
#define TIMER_RESOLUTION 256UL

// Prescale values
#define PRESCALE_0     B0000

// Generic defines for registers
#define TCNT  TCNT2
#define TIFR  TIFR2
#define TCCRA TCCR2A
#define TCCRB TCCR2B
#define TCNT  TCNT2
#define TIMSK TIMSK2
#define INTERRUPT_COST 3.0816326531

//  Global pointer needed to acces instance in ISR
static RunLoopHardwareTimer *__timerInstance = NULL;
static TimerPreset          *__timerPreset   = NULL;

ISR(TIMER2_OVF_vect)
{
  // Reset timer
  TCNT = __timerPreset->counterReset;
  TIFR = 0x00;
  
  // Do the job
  __timerInstance->hardwareLoop();
}

RunLoopHardwareTimer2::RunLoopHardwareTimer2()
{
  // Set local static instances for acces in ISR
  __timerInstance = this;
  __timerPreset = &_timerPreset;
}

RunLoopHardwareTimer2::~RunLoopHardwareTimer2()
{
  TCCRB = PRESCALE_0;
  __timerInstance = NULL;
  __timerPreset = NULL;
}

void RunLoopHardwareTimer2::setDelay(unsigned long delay)
{
  this->setMicroDelay(delay*1000);
}

void RunLoopHardwareTimer2::setMicroDelay(unsigned long delay)
{
  _microDelay = delay;

  // Calculate prescale, clock select bits and counter reset according to delay and timer resolution
  _timerPreset.outOfBounds = 0;
  unsigned short prescale;
  if( this->clockSelectBitsCounterResetAndPrescaleForDelayAndResolution(delay,TIMER_RESOLUTION,&_timerPreset.clockSelectBits,&_timerPreset.counterReset,&prescale,INTERRUPT_COST) )
  {
    _timerPreset.outOfBounds=1000;
    delay /= 1000;
    this->clockSelectBitsCounterResetAndPrescaleForDelayAndResolution(delay,TIMER_RESOLUTION,&_timerPreset.clockSelectBits,&_timerPreset.counterReset,&prescale,INTERRUPT_COST);
  }
  _timerPreset.shouldRiseCount = _timerPreset.outOfBounds;
  
  // Initialize timer
  noInterrupts();              // disable all interrupts
  TCCRA = 0;
  TCCRB = PRESCALE_0;          // Disable timer
  TCNT  = _timerPreset.counterReset; // preload timer
  TIMSK = 1;                   // enable timer overflow interrupt
  interrupts();
  
  if( !this->isIdle() )
  {
    // Fire timer immediately
    TCNT  = TIMER_RESOLUTION-1;
    TCCRB = _timerPreset.clockSelectBits;
  }
}

void RunLoopHardwareTimer2::setIdle(bool state)
{
  if( state != this->isIdle() )
  {
    _isIdle = state;
    
    if( _isIdle )
    {
      TCCRB = PRESCALE_0;
    }
    else if( _microDelay )
    {
      TCNT  = TIMER_RESOLUTION-1;
      TCCRB = _timerPreset.clockSelectBits;
    }
  }
}

TimerPreset RunLoopHardwareTimer2::timerPresetForMicroDelay(unsigned long delay)
{
  TimerPreset timer;
  
  timer.clockSelectBits = 0;
  timer.counterReset    = 0;
  timer.outOfBounds     = 0;
  timer.shouldRiseCount = 0;
  
  return timer;
}