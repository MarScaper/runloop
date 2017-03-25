/*
 * AppController.hpp
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
#ifndef AppController_hpp
#define AppController_hpp

#include <RunLoop.h>

#include "BuzzerView.hpp"

/*
 * AppController inherits from RunLoopObject and from RunLoopTimerDelegate.
 * 
 * RunLoopTimerDelegate is an abstract class used to create a protocol. 
 * As a result, delegate must conforms to protocol by implementing 
 * “fire(RunLoopTimer *sender)“ method. When timers will fire,  timers will call
 * the method. It's a smart way to deal with asynchronous feedbacks in C++.
 */
class AppController : public RunLoopObject, RunLoopTimerDelegate
{
  
public:

  AppController();
  ~AppController();

  // Declare delegate method according to RunLoopTimerDelegate protocol.
  void fire(RunLoopTimer *sender);

  // Overwrite virtual method of RunLoopObject to do another job.
  void loop();

private:

  // A buzzer to play music
  BuzzerView *buzzer = NULL;

  // A timer to launch, relaunch, relaunch... music cause the show must go on! 
  RunLoopTimer *timer = NULL;
};

#endif
