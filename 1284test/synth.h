#ifndef SYNTH_H
#define SYNTH_H

#include <stdint.h>
#include "ym2612.h"
#include "midi.h"


#define MIDI_CHANNEL 0

// Channel selection codes for the key on/off register
#define KEY_ON_CH_1 B000
#define KEY_ON_CH_2 B001
#define KEY_ON_CH_3 B010
#define KEY_ON_CH_4 B100
#define KEY_ON_CH_5 B101
#define KEY_ON_CH_6 B110

// Operator selectrion codes for the key on/off register. To select multiple operators, OR these values together
#define OP_1_SEL B0001
#define OP_2_SEL B0010
#define OP_3_SEL B0100
#define OP_4_SEL B1000
#define OP_ALL_SEL B1111
#define OP_NONE_SEL B0000

#define NUM_YM2612S 1
#define NOTES_PER_YM 6

#define MAX_NOTES_ON NUM_YM2612S*NOTES_PER_YM
#define NUM_CHANNELS MAX_NOTES_ON
#define OPERATORS_PER_CHANNEL 4

class Synth {
	private:
		// Represents the current notes that are "on". A "0" represents the absence of a note. Each index corresponds to a particular channel.
		uint8_t notesOn[MAX_NOTES_ON];
		uint16_t noteToFreqVal(Note note);
		bool checkChannel(uint8_t midiByte);
		uint8_t channelToKeyOnCode(uint8_t channel);
		uint8_t midiChannel;
		midiMessage midiData;

		// Synthesizer parameters. We need to remember some parameters here, because certain registers store several parameters,
		// and in order to change one, we have to re-write the other parameters along with the one we're trying to change.
		uint8_t lfoFreq; 	// This is not an actual "frequency", but a register value
		bool lfoEnable;
		uint16_t timerAFreq;
		uint8_t timerBFreq;
		uint8_t vals_DT1[NUM_CHANNELS][OPERATORS_PER_CHANNEL];
		uint8_t vals_MUL[NUM_CHANNELS][OPERATORS_PER_CHANNEL];
		uint8_t vals_TL[NUM_CHANNELS][OPERATORS_PER_CHANNEL];
		uint8_t vals_RS[NUM_CHANNELS][OPERATORS_PER_CHANNEL];
		uint8_t vals_AR[NUM_CHANNELS][OPERATORS_PER_CHANNEL];
		bool vals_AM[NUM_CHANNELS][OPERATORS_PER_CHANNEL];
		uint8_t vals_D1R[NUM_CHANNELS][OPERATORS_PER_CHANNEL];
		uint8_t vals_D2R[NUM_CHANNELS][OPERATORS_PER_CHANNEL];
		uint8_t vals_D1L[NUM_CHANNELS][OPERATORS_PER_CHANNEL];
		uint8_t vals_RR[NUM_CHANNELS][OPERATORS_PER_CHANNEL];
		uint8_t vals_SSG_EG[NUM_CHANNELS][OPERATORS_PER_CHANNEL];
		uint8_t vals_BLOCK[NUM_CHANNELS];
		uint16_t vals_FREQ[NUM_CHANNELS];
		uint8_t vals_FDBCK[NUM_CHANNELS];
		uint8_t vals_ALG[NUM_CHANNELS];
		bool vals_L_OUT[NUM_CHANNELS];
		bool vals_R_OUT[NUM_CHANNELS];
		uint8_t vals_AMS[NUM_CHANNELS];
		uint8_t vals_FMS[NUM_CHANNELS];

	public:
		Synth();
		int turnMidiNoteOn(uint8_t note, uint8_t vel);
		int turnMidiNoteOff(uint8_t note);
		int processMidi();
		int addMidiByte(uint8_t byte);

		// Public methods for modiyfing parameters. We normally want all voices to have the same parameters, but not always. For those
		// parameters which are on a channel-to-channel basis, we have a channel select argument.

		// Global LFO parameters
		int enableLFO();
		int disableLFO();
		int setLFOFreq(uint8_t freq);

		// Timer parameters
		int setTimerA(uint16_t val);
		int setTimerB(uint8_t val);

		// Register 27H goes here

		// Set operators on or off for a particular channel
		int setOperatorsOnOff(uint8_t operators, uint8_t channel);

		// Turn on or off a note for a given channel
		int setKeyOn(uint8_t channel);
		int setKeyOff(uint8_t channel);

