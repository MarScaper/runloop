/*
 * RunLoopObject.cpp
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

#include "RunLoopObject.hpp"

#pragma mark -
#pragma mark Memory management

RunLoopObject::RunLoopObject()
{
}

RunLoopObject::~RunLoopObject()
{
  free(_runLoopObjectArray);
}

#pragma mark -
#pragma mark Run loop management

bool RunLoopObject::removeFromRunLoop(RunLoopObject *object, bool deleteObject)
{
  for( unsigned short numObject=0; numObject<_runLoopObjectCount; numObject++ )
  {
    RunLoopObject *currentObject = _runLoopObjectArray[numObject];
    
    if( currentObject == object )
    {
      // Unassign object
      _runLoopObjectArray[numObject] = NULL;
      
      // Delete if needed
      if( deleteObject )
      {
        delete currentObject;
      }
      
      return true;
    }
  }
  
  return false;
}

bool RunLoopObject::removeFromRunLoop(RunLoopObject *object)
{
  return this->removeFromRunLoop(object,false);
}

bool RunLoopObject::addToRunLoop(RunLoopObject *object)
{
  if( object->ancestor() )
  {
    // Object already in another run loop.
    return false;
  }
  
  
  for( unsigned short numObject=0; numObject<_runLoopObjectCount; numObject++ )
  {
    RunLoopObject *currentObject = _runLoopObjectArray[numObject];
    
    if( object == currentObject )
    {
      // Object already loaded in run loop.
      return false;
    }
    else if ( currentObject == NULL )
    {
      // Space available. We use It.
      _runLoopObjectArray[numObject] = object;
      
      // Set the ancestor
      object->setAncestor(this);
      
      return true;
    }
  }
  
  // Should we need to resize the array?
  if( _runLoopObjectCount == 0 )
  {
    _runLoopObjectArray = (RunLoopObject**)malloc(sizeof(RunLoopObject*));
  }
  else
  {
    _runLoopObjectArray = (RunLoopObject**)realloc(_runLoopObjectArray,sizeof(RunLoopObject*)*(_runLoopObjectCount+1));
  }
  
  // Set the ancestor
  object->setAncestor(this);
  
  // Add object to run loop array...
  _runLoopObjectArray[_runLoopObjectCount] = object;
  _runLoopObjectCount++;
  
  return true;
}

#pragma mark -
#pragma mark Virtual method for overwrite.

void RunLoopObject::setIdle(bool state)
{
  if( state != _isIdle )
  {
    _isIdle = state;
  }
}

void RunLoopObject::loop()
{
  if( _isIdle == true )
  {
    return;
  }
  
  for( unsigned short numObject=0; numObject<_runLoopObjectCount; numObject++ )
  {
    RunLoopObject *currentObject = _runLoopObjectArray[numObject];
    
    if( currentObject->isIdle() == false )
    {
      currentObject->loop();
    }
  }
}

#pragma mark -
#pragma mark Memory management

void RunLoopObject::smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    // Execute run loop for registered objects
    this->RunLoopObject::loop();
    
  }while(millis() - start < ms);
}

void RunLoopObject::setAncestor(RunLoopObject *ancestor)
{
  _ancestor = ancestor;
}