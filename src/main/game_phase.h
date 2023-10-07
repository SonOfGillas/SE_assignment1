#ifndef __GAME_PHASE__
#define __GAME_PHASE__

#include "model.h"

extern const int leds[];

namespace game_phase {
  /* public */
  STATUS phase(bool isPhaseChanged);
}

#endif