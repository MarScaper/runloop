/*
 * app_controller_template.ino
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
  * This sample code is a simple template with an application controller
  * class inheriting from RunLoopObject. It's a good starting point
  * to create an empty project using RunLoop library.
  * 
  * Arduino's version of main() is replaced for optimizations.
  */

#include "AppController.hpp"

// Replica of the Arduino's version of main() with minor changes
// for direct call to AppController's loop.
int main( void )
{
  //Initialise Arduino functionality.
  init();
  
  //Attach USB for applicable processors.
#ifdef USBCON
  USBDevice.attach();
#endif
  
  // Main app controller. The magic hat... ;)
  AppController *appController = new AppController();
  
  for(;;)
  {
    //Application controller's loop method.
    appController->loop();
    
    //Process the serial libaries event queue.
    if( serialEventRun ) serialEventRun();
  }
  
  //Execution should never reach this point.
  return 0x00;
}
