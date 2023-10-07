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

// led pin
#define ledRed 10
#define ledGreen1 12
#define ledGreen2 11
#define ledGreen3 9
#define ledGreen4 8

// button pin
#define button1 7
#define button2 6
#define button3 5
#define button4 4

// potenziometer
#define pot A0

PHASE currentPhase = waiting;
bool isPhaseChanged = false;
STATUS phaseStatus = ok;
int leds = [ledGreen1,ledGreen2,ledGreen3,ledGreen4];

void setup() {
  // led initialization
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen1, OUTPUT);
  pinMode(ledGreen2, OUTPUT);
  pinMode(ledGreen3, OUTPUT);
  pinMode(ledGreen4, OUTPUT);
  // button initializzation
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  //pot
  pinMode(pot,INPUT)

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
