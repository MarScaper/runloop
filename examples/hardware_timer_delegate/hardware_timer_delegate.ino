/*
 * software_timer_callback.ino
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

/*
 * This sample code shows the way to use hardware timers with a full C++ approach.
 * The only change compared to software_timer_delegate.ino is the class instantiation.
 *
 * Hardware timers inherit from RunLoopTimer and work exactly in the same way (see inheritance 
 * diagram for details). As a result, they are perfectly interchangeable. :)
 *
 * RunLoop library embed RunLoopHardwareTimer0, RunLoopHardwareTimer1, RunLoopHardwareTimer2, 
 * RunLoopHardwareTimer3, RunLoopHardwareTimer4, RunLoopHardwareTimer5. Timers 3,4,5 are only
 * availables with Arduino Mega.
 */

#include "AppController.hpp"

AppController *appController = NULL;

void setup() 
{
  // Start serial
  Serial.begin(9600);

  // Create the main controller.
  appController = new AppController();  
}

void loop() 
{
  // Application controller loop.
  appController->loop();
}
