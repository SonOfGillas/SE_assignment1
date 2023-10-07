#ifndef __WAITING_PHASE__
#define __WAITING_PHASE__

#include "model.h"

extern const int leds[];

namespace waiting_phase {
  /* public */
  STATUS phase(bool isPhaseChanged);
}

#endif
