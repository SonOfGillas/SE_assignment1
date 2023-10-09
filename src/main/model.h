#ifndef _MODEL_
#define _MODEL_

// led pin
#define LED_RED 11
#define NUM_GREEN_LEDS 4
#define LED_GREEN_1 8
#define LED_GREEN_2 9
#define LED_GREEN_3 10
#define LED_GREEN_4 12

// button_ pin
#define NUM_BUTTONS NUM_GREEN_LEDS
#define BUTTON_1 2
#define BUTTON_2 3
#define BUTTON_3 4
#define BUTTON_4 5

// potentiometer
#define POT A0

const int leds[NUM_GREEN_LEDS] = {LED_GREEN_1, LED_GREEN_2, LED_GREEN_3, LED_GREEN_4};
const int buttons[NUM_BUTTONS] = {BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4};

const int T1 = 2000; // pause between match
const int T2 = 1000; // pause between one led of the sequence turn off
const int T3 = 5000; // response time

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

// this value represent the percentage decreasing of the times: T1, T2, T3
enum DIFFICULTY {
  easy = 5,
  medium = 10,
  hard = 15,
  extreme = 20
};

extern DIFFICULTY difficulty;

#endif
