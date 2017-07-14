/*
 * RunLoopHardwareTimer5.cpp
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

// Timer only available with Arduino Mega
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)

#include <avr/io.h>
#include <avr/interrupt.h>

#include "RunLoopHardwareTimer5.hpp"

// Timer resolution
#define TIMER_RESOLUTION 65536UL

// Prescale values
#define PRESCALE_0     B0000

// Generic defines for registers
#define TCNT  TCNT5
#define TIFR  TIFR5
#define TCCRA TCCR5A
#define TCCRB TCCR5B
#define TCNT  TCNT5
#define TIMSK TIMSK5
#define INTERRUPT_COST 3.2946428571

//  Global pointer needed to acces instance in ISR
static RunLoopHardwareTimer *__timerInstance = NULL;
static TimerPreset          *__timerPreset   = NULL;

ISR(TIMER5_OVF_vect)
{
  // Reset timer
  TCNT = __timerPreset->counterReset;
  TIFR = 0x00;
  
  // Do the job
  __timerInstance->hardwareLoop();
}

RunLoopHardwareTimer5::RunLoopHardwareTimer5()
{
  // Set local static instances for acces in ISR
  __timerInstance = this;
  __timerPreset   = &_timerPreset;
}

RunLoopHardwareTimer5::~RunLoopHardwareTimer5()
{
  TCCRB = PRESCALE_0;
  __timerInstance = NULL;
  __timerPreset   = NULL;
}

void RunLoopHardwareTimer5::setDelay(unsigned long delay)
{
  this->setMicroDelay(delay*1000);
}

void RunLoopHardwareTimer5::setMicroDelay(unsigned long delay)
{
  _microDelay = delay;
  
  _timerPreset = this->timerPresetForMicroDelay(_microDelay);
  
  // Initialize timer
  noInterrupts();              // disable all interrupts
  TCCRA = 0;
  TCCRB = PRESCALE_0;          // Disable timer
  TIMSK = 1;                   // enable timer overflow interrupt
  interrupts();
  
  this->setTimerPreset(&_timerPreset);
}

void RunLoopHardwareTimer5::setIdle(bool state)
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
      // Launch timer
      TCCRB = __timerPreset->clockSelectBits;
      TCNT  = __timerPreset->counterReset;
      
      __timerInstance->hardwareLoop();
    }
  }
}

TimerPreset RunLoopHardwareTimer5::timerPresetForMicroDelay(unsigned long microDelay)
{
  TimerPreset timer;
  
  // Calculate prescale, clock select bits and counter reset according to delay and timer resolution
  timer.outOfBounds = 0;
  unsigned short prescale;
  if( this->clockSelectBitsCounterResetAndPrescaleForDelayAndResolution(microDelay,TIMER_RESOLUTION,&timer.clockSelectBits,&timer.counterReset,&prescale,INTERRUPT_COST) )
  {
    timer.outOfBounds=1000;
    microDelay /= 1000;
    this->clockSelectBitsCounterResetAndPrescaleForDelayAndResolution(microDelay,TIMER_RESOLUTION,&timer.clockSelectBits,&timer.counterReset,&prescale,INTERRUPT_COST);
  }
  timer.shouldRiseCount = timer.outOfBounds;
  
  return timer;
}

void RunLoopHardwareTimer5::setTimerPreset(TimerPreset *timerPreset)
{
  // Copy timer content to local preset
  _timerPreset = *timerPreset;
  
  // Set global preset address
  __timerPreset = &_timerPreset;
  
  if( !_isIdle )
  {
    // Launch timer
    TCCRA = 0;
    TCCRB = __timerPreset->clockSelectBits;
    TCNT  = __timerPreset->counterReset;
    TIMSK = 1;
  }
}
#endif