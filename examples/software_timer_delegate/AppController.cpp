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
  // First timer will fire every second. 
  timer1 = new RunLoopTimer();
  timer1->setTimerDelegate(this);
  timer1->setDelay(1000);
  this->addToRunLoop(timer1);

  // Second timer will fire 1/100s.
  timer2 = new RunLoopTimer();
  timer2->setTimerDelegate(this);
  timer2->setDelay(100);
  this->addToRunLoop(timer2);
}

AppController::~AppController()
{
  delete timer1;
  delete timer2;
}

void AppController::fire(RunLoopTimer *sender)
{
  if( sender == timer1 )
  {
    Serial.print("Timer 1: ");
    Serial.println(millis());
  }
  else if( sender == timer2 )
  {
    Serial.print("   Timer 2: ");
    Serial.println(millis());

    // Just for fun, we stop timer2 after 10s
    if( countT2 == 0 )
    {
      timer2->setIdle(true);
    }

    countT2--;
  }
}
