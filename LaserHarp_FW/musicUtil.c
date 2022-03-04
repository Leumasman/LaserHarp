#include "musicUtil.h"

void MusicUtil_INIT()
{
    MusicUtil_calcMSecInMeter();
}

void MusicUtil_SetBPM(uint8_t bpm)
{
    mMusicUtil_BPM = bpm; 
}

void MusicUtil_SetMeasDiv(uint8_t bpMeas)
{
    mMusicUtil_BPMeasure = bpMeas; 
}

void MusicUtil_MetronomeTest(SoftwareSerial &midiCtrl)
{
    uint8_t bingNote = 45;
    uint8_t bongNote = 33; 

    for(uint8_t i = 0; i < 10; i++)
    {
        MusicUtil_PlayNoteInBeat(bingNote, 100); 
        MusicUtil_PlayNoteInBeat(bongNote, 100);
        MusicUtil_PlayNoteInBeat(bongNote, 100);
        MusicUtil_PlayNoteInBeat(bongNote, 100);
    }
}

/*
    PlayNote()

    This function executes the on and off of a given note over
    stuff. 
*/
void MusicUtil_PlayNoteInBeat(SoftwareSerial &midiCtrl, uint8_t note, uint16_t noteLenMSec)
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
    portOne.write(MIDI_NOTE_OFF_VOLUME);

    // Wait until the beat is done
    while(millis() < (noteStartMSec + mMusicUtil_MSecPerBeat))
    {
        // wait()
    }
}

void MusicUtil_PlayMajArpeg(uint8_t startingNote)
{

}

void MusicUtil_PlayMinArpeg(uint8_t startingNote)
{

}

void MusicUtil_calcMSecInMeter()
{
    float secPerBeat = SECONDS_PER_MINUTE / mMusicUtil_BPM; 
    mMusicUtil_MSecPerBeat = secPerBeat * 1000; 
    mMusicUtil_MSecPerMeasure = mMusicUtil_MSecPerBeat * mMusicUtil_BPMeasure;
} 
