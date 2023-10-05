#ifndef _MODEL_
#define _MODEL_  

enum PHASE {
  waiting_phase,
  game_phase,
};

enum STATUS {
  ok,
  go_next_phase,
  err
};

#endif