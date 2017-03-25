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

#define BUZZER_PIN 4

AppController::AppController()
{
  // Start serial
  Serial.begin(9600);
  
  // Create the buzzer to play the melody
  buzzer = new BuzzerView(BUZZER_PIN);
  this->addToRunLoop(buzzer);

  // Now we'll use a timer to launch the melody again and again
  timer = new RunLoopTimer();
  timer->setTimerDelegate(this);
  timer->setDelay(7000);
  this->addToRunLoop(timer);
}

AppController::~AppController()
{
  delete buzzer;
  delete timer;
}

void AppController::fire(RunLoopTimer *sender)
{
  // Show must go on! :D
  buzzer->startIntroMelody();
}

void AppController::loop()
{
  // Oh! My god!
  Serial.println("Luke, I am Your Father.");

  // By using smartDelay() of RunLoopObject instead of standard delay() function, 
  // the loop will automatically update objects added to Its run loop. Its 
  // a much more convenient way to keep program (sensors, etc) up-to-date 
  // while waiting.
  this->smartDelay(1000);

  RunLoopObject::loop();
}

