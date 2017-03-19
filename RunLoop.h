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
#include <RunLoopTimer.hpp>
#include <RunLoopHardwareTimer0.hpp>
#include <RunLoopHardwareTimer1.hpp>
#include <RunLoopHardwareTimer2.hpp>

// Timers only availables with Arduino Mega
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#include <RunLoopHardwareTimer3.hpp>
#include <RunLoopHardwareTimer4.hpp>
#include <RunLoopHardwareTimer5.hpp>
#endif

#endif

