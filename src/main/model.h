#ifndef _MODEL_
#define _MODEL_  

// led pin
#define LED_RED 10
#define NUM_GREEN_LEDS 4
#define LED_GREEN_1 12
#define LED_GREEN_2 11
#define LED_GREEN_3 9
#define LED_GREEN_4 8

// button_ pin
#define NUM_BUTTONS NUM_GREEN_LEDS
#define BUTTON_1 7
#define BUTTON_2 6
#define BUTTON_3 5
#define BUTTON_4 4

// potentiometer
#define POT A0

const int leds[NUM_GREEN_LEDS] = {LED_GREEN_1, LED_GREEN_2, LED_GREEN_3, LED_GREEN_4};
const int buttons[NUM_BUTTONS] = {BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4};

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