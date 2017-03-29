/*
 * AppController.cpp
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

#include "AppController.hpp"

AppController::AppController()
{
  //
  // Setup is here
  //

  Serial.begin(9600);

  Serial.println(F("We are in the setup."));
}

void AppController::loop()
{
  //
  // Your loop is here
  //

  Serial.println(F("We are in the main loop."));

  this->smartDelay(1000);
  
  RunLoopObject::loop();
}

