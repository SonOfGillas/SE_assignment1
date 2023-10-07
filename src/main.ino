// phases: 
// - game:
//   - led sequence
//   - button sequence
//   - end round 
// - waiting for game:
//   - fade led
//   - sleep

#include "model.h"
#include "waiting_phase.h"
#include "game_phase.h"

PHASE currentPhase = waiting;
bool isPhaseChanged = false;
STATUS phaseStatus = ok;

void setup() { 
  Serial.begin(115200);
}

void loop() {
  runPhase();
  checkPhaseSwitch();
}

void runPhase(){
  switch (currentPhase)
  {
  case waiting:
    phaseStatus = waiting_phase::phase(isPhaseChanged);
    break;
  case game:
    phaseStatus = game_phase::phase(isPhaseChanged);
    break;
  default:
    phaseStatus = err;
    break;
  }
}

void checkPhaseSwitch(){
  if(phaseStatus = go_next_phase){
    if(currentPhase == waiting){
      currentPhase = game;
    } else {
      currentPhase = waiting;
    }
    isPhaseChanged == true;
  } else {
    isPhaseChanged == false;
  }
}
