#include "game_phase.h"
#include <stdlib.h>  

#define NO_RESPONSE -1
#define BUTTON_PRESS_DELAY 100 // after this time the button can be pressed again

GAME_SUBPHASE currentGameSubPhase = show_sequence;
STATUS gameSubPhaseStatus = ok;
bool gameOver = false;
long replicateSequenceStartingTime;
int sequence[NUM_GREEN_LEDS];
int responce[NUM_GREEN_LEDS];
int responceIndex = 0;
int lastTimeTheButtonsWerePressed[NUM_GREEN_LEDS]; 

int T1 = 2000; //pause between match
int T2 = 1000; //pause between one led of the sequence turn off
int T3 = 5000; //response time

namespace game_phase {
  static void init() {
    currentGameSubPhase = show_sequence;

    for(int i=0;i<NUM_GREEN_LEDS;i++){
      sequence[i] = leds[i];  // copy leds into sequence
    }
  }

  static STATUS showSequence() {
    for(int led : leds)
      digitalWrite(led, HIGH);
    
    delay(T1);

    //shuffle sequence
    srand (millis()); //seed
    for (int i=0; i < NUM_GREEN_LEDS; i++) {
       int n = rand() % NUM_GREEN_LEDS ;  // Integer from 0 to NUM_GREEN_LEDS-1
       int temp = sequence[n];
       sequence[n] =  sequence[i];
       sequence[i] = temp;
    }
    
    //turn off leds in sequence
    for(int led : sequence){
      digitalWrite(led, LOW);
      delay(T2);
    }

    initReplicateSequence();
    return go_next_phase;
  }

  static void initReplicateSequence(){
    replicateSequenceStartingTime = millis(); // the reponce time starts now
    responceIndex = 0; 
     for(int i=0;i<NUM_GREEN_LEDS;i++){
      responce[i] = NO_RESPONSE; // set responce array
      lastTimeTheButtonsWerePressed[i] = 0; // set variable for check the button bouncing
    }
  }

  static STATUS replicateSequence() {
    long currentTime = millis();
    //check if the responce time is over or if the user has already filled the responce array
    if(currentTime - replicateSequenceStartingTime > T3 || responceIndex >= NUM_GREEN_LEDS){
      return go_next_phase;
    }

    //read all buttons
    for(int i=0;i<NUM_GREEN_LEDS;i++){
      if(currentTime - lastTimeTheButtonsWerePressed[i] > BUTTON_PRESS_DELAY){
        //the button are set in pullup mode, so if the button is pressed the value is LOW
        if(digitalRead(buttons[i]) == LOW){
          lastTimeTheButtonsWerePressed[i] = currentTime;
          // check if the user has already filled the responce array
          if(responceIndex < NUM_GREEN_LEDS){
            responce[responceIndex] = buttons[i]; // save the button pressed 
            responceIndex++;
          }
        }
      }
    }
    return ok;
  }

  static STATUS endRound() {
    //check here if the match is over
    if(true){
      gameOver = true;
    } 
    return go_next_phase;
  }

  static void runGameSubPhase(){
    switch (currentGameSubPhase)
    {
      case show_sequence:
        gameSubPhaseStatus = showSequence();
        break;
      case replicate_sequence:
        gameSubPhaseStatus = replicateSequence();
        break;
      case end_round:
        gameSubPhaseStatus = endRound();
        break;
      default:
        break;
    }
  }

  static void checkGameSubPhaseSwitch(){
    if(gameSubPhaseStatus == go_next_phase){
      if(currentGameSubPhase == end_round){
        currentGameSubPhase = show_sequence;
      } else {
        //increment currentGameSubPhase
        currentGameSubPhase = static_cast<GAME_SUBPHASE>(static_cast<int>(currentGameSubPhase) + 1); 
      }
    }
  }

  /* public */
  STATUS phase(bool isPhaseChanged) {
    if(isPhaseChanged){
      init();
    }
    runGameSubPhase();
    checkGameSubPhaseSwitch();
    return gameOver? go_next_phase : ok;
  }
}


