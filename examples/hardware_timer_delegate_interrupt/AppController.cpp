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
  timer1 = new RunLoopHardwareTimer0();
  timer1->setTimerDelegate(this);
  timer1->setDelay(1000);
  this->addToRunLoop(timer1);

  // Second timer will fire at 1/100s.
  timer2 = new RunLoopHardwareTimer1();
  timer2->setTimerDelegate(this);
  timer2->setDelay(100);
  this->addToRunLoop(timer2);

  // Add an interrupt to catch a push button on pin 2.
  // If you do not have a button, you can use a wire and 
  // set/unset pin 2 to the ground.
  interruptPin2 = new RunLoopInterruptPin2(INPUT_PULLUP,RISING);
  interruptPin2->setInterruptDelegate(this);
  this->addToRunLoop(interruptPin2);
}

AppController::~AppController()
{
  delete timer1;
  delete timer2;
  delete interruptPin2;
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
  }
}

void AppController::interrupt(RunLoopInterrupt *sender)
{
  // Start/stop timer2 when button pressed
  timer2->setIdle(!timer2->isIdle());
}

