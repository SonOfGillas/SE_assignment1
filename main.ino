// phases: 
// - game:
//   - led sequence
//   - button sequence
//   - end round 
// - waiting for game:
//   - fade led
//   - sleep

#include "model.h"

PHASE currentPhase = waiting_phase;
bool isPhaseChanged = false;

void setup() { 
  Serial.begin(115200);
}

void loop() {
 switch (currentPhase)
 {
 case waiting_phase:
  waiting_phase::phase(isPhaseChanged);
  break;
 case game_phase:
  /* code */
  break;
 default:
  //reset
  break;
 }
}
