
#ifndef LAS_HARP_MUSIC_UTIL_H_
#define LAS_HARP_MUSIC_UTIL_H_

#include "Arduino.h"
#include "stdint.h"

#define SECONDS_PER_MINUTE      60
#define MIDI_NOTE_COMMAND       0x90
#define MIDI_NOTE_ON_VOLUME     0x45
#define MIDI_NOTE_OFF_VOLUME    0x00

uint8_t mMusicUtil_BPM = 100; 
uint8_t mMusicUtil_BPMeasure = 4;
uint16_t mMusicUtil_MSecPerBeat = 0;  
uint16_t mMusicUtil_MSecPerMeasure = 0;  

// Public Functions
void MusicUtil_INIT();
void MusicUtil_SetBPM(uint8_t bpm); 
void MusicUtil_SetMeasDiv(uint8_t measDiv);

void MusicUtil_PlayNoteInBeat(SoftwareSerial &midiCtrl, uint8_t note, uint16_t noteLenMSec);
void MusicUtil_PlayMajArpeg(uint8_t startingNote);
void MusicUtil_PlayMinArpeg(uint8_t startingNote);

void MusicUtil_MetronomeTest(SoftwareSerial &midiCtrl);


// Private Functions
void MusicUtil_calcMSecInMeasure(); 

#endif