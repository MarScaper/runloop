/*
 * RunLoopHardwareTimer1.cpp
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

#include "RunLoopHardwareTimer1.hpp"

// Timer resolution
#define TIMER_RESOLUTION 65536UL

// Prescale values
#define PRESCALE_0     B0000

// Generic defines for registers
#define TCNT  TCNT1
#define TIFR  TIFR1
#define TCCRA TCCR1A
#define TCCRB TCCR1B
#define TCNT  TCNT1
#define TIMSK TIMSK1

//  Global pointer needed to acces instance in ISR
static RunLoopHardwareTimer *__timerInstance = NULL;

ISR(TIMER1_OVF_vect)
{
  // Get timer data for counter reset value
  TimerStruct *timer = __timerInstance->timer();
  
  // Reset timer
  TCNT = timer->counterReset;
  TIFR = 0x00;
  
  // Do the job
  __timerInstance->hardwareLoop();
}

RunLoopHardwareTimer1::RunLoopHardwareTimer1()
{
  // Set local static instance for acces in ISR
  __timerInstance = this;
}

RunLoopHardwareTimer1::~RunLoopHardwareTimer1()
{
  TCCRB = PRESCALE_0;
  __timerInstance = NULL;
}

void RunLoopHardwareTimer1::setDelay(unsigned long delay)
{
  this->setMicroDelay(delay*1000);
}

void RunLoopHardwareTimer1::setMicroDelay(unsigned long delay)
{
  _microDelay = delay;
  
  // Calculate prescale, clock select bits and counter reset according to delay and timer resolution
  _timer.outOfBounds = 0;
  unsigned short prescale;
  if( this->clockSelectBitsCounterResetAndPrescaleForDelayAndResolution(delay,TIMER_RESOLUTION,&_timer.clockSelectBits,&_timer.counterReset,&prescale) )
  {
    _timer.outOfBounds=1000;
    delay /= 1000;
    this->clockSelectBitsCounterResetAndPrescaleForDelayAndResolution(delay,TIMER_RESOLUTION,&_timer.clockSelectBits,&_timer.counterReset,&prescale);
  }
  _timer.shouldRiseCount = _timer.outOfBounds;
  
  // Initialize timer
  noInterrupts();              // disable all interrupts
  TCCRA = 0;
  TCCRB = PRESCALE_0;          // Disable timer
  TCNT  = _timer.counterReset; // preload timer
  TIMSK = 1;                   // enable timer overflow interrupt
  interrupts();
  
  if( !this->isIdle() )
  {
    // Fire timer immediately
    TCNT  = TIMER_RESOLUTION-1;
    TCCRB = _timer.clockSelectBits;
  }
}

void RunLoopHardwareTimer1::setIdle(bool state)
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
      TCCRB = _timer.clockSelectBits;
    }
  }
}