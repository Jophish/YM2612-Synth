#include <stdint.h>
#include "synth.h"


Synth *globalSynth;

void setup() {
  globalSynth = new Synth();
  Serial.begin(9600);
}

void loop() {
}

void serialEvent1() {
  while (Serial1.available()) {
    uint8_t midiByte = (uint8_t)Serial1.read();
    globalSynth->addMidiByte(midiByte);
  }
}
