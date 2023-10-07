#ifndef _MODEL_
#define _MODEL_  

enum PHASE {
  waiting,
  game,
};

enum GAME_SUBPHASE {
  show_sequence,
  replicate_sequence,
  end_round
};


enum STATUS {
  ok,
  go_next_phase,
  err
};

#endif