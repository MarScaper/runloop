/*
 * blink.ino
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
  * This sample code shows the way to use software or hardware timer alone with a simple C function call back.
  */

#include <RunLoop.h>

bool ledState = false;
RunLoopTimer *timer = NULL;

void setup() 
{
  // Initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Comment/Uncomment the timer you want... 
  {
    // Use a software timer
    timer = new RunLoopTimer();
  
    // Use hardware Timer 2
    //timer = new RunLoopHardwareTimer2();
  }
  
  timer->attachInterrupt(blink);
  timer->setDelay(1000);
}

void loop() 
{
  // Update timer
  timer->loop();
}

void blink(RunLoopTimer *sender)
{
  //
  // Change led state
  //
  
  if( ledState == false )
  {
    digitalWrite(LED_BUILTIN, HIGH);
    ledState = true; 
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW); 
    ledState = false; 
  }
}
