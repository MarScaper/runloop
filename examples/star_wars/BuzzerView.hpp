/*
 * BuzzerView.hpp
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
#ifndef BuzzerView_hpp
#define BuzzerView_hpp

#include <RunLoop.h>

/*! \class NewTone
 *  NewTone is an external library available at:<br>
 *  https://bitbucket.org/teckel12/arduino-new-tone
 *  <br><br>
 *  Plug-in replacement for Tone. Uses timer 1 which may free 
 *  up conflicts with the tone library.
 *
 *  @ingroup ExternalLib
 *  @ingroup Timer
 */
#include <NewTone.h>

#define SilentNote      0.00 // Hz

// English notes
#define CNote         261.63 // Hz
#define CSharpNote    277.18 // Hz
#define DNote         293.66 // Hz
#define DSharpNote    311.13 // Hz
#define ENote         329.63 // Hz
#define FNote         349.23 // Hz
#define FSharpNote    369.99 // Hz
#define GNote         392.00 // Hz
#define GSharpNote    415.30 // Hz
#define ANote         440.00 // Hz
#define ASharpNote    466.16 // Hz
#define BNote         493.88 // Hz

//
// As you want... ;)
//

// Latin notes
#define DoNote        261.63 // Hz
#define DoSharpNote   277.18 // Hz
#define ReNote        293.66 // Hz
#define ReSharpNote   311.13 // Hz
#define MiNote        329.63 // Hz
#define FaNote        349.23 // Hz
#define FaSharpNote   369.99 // Hz
#define SolNote       392.00 // Hz
#define SolSharpNote  415.30 // Hz
#define LaNote        440.00 // Hz
#define LaSharpNote   466.16 // Hz
#define SiNote        493.88 // Hz

// Comment / Uncomment defines to choose the intro you want... ;)
//#define BUZZER_INTRO_NONE
//#define BUZZER_INTRO_STAR_TREK
#define BUZZER_INTRO_STAR_WARS

/*! This structure defines a musical note. */
struct MuscicalNote
{
  unsigned short frequency;
  float beat;
};

enum BuzzerViewSound 
{
  BuzzerViewNoSound,
  BuzzerViewPlaySound
};

/*!
 *  This class manage a buzzer.
 *
 *  @ingroup View
 */
class BuzzerView : public RunLoopObject
{
  
public:
  
#pragma mark -
#pragma mark Create and destroy
  
  BuzzerView(int buzzerPin);
  ~BuzzerView();
  
  void startIntroMelody();
  void startWarning();
  void stop();
  
private:
  
  int _buzzerPin;
  
  BuzzerViewSound _buzzerSound;
  
  MuscicalNote *_currentMusic         = NULL;
  unsigned int _currentMusicNoteCount = 0;
  unsigned int _currentMusicBPM       = 0;
  bool         _autoReplay            = false;
  
  unsigned int _currentNoteIndex = 0;
  long         _currentNoteStart = 0;
  unsigned int _currentNoteDelay = 0;
  
  unsigned int playNote(float note, float beat, unsigned int bpm);
  
  bool nextNote();
  
  /*! Overwrite virtual method of RunLoopObject. */
  void loop();
};

#endif
