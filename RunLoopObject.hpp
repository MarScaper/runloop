/*
 * RunLoopObject.hpp
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
#ifndef RunLoopObject_hpp
#define RunLoopObject_hpp

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "Arduino.h"
#endif

/*!
 * The class manages a run loop with a hierachy of RunLoopObject instances.
 * It's a very convenient way to get asynchronous management easily.
 *
 *  @ingroup Model
 */
class RunLoopObject
{
  
public:
  
#pragma mark -
#pragma mark Create and destroy
  
  RunLoopObject();
  ~RunLoopObject();
  
#pragma mark -
#pragma mark Virtual method for overwrite.
  
  /*! This virtual method is the run loop and should be overwrite by subclass. */
  virtual void loop();
  
  /*! This virtual method allow to start or stop the loop. */
  virtual void setIdle(bool state);
  
#pragma mark -
#pragma mark Run loop management
  
  /*! Return the loop state. */
  inline bool isIdle() {return _isIdle;};
  
  /*! Add a run loop object to the run loop. */
  bool addToRunLoop(RunLoopObject *object);
  
  /*! Remove object from run loop and release It if deleteObject is true. */
  bool removeFromRunLoop(RunLoopObject *object, bool deleteObject);
  
  /*! Remove object from run loop without release. */
  bool removeFromRunLoop(RunLoopObject *object);
  
  /*! Smart way to pause main loop while sub run loop objects keep up to date. */
  void smartDelay(unsigned long ms);
  
  /*! Return ancestor if available. */
  inline RunLoopObject* ancestor() {return _ancestor;};
  
protected:
  
  /*! Idle state. By default an object always start automatically. */
  bool _isIdle = false;

  /*! Go back in the hierarchy of ancestors to check that none is idle. */
  bool areAncestorsIdle();
  
  /*! RunLoopObject childs count. */
  unsigned short _runLoopObjectCount = 0;
  
  /*! RunLoopObject childs array. */
  RunLoopObject* *_runLoopObjectArray = NULL;
  
private:
  
  /*! Hierarchical ancestor. */
  RunLoopObject *_ancestor = NULL;
  
  /*! Set the ancestor. This method is autmatically called internally by addToRunLoop(...). */
  void setAncestor(RunLoopObject *ancestor);
};

#endif
