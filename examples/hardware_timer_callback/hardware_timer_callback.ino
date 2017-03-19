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
  * This sample code shows the way to use hardware timers alone with a simple C function call back.
  * The only change compared to software_timer_callback.ino is the class instantiation.
  *
  * Hardware timers inherit from RunLoopTimer and work exactly in the same way (see inheritance 
  * diagram for details). As a result, they are perfectly interchangeable. :)
  *
  * RunLoop library embed RunLoopHardwareTimer0, RunLoopHardwareTimer1, RunLoopHardwareTimer2, 
  * RunLoopHardwareTimer3, RunLoopHardwareTimer4, RunLoopHardwareTimer5. Timers 3,4,5 are only
  * availables with Arduino Mega.
  */

#include <RunLoop.h>

static int countT2 = 100;

RunLoopTimer *timer1 = NULL;
RunLoopTimer *timer2 = NULL;

void setup() 
{
  // Start serial
  Serial.begin(9600);

  // First timer will fire every second. 
  timer1 = new RunLoopHardwareTimer0();
  timer1->attachInterrupt(fire);
  timer1->setDelay(1000);

  // Second timer will fire 1/100s.
  timer2 = new RunLoopHardwareTimer1();
  timer2->attachInterrupt(fire);
  timer2->setDelay(100);
}

// Unlike other timer libraries, attachInterrupt(...) takes 
// a function with a timer object as paramater. As a result,
// we can use the same function for serveral timers and we
// just need to test the sender.
void fire(RunLoopTimer *sender)
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

void loop() 
{
  // Update each timer
  timer1->loop();
  timer2->loop();
}
