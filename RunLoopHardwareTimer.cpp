/*
 * RunLoopHardwareTimer.cpp
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

#include "RunLoopHardwareTimer.hpp"

// Prescale values for 8-Bit Timers
#define PRESCALE_8_0     B0000
#define PRESCALE_8_1     B0001
#define PRESCALE_8_8     B0010
#define PRESCALE_8_32    B0011
#define PRESCALE_8_64    B0100
#define PRESCALE_8_128   B0101
#define PRESCALE_8_256   B0110
#define PRESCALE_8_1024  B0111

// Prescale values for 16-Bit Timers
#define PRESCALE_16_0     B0000
#define PRESCALE_16_1     B0001
#define PRESCALE_16_8     B0010
#define PRESCALE_16_64    B0011
#define PRESCALE_16_256   B0100
#define PRESCALE_16_1024  B0101

RunLoopHardwareTimer::RunLoopHardwareTimer()
{
  // init timer data
  _timerPreset.clockSelectBits = 0;
  _timerPreset.counterReset    = 0;
  _timerPreset.outOfBounds     = 0;
  _timerPreset.shouldRiseCount = 0;
}

RunLoopHardwareTimer::~RunLoopHardwareTimer()
{
}

bool RunLoopHardwareTimer::clockSelectBitsCounterResetAndPrescaleForDelayAndResolution(unsigned long delay, unsigned long resolution, unsigned char *clockSelectBits, unsigned short *counterReset, unsigned short *prescale, unsigned long *cycles)
{
  bool isOutOfBounds = false;
  
  unsigned long cpuSpeed = F_CPU/1000000;
  
  *cycles = cpuSpeed * delay;
  
  // For perfect precision, we must keep in mind the irq overhead of the arduino library.
  // A very good explanation on Bill Grundmann’s Blog:
  // https://billgrundmann.wordpress.com/2009/03/02/the-overhead-of-arduino-interrupts/
  int irq_overhead = 55; // cycles
  if( *cycles > irq_overhead )
  {
    *cycles -= irq_overhead;
  }
  else
  {
    *cycles = 1;
  }
  
  if( resolution == 256 )
  {
    //
    // 8-Bit Timer
    //
    
    *prescale = PRESCALE_8_0;
    if(*cycles < resolution)
    {
      *clockSelectBits = PRESCALE_8_1;
      *prescale = 1;
    }
    else if(*cycles < resolution*8)
    {
      *clockSelectBits = PRESCALE_8_8;
      *prescale = 8;
    }
    else if(*cycles < resolution*32)
    {
      *clockSelectBits = PRESCALE_8_32;
      *prescale = 32;
    }
    else if(*cycles < resolution*64)
    {
      *clockSelectBits = PRESCALE_8_64;
      *prescale = 64;
    }
    else if(*cycles < resolution*128)
    {
      *clockSelectBits = PRESCALE_8_128;
      *prescale = 128;
    }
    else if(*cycles < resolution*256)
    {
      *clockSelectBits = PRESCALE_8_256;
      *prescale = 256;
    }
    else
    {
      *clockSelectBits = PRESCALE_8_1024;
      *prescale = 1024;
      
      isOutOfBounds = true;
    }
  }
  else if( resolution == 65536 )
  {
    //
    // 16-Bit Timer
    //
    
    *prescale = PRESCALE_16_0;
    if(*cycles < resolution)
    {
      *clockSelectBits = PRESCALE_16_1;
      *prescale = 1;
    }
    else if(*cycles < resolution*8)
    {
      *clockSelectBits = PRESCALE_16_8;
      *prescale = 8;
    }
    else if(*cycles < resolution*64)
    {
      *clockSelectBits = PRESCALE_16_64;
      *prescale = 64;
    }
    else if(*cycles < resolution*256)
    {
      *clockSelectBits = PRESCALE_16_256;
      *prescale = 256;
    }
    else
    {
      *clockSelectBits = PRESCALE_16_1024;
      *prescale = 1024;
      
      isOutOfBounds = true;
    }
  }
  
  if( !isOutOfBounds )
  {
    // Set counter to the needed value
    *counterReset = resolution-1-*cycles / *prescale;
  }
  else
  {
    // Set counter as long as possible.
    *counterReset = 0;
  }
  
  *cycles += irq_overhead;
  
  return isOutOfBounds;
}

void RunLoopHardwareTimer::hardwareLoop()
{
  bool ancestorsIdle = false;
  if( _ancestor )
  {
    ancestorsIdle = this->areAncestorsIdle();
  }
  
  // Take care to ancestors state if exist cause we do not deal with "official run loop"
  if( !ancestorsIdle )
  {
    if( !_timerPreset.outOfBounds )
    {
      // Fire according to callback, delegate, or inheritance
      this->railSwitchingFire();
    }
    else
    {
      _timerPreset.shouldRiseCount--;
      
      if( _timerPreset.shouldRiseCount == 0 )
      {
        // Fire according to callback, delegate, or inheritance
        this->railSwitchingFire();
        
        // Reset rise count
        _timerPreset.shouldRiseCount = _timerPreset.outOfBounds;
      }
    }
  }
}
