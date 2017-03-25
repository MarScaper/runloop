/*
 * software_timer_delegate_interrupt.ino
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
 * This sample code shows the way to use hardware timers and a button rising 
 * an interrupt with a full C++ approach.
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
