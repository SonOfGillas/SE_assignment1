// phases: 
// - game phase:
//   - led sequence
//   - button sequence
//   - end round phase
// - waiting for game
// - sleep fase

enum PHASE {
  waiting_for_game,
  game_phase,
  sleep_phase
};

PHASE currentPhase = waiting_for_game;

void setup() { 
  Serial.begin(115200);
}

void loop() {
 switch (currentPhase)
 {
 case waiting_for_game:
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
