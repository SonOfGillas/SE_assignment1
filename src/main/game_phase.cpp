#include "game_phase.h"

GAME_SUBPHASE currentGameSubPhase = show_sequence;
STATUS gameSubPhaseStatus = ok;
bool isGameSubPhaseChanged = false;
bool gameOver = false;
namespace game_phase {
  static void init() {
    currentGameSubPhase = show_sequence;
  }

  static STATUS showSequence() {
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
      isGameSubPhaseChanged = true;
    } else {
      isGameSubPhaseChanged = false;
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


