#ifndef MIDI_H
#define MIDI_H

#include "ym2612.h"
#include <stdint.h>

#define NOTES_PER_OCTAVE 12
#define NUM_MIDI_MESSAGES 3
#define MIDI_BAUD 31250

#define MIDI_NOTE_ON 0x9
#define MIDI_NOTE_OFF 0x8
#define MIDI_TIMING 0xF8

class midiMessage {
	private:
		static const Note noteArray[NOTES_PER_OCTAVE];
		uint8_t midiMessages[NUM_MIDI_MESSAGES];
		uint8_t nextIndex;
		bool msgReady;
	public:
		midiMessage();
		bool addByte(uint8_t byte);	
		int getByte(int num);
		bool msgIsReady();

		static uint8_t midiToOctave(uint8_t midiNote);
		static Note midiToNote(uint8_t midiNote);
};

#endif /* MIDI_H */