#include "game_phase.h"

namespace game_phase {
  static void init() {
    //init
  }

  /* public */
  STATUS phase(bool isPhaseChanged) {
    if(isPhaseChanged){
      init();
    }
    return ok;
  }
}