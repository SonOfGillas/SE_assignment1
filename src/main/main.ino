// phases: 
// - game:
//   - led sequence
//   - button_ sequence
//   - end round 
// - waiting for game:
//   - fade led
//   - sleep

#include "model.h"
#include "waiting_phase.h"
//#include "game_phase/game_phase.h"

// led pin
#define LED_RED 10
#define LED_GREEN_1 12
#define lED_GREEN_2 11
#define lED_GREEN_3 9
#define lED_GREEN_4 8

// button_ pin
#define BUTTON_1 7
#define BUTTON_2 6
#define BUTTON_3 5
#define BUTTON_4 4

// potenziometer
#define POT A0

PHASE currentPhase = waiting;
bool isPhaseChanged = false;
STATUS phaseStatus = ok;
int leds[] = {LED_GREEN_1,lED_GREEN_2,lED_GREEN_3,lED_GREEN_4};

void setup() {
  // led initialization
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN_1, OUTPUT);
  pinMode(lED_GREEN_2, OUTPUT);
  pinMode(lED_GREEN_3, OUTPUT);
  pinMode(lED_GREEN_4, OUTPUT);
  // button initializzation
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(BUTTON_4, INPUT_PULLUP);
  //pot
  pinMode(POT,INPUT);

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
    //phaseStatus = game_phase::phase(isPhaseChanged);
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
