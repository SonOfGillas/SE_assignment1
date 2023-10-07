#include "game_phase.h"
#include <bits/stdc++.h>

GAME_SUBPHASE currentGameSubPhase = show_sequence;
STATUS gameSubPhaseStatus = ok;
bool gameOver = false;
long gameStartingTime;
int sequence[NUM_GREEN_LEDS];

int T1 = 2000; //pause between match
int T2 = 1000; //pause between one led of the sequence turn off
int T3 = 5000; //response time

namespace game_phase {
  static void init() {
    currentGameSubPhase = show_sequence;
    gameStartingTime=millis();
  }

  void shuffle_array(int arr[], int n)
    {
        unsigned seed = gameStartingTime;

        // Shuffling our array
        shuffle(arr, arr + n,
                default_random_engine(seed));
  
    }

  static STATUS showSequence() {
    for(int led : leds)
      digitalWrite(led, HIGH);
    
    delay(T1);

    // copy leds into sequence
    for(int i=0;i<NUM_GREEN_LEDS;i++){
      sequence[i] = leds[i];
    }

    // shuffle sequence
    int n = sizeof(sequence) / sizeof(sequence[0]);
    shuffle_array(sequence, n);

    //better shuffle ?
    random_shuffle(std::begin(a), std::end(a));
    

    return ok;
  }

  static STATUS replicateSequence() {
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

  void checkGameSubPhaseSwitch(){
    if(gameSubPhaseStatus == go_next_phase){
      if(currentGameSubPhase == end_round){
        currentGameSubPhase = show_sequence;
      } else {
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