		// Enables or disables the channel 6 DAC. This DAC should typically be disabled.
		int enableDAC();
		int disableDAC();

		// Sets DT1 of a particular operator on a given channel
		int setDetune(uint8_t val, uint8_t op, uint8_t channel);

		// Sets DT1 of a particular operator on all channels
		int setDetuneAll(uint8_t val, uint8_t op);

		// Sets MUL of a particular operator on a given channel
		int setMultiple(uint8_t val, uint8_t op, uint8_t channel);

		// Sets MUL of a particular operator on all channels
		int setMultipleAll(uint8_t val, uint8_t op);

		// Sets TL of a particular operator on a given channel
		int setTotalLevel(uint8_t val, uint8_t op, uint8_t channel);

		// Sets TL of a particular operator on all channels
		int setTotalLevelAll(uint8_t val, uint8_t op);

		// Sets RS of a particular operator on a given channel
		int setRateScaling(uint8_t val, uint8_t op, uint8_t channel);

		// Sets RS of a particular operator on all channels
		int setRateScalingAll(uint8_t val, uint8_t op);

		// Sets AR of a particular operator on a given channel
		int setAttackRate(uint8_t val, uint8_t op, uint8_t channel);

		// Sets AR of a particular operator on all channels
		int setAttackRateAll(uint8_t val, uint8_t op);

		// Enables AM of a particular operator on a given channel
		int enableAmpMod(uint8_t op, uint8_t channel);

		// Disables AM of a particular operator on a given channel
		int disableAmpMod(uint8_t op, uint8_t channel);

		// Enables AM of a particular operator on all channels
		int enableAmpModAll(uint8_t op);

		// Disables AM of a particular operator on all channels
		int disableAmpModAll(uint8_t op);

		// Sets D1R of a particular operator on a given channel
		int setDecayRate1(uint8_t val, uint8_t op, uint8_t channel);

		// Sets D1R of a particular operator on all channels
		int setDecayRate1All(uint8_t val, uint8_t op);

		// Sets D2R of a particular operator on a given channel
		int setDecayRate2(uint8_t val, uint8_t op, uint8_t channel);

		// Sets D2R of a particular operator on all channels
		int setDecayRate2All(uint8_t val, uint8_t op);

		// Sets D1L of a particular operator on a given channel
		int setAmp2(uint8_t val, uint8_t op, uint8_t channel);

		// Sets D1L of a particular operator on all channels
		int setAmp2All(uint8_t val, uint8_t op);

		// Sets RR of a particular operator on a given channel
		int setReleaseRate(uint8_t val, uint8_t op, uint8_t channel);

		// Sets RR of a particular operator on all channels
		int setReleaseRateAll(uint8_t val, uint8_t op);

		// Set SSG-EG of a particular operator on a given channel
		int setSSGEG(uint8_t val, uint8_t op, uint8_t channel);

		// Sets SSG-EG of a particular operator on all channels
		int setSSGEGAll(uint8_t val, uint8_t op);

		// Sets the frequency and block number of a given channel
		int setFrequency(uint8_t block, uint16_t frequency, uint8_t channel);

		// Sets the feedback of a given channel
		int setFeedback(uint8_t val, uint8_t channel);

		// Sets the feedback of all channels
		int setFeedbackAll(uint8_t val);

		// Sets the algorithm of a given channel
		int setAlgorithm(uint8_t val, uint8_t channel);

		// Sets the algorithm of all channels
		int setAlgorithmAll(uint8_t val);

		// Enables left output for a given channel
		int enableLeft(uint8_t channel);

		// Disables left output for a given channel
		int disableLeft(uint8_t channel);

		// Enables right output for a given channel
		int enableRight(uint8_t channel);

		// Disables right output for a given channel
		int disableRight(uint8_t channel);

		// Enables left output for all channels
		int enableLeftAll();

		// Disables left output for all channels
		int disableLeftAll();

		// Enables right output for all channels
		int enableRightAll();

		// Disables right output for all channels
		int disableRightAll();

		// Sets AMS for a given channel
		int setAmpModSens(uint8_t val, uint8_t channel);

		// Sets FMS for a given channel
		int setFreqModSens(uint8_t val, uint8_t channel);

		// Sets AMS for all channels
		int setAmpModSensAll(uint8_t val);

		// Sets FMS for all channels
		int setFreqModSensAll(uint8_t val);
};


#endif /* SYNTH_H */