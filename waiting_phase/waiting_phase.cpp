#include "waiting_phase.h"

namespace waiting_phase {

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
