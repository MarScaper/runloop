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

/*
 * AppController inherits from RunLoopObject and will be the main class.
 */
class AppController : public RunLoopObject
{
  
public:

  // Constructor for setup
  AppController();

  // Overwrite virtual method of RunLoopObject 
  void loop();
};

#endif
