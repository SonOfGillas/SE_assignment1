// phases: 
// - game phase:
//   - led sequence
//   - button sequence
//   - end round phase
// - waiting for game
// - sleep fase

enum PHASE {
  waiting_phase,
  game_phase,
  sleep_phase
};

PHASE currentPhase = waiting_phase;

void setup() { 
  Serial.begin(115200);
}

void loop() {
 switch (currentPhase)
 {
 case waiting_phase:
  /* code */
  break;
 case game_phase:
  /* code */
  break;
 case sleep_phase:
  /* code */
  break;
 default:
  //reset
  break;
 }
}
