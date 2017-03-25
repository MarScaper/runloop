/*
 * BuzzerView.cpp
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

#include "BuzzerView.hpp"

#ifndef BUZZER_INTRO_NONE
#ifdef BUZZER_INTRO_STAR_TREK
unsigned int bpmStarTrekIntro = 200;
MuscicalNote starTrekIntro[] = 
{
  {FNote,       2    },
  {DSharpNote,  2    },
  
  {SilentNote,  1    },
  {DSharpNote,  1    },
  
  {CSharpNote,  0.67 },
  {ASharpNote,  0.67 },
  {ANote,       0.67 },
  
  {GSharpNote,  3    }
};
#endif

#ifdef BUZZER_INTRO_STAR_WARS
unsigned int bpmStarWars     = 120;
MuscicalNote StarWarsNotes[] = 
{
  {ANote,       1    },
  {SilentNote,  0.1  },
  {ANote,       1    },
  {SilentNote,  0.1  },
  {ANote,       1    },
  {SilentNote,  0.1  },
  
  {FNote,       0.7  },
  {SilentNote,  0.1  },
  {CSharpNote,  0.3  },
  {SilentNote,  0.1  },
  {ANote,       1    },
  {SilentNote,  0.1  },
  
  {FNote,       0.7  },
  {SilentNote,  0.1  },
  {CSharpNote,  0.3  },
  {SilentNote,  0.1  },
  {ANote,       1.3  },
  {SilentNote,  0.1  }
};
#endif
#endif

unsigned int bpmWarning      = 120;
MuscicalNote warningNotes[] = 
{
  {ANote,       1    },
  {SilentNote,  1    }
};

BuzzerView::BuzzerView(int buzzerPin)
{
  _buzzerPin = buzzerPin;
  
  // Go to sleep...
  this->setIdle(true);
}

BuzzerView::~BuzzerView()
{
}

unsigned int BuzzerView::playNote(float note, float beat, unsigned int bpm)
{
  long noteDelay = beat*60000/bpm;
  
  if( note )
  {
    NewTone(_buzzerPin, note, noteDelay);
  }
  else 
  {
    noNewTone(_buzzerPin);
  }
  
  return noteDelay;
}

void BuzzerView::startIntroMelody()
{
  _currentNoteIndex      = 0;
  
#ifndef BUZZER_INTRO_NONE
#ifdef BUZZER_INTRO_STAR_TREK
  _buzzerSound           = BuzzerViewPlaySound;
  _currentMusic          = starTrekIntro;
  _currentMusicNoteCount = sizeof(starTrekIntro)/sizeof(MuscicalNote);
  _currentMusicBPM       = bpmStarTrekIntro;
  
  _autoReplay            = false;

  // Wake up
  this->setIdle(false);
#endif

#ifdef BUZZER_INTRO_STAR_WARS
  _buzzerSound           = BuzzerViewPlaySound;
  _currentMusic          = StarWarsNotes;
  _currentMusicNoteCount = sizeof(StarWarsNotes)/sizeof(MuscicalNote);
  _currentMusicBPM       = bpmStarWars;
  
  _autoReplay            = false;

  // Wake up
  this->setIdle(false);
#endif
#endif
  
}

void BuzzerView::startWarning()
{
  _currentNoteIndex      = 0;
  _buzzerSound           = BuzzerViewPlaySound;
  _currentMusic          = warningNotes;
  _currentMusicNoteCount = sizeof(warningNotes)/sizeof(MuscicalNote);
  _currentMusicBPM       = bpmWarning;
  _autoReplay            = true;
  
  // Wake up
  this->setIdle(false);
}

bool BuzzerView::nextNote()
{
  // Is there another note to play?
  if( _currentNoteIndex < _currentMusicNoteCount )
  {
    // Play note
    MuscicalNote note = _currentMusic[_currentNoteIndex];
    _currentNoteStart = millis();
    _currentNoteDelay = playNote(note.frequency, note.beat, _currentMusicBPM);    
    _currentNoteIndex++;
    
    return true;
  }
  
  return false;
}

void BuzzerView::stop()
{
  _buzzerSound = BuzzerViewNoSound;
  
  _currentMusic          = NULL;
  _currentMusicNoteCount = 0;
  _currentMusicBPM       = 0;
  
  _currentNoteIndex = 0;
  _currentNoteStart = 0;
  _currentNoteDelay = 0;
  
  // Go to sleep...
  this->setIdle(true);
}

void BuzzerView::loop()
{
  if( _buzzerSound == _buzzerSound )
  {
    // Is current note finished?
    if( (millis()-_currentNoteStart) >= _currentNoteDelay )
    {
      // Another note to play?
      if( !nextNote() )
      {
        if( _autoReplay == false )
        {
          // Stop melody
          this->stop();
        }
        else 
        {
          // Restart melody
          _currentNoteIndex = 0;
          _currentNoteDelay = 0;
        }
      }
    }
  }
}
