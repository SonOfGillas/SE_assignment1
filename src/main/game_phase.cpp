#include "game_phase.h"
#include "Arduino.h"
#include <stdlib.h>  

#define NO_RESPONSE -1
#define BUTTON_PRESS_DELAY 500 // after this time the button can be pressed again

GAME_SUBPHASE currentGameSubPhase = show_sequence;
STATUS gameSubPhaseStatus = ok;
int score = 0;
bool gameOver = false;
long replicateSequenceStartingTime;
int sequence[NUM_GREEN_LEDS];
int responce[NUM_GREEN_LEDS];
int responceIndex = 0;
long lastTimeTheButtonsWerePressed[NUM_BUTTONS];
long currentTime = 0; 
float gameT2;
float gameT3;

namespace game_phase {
  static void init() {
    Serial.println("Difficulty: -" + String(difficulty)+"% time each round");
    gameOver=false;
    score = 0;
    currentGameSubPhase = show_sequence;

    gameT2 = T2;
    gameT3 = T3;
  
    // copy leds into sequence
    for(int i=0;i<NUM_GREEN_LEDS;i++){
      sequence[i] = leds[i];  
    }

    digitalWrite(LED_RED, LOW);
  }

  static void initReplicateSequence(){
    responceIndex = 0; 
     for(int i=0;i<NUM_BUTTONS;i++){
      responce[i] = NO_RESPONSE; // set responce array
      lastTimeTheButtonsWerePressed[i] = 0; // set variable for check the button bouncing
    }
    replicateSequenceStartingTime = millis(); // the reponce time starts now
    Serial.println("Go!");
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
      delay(gameT2);
      digitalWrite(led, LOW);
    }

    initReplicateSequence();
    return go_next_phase;
  }

  static STATUS replicateSequence() {
    currentTime = millis();
    //check if the responce time is over or if the user has already filled the responce array
    if(currentTime - replicateSequenceStartingTime > gameT3 || responceIndex >= NUM_GREEN_LEDS){
      return go_next_phase;
    }

    //read all buttons
    for(int i=0;i<NUM_BUTTONS;i++){
      if(currentTime - lastTimeTheButtonsWerePressed[i] > BUTTON_PRESS_DELAY){
        //the button are set in pullup mode, so if the button is pressed the value is LOW
        if(digitalRead(buttons[i]) == LOW){
          lastTimeTheButtonsWerePressed[i] = currentTime;
          // check if the user has already filled the responce array
          if(responceIndex < NUM_GREEN_LEDS){
            responce[responceIndex] = leds[i]; // save the button pressed 
            responceIndex++;
          }
        }
      }
    }
    return ok;
  }

  static STATUS endRound() {
    //check if the responce time is over
    currentTime = millis();
    if(currentTime - replicateSequenceStartingTime > gameT3){
      gameOver = true;
      return go_next_phase;
    }

    gameOver = false;
    //check if the user has replicated the sequence
    //NOTE: the responce must be in the reverse order
    for(int i=0,k=NUM_GREEN_LEDS-1;i<NUM_GREEN_LEDS && k >= 0;i++,k--){
      if(sequence[i] != responce[k]){
        gameOver = true;
        return go_next_phase;
      }
    }

    score++;
    Serial.println("New point! Score: " + String(score));
    //decrease the times
    gameT2 -= (gameT2 * difficulty) / 100.0;
    gameT3 -= (gameT3 * difficulty) / 100.0;

    return go_next_phase;
  }

  static void runGameSubPhase() {
    switch (currentGameSubPhase) {
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

  static void checkGameSubPhaseSwitch() {
    if(gameSubPhaseStatus == go_next_phase){
      switch(currentGameSubPhase) {
        case end_round:
          currentGameSubPhase = show_sequence;
          break;
        case show_sequence:
          currentGameSubPhase = replicate_sequence;
          break;
        case replicate_sequence:
          currentGameSubPhase = end_round;
          break;
        default:
          break;
      }
    }
  }

  /* public */
  STATUS phase(const bool isPhaseChanged) {
    if(isPhaseChanged) {
      init();
    }
    runGameSubPhase();
    checkGameSubPhaseSwitch();
    if(gameOver){
      Serial.println("Game Over! Final Score: " + String(score));
      digitalWrite(LED_RED, HIGH);
      delay(10000); // wait 10 seconds before restart to initial state
      return go_next_phase;
    }
    return ok;
  }
}


