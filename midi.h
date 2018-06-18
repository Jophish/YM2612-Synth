#ifndef MIDI_H
#define MIDI_H

#include "ym2612.h"
#include <stdint.h>

#define NOTES_PER_OCTAVE 12
#define NUM_MIDI_MESSAGES 3
#define MIDI_BAUD 31250

#define MIDI_NOTE_OFF 0x80
#define MIDI_NOTE_ON 0x90
#define MIDI_POLY_AFTERTOUCH 0xA0
#define MIDI_CTRL_CHANGE 0xB0
#define MIDI_PROG_CHANGE 0xC0
#define MIDI_CHAN_AFTERTOUCH 0xD0
#define MIDI_PITCH_BEND 0xE0

#define MIDI_SYS_EX 0xF0
#define MIDI_TIME_CODE_QTR_FRAME 0xF1
#define MIDI_SONG_POS_PTR 0xF2
#define MIDI_SONG_SELECT 0xF3
#define MIDI_TUNE_REQUEST 0xF6
#define MIDI_EOX 0xF7
#define MIDI_TIMING 0xF8
#define MIDI_START 0xFA
#define MIDI_CONTINUE 0xFB
#define MIDI_STOP 0xFC
#define MIDI_ACTIVE_SENS 0xFE
#define MIDI_RESET 0xFF

class midiMessage {
	private:
		static const Note noteArray[NOTES_PER_OCTAVE];
		uint8_t midiMessages[NUM_MIDI_MESSAGES];
		uint8_t nextIndex;
		bool msgReady;
		int midiCommandToNumBytes(uint8_t cmd);
		uint8_t numBytes;
	public:
		midiMessage();
		bool addByte(uint8_t byte);	
		int getByte(int num);
		bool msgIsReady();

		static uint8_t midiToOctave(uint8_t midiNote);
		static Note midiToNote(uint8_t midiNote);
};

#endif /* MIDI_H */