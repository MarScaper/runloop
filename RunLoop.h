/*
 * RunLoop.h
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
 
#ifndef RunLoop_library
#define RunLoop_library

#include <RunLoopObject.hpp>

// Timers
#include <RunLoopTimer.hpp>
#include <RunLoopHardwareTimer0.hpp>
#include <RunLoopHardwareTimer1.hpp>
#include <RunLoopHardwareTimer2.hpp>
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) // Timers only availables with Arduino Mega
#include <RunLoopHardwareTimer3.hpp>
#include <RunLoopHardwareTimer4.hpp>
#include <RunLoopHardwareTimer5.hpp>
#endif

// Interrupts
#include <RunLoopInterrupt.hpp>
#include <RunLoopInterruptPin0.hpp>
#include <RunLoopInterruptPin1.hpp>
#include <RunLoopInterruptPin2.hpp>
#include <RunLoopInterruptPin3.hpp>
#include <RunLoopInterruptPin4.hpp>
#include <RunLoopInterruptPin5.hpp>
#include <RunLoopInterruptPin6.hpp>
#include <RunLoopInterruptPin7.hpp>
#include <RunLoopInterruptPin8.hpp>
#include <RunLoopInterruptPin9.hpp>
#include <RunLoopInterruptPin10.hpp>
#include <RunLoopInterruptPin11.hpp>
#include <RunLoopInterruptPin12.hpp>
#include <RunLoopInterruptPin13.hpp>
#include <RunLoopInterruptPinA0.hpp>
#include <RunLoopInterruptPinA1.hpp>
#include <RunLoopInterruptPinA2.hpp>
#include <RunLoopInterruptPinA3.hpp>
#include <RunLoopInterruptPinA4.hpp>
#include <RunLoopInterruptPinA5.hpp>

#endif

