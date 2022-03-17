/*
 MIDI note player
 
 ***********************************************************************
 **                                                                   **
 **  Teensy Note:                                                     **
 **                                                                   **
 **  This will NOT work on Teensy, because "Serial" talks to the      **
 **  USB virtual serial port if Serial mode is used, or an emulated   **
 **  virtual serial to the Arduino Serial Monitor in non-serial       **
 **  modes.  You can use Teensy's real serial port this way:          **
 **  http://www.pjrc.com/teensy/td_uart.html                          **
 **                                                                   **
 **  The MIDI library offers an easier way to use MIDI                **
 **  http://www.pjrc.com/teensy/td_libs_MIDI.html                     **
 **                                                                   **
 **  Teensy also has USB MIDI, for native MIDI to your computer       **
 **  http://www.pjrc.com/teensy/td_midi.html                          **
 **                                                                   **
 **  You can use both USB MIDI and the MIDI library on Teensy!  :)    **
 **                                                                   **
 ***********************************************************************


 This sketch shows how to use the serial transmit pin (pin 1) to send MIDI note data.
 If this circuit is connected to a MIDI synth, it will play 
 the notes F#-0 (0x1E) to F#-5 (0x5A) in sequence.

 
 The circuit:
 * digital in 1 connected to MIDI jack pin 5
 * MIDI jack pin 2 connected to ground
 * MIDI jack pin 4 connected to +5V through 220-ohm resistor
 Attach a MIDI cable to the jack, then to a MIDI synth, and play music.

 created 13 Jun 2006
 modified 30 Aug 2011
 by Tom Igoe 

 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/MIDI
 
 */
 
#include <SoftwareSerial.h>
//#include "musicUtil.h"

#define SECONDS_PER_MINUTE      60
#define MIDI_NOTE_COMMAND       0x90
#define MIDI_NOTE_ON_VOLUME     0x45
#define MIDI_NOTE_OFF_VOLUME    0x00

uint8_t mMusicUtil_BPM = 60; 
uint8_t mMusicUtil_BPMeasure = 4;
uint16_t mMusicUtil_MSecPerBeat = 0;  
uint16_t mMusicUtil_MSecPerMeasure = 0;  

// Public Functions
void MusicUtil_INIT();
void MusicUtil_SetBPM(uint8_t bpm); 
void MusicUtil_SetMeasDiv(uint8_t measDiv);

void MusicUtil_PlayNoteInBeat(uint8_t note, uint16_t noteLenMSec);
void MusicUtil_PlayMajArpeg(uint8_t rootNote);
void MusicUtil_PlayMinArpeg(uint8_t rootNote);

void MusicUtil_MetronomeTest();


// Private Functions
void MusicUtil_calcMSecInMeasure(); 

SoftwareSerial portOne(PB7, PB6);

void setup() {
  //  Set MIDI baud rate:
  portOne.begin(31250);
  MusicUtil_INIT(); 
  //MusicUtil_MetronomeTest();
  delay(500);
}

// Arpegio (pattern to play when one beam is interupted)
void loop() {
  // play notes from F#-0 (0x1E) to F#-5 (0x5A):
    for(uint8_t i = 0; i < 2; i++)
    {
        MusicUtil_PlayMinArpeg(67); // Gmin
    }

    for(uint8_t i = 0; i < 2; i++)
    {
        MusicUtil_PlayMinArpeg(65); // Fmin
    }

    for(uint8_t i = 0; i < 2; i++)
    {
        MusicUtil_PlayMinArpeg(63); // D#min
    }

    for(uint8_t i = 0; i < 2; i++)
    {
        MusicUtil_PlayMinArpeg(60); // Cmin
    }
}

//  plays a MIDI note.  Doesn't check to see that
//  cmd is greater than 127, or that data values are  less than 127:
void noteOn(int cmd, int pitch, int velocity) {
  portOne.write(cmd);
  portOne.write(pitch);
  portOne.write(velocity);
}

// Establishes a metronome pattern (ex: BIP boop boop boop)
void MusicUtil_INIT()
{
    MusicUtil_calcMSecInMeasure();
}

// bpm(speed) = beats per minute
void MusicUtil_SetBPM(uint8_t bpm)
{
    mMusicUtil_BPM = bpm; 
}

//defines the amount of time in a measure
void MusicUtil_SetMeasDiv(uint8_t bpMeas)
{
    mMusicUtil_BPMeasure = bpMeas; 
}

//Sets up the metronome function
void MusicUtil_MetronomeTest()
{
    uint8_t bingNote = 0x40;
    uint8_t bongNote = 0x39; 

    for(uint8_t i = 0; i < 100; i++)
    {
        MusicUtil_PlayNoteInBeat(bingNote, 250); 
        MusicUtil_PlayNoteInBeat(bongNote, 250);
        MusicUtil_PlayNoteInBeat(bongNote, 250);
        MusicUtil_PlayNoteInBeat(bongNote, 250);
    }
}

/*
    PlayNote()

    This function executes the on and off of a given note over
    stuff. 
*/
void MusicUtil_PlayNoteInBeat(uint8_t note, uint16_t noteLenMSec)
{
    uint32_t noteOffDelayMSec = (noteLenMSec > mMusicUtil_MSecPerBeat) ? mMusicUtil_MSecPerBeat : noteLenMSec; 
    
    uint32_t noteStartMSec = millis();
    // Turn the Note ON
    portOne.write(MIDI_NOTE_COMMAND);
    portOne.write(note);
    portOne.write(MIDI_NOTE_ON_VOLUME);

    // Wait until it is time to turn the note off
    while(millis() < (noteStartMSec + noteOffDelayMSec))
    {
        // wait
        delay(3);
    }

    // Turn the note OFF
    portOne.write(MIDI_NOTE_COMMAND);
    portOne.write(note);
    portOne.write((uint8_t)MIDI_NOTE_OFF_VOLUME);

    // Wait until the beat is done
    while(millis() < (noteStartMSec + mMusicUtil_MSecPerBeat))
    {
        // wait()
    }
}

#define MIN_THIRD(c)    c + 3
#define MAJ_THIRD(c)    c + 4
#define FIFTH(c)        c + 7
#define OCTAVE(c)       c + 12

void MusicUtil_PlayMajArpeg(uint8_t rootNote)
{
    MusicUtil_PlayNoteInBeat(rootNote, 250); 
    MusicUtil_PlayNoteInBeat(MAJ_THIRD(rootNote), 250);
    MusicUtil_PlayNoteInBeat(FIFTH(rootNote), 250);
    MusicUtil_PlayNoteInBeat(OCTAVE(rootNote), 250);
}

void MusicUtil_PlayMinArpeg(uint8_t rootNote)
{
    MusicUtil_PlayNoteInBeat(rootNote, 250); 
    MusicUtil_PlayNoteInBeat(MIN_THIRD(rootNote), 250);
    MusicUtil_PlayNoteInBeat(FIFTH(rootNote), 250);
    MusicUtil_PlayNoteInBeat(OCTAVE(rootNote), 250);
}

void MusicUtil_calcMSecInMeasure()
{
    float secPerBeat = SECONDS_PER_MINUTE / mMusicUtil_BPM; 
    mMusicUtil_MSecPerBeat = secPerBeat * 1000; 
    mMusicUtil_MSecPerMeasure = mMusicUtil_MSecPerBeat * mMusicUtil_BPMeasure;
} 
