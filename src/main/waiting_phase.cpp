#include "pins_arduino.h"
#include "HardwareSerial.h"
#include "Arduino.h"
#include "waiting_phase.h"
#include <TimerOne.h>
#include <avr/sleep.h>
#include <EnableInterrupt.h>

namespace waiting_phase {

  const uint8_t INTN = digitalPinToInterrupt(buttons[0]);

  unsigned short value, out = 0;
  short inc = 3;
  volatile bool exit = false;
  volatile bool toSleep = false;

  static void wakeUp(){
    for(int button: buttons){
      disableInterrupt(digitalPinToInterrupt(button));
    }
    init();
  }

  static void next_phase() {
    exit = true;

    // disable B1 interrupt
    disableInterrupt(INTN);

    // disable Timer1 interrupt
    Timer1.detachInterrupt();
  }

  static void sleep() {
    for(int button: buttons){
      enableInterrupt(digitalPinToInterrupt(button), wakeUp, FALLING);
    }
    digitalWrite(LED_RED, LOW); // shut down red led to save power
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_mode();
    next_phase();
  }

  static void enableSleep() {
    toSleep = true;
  }

  static void init() {
    // turn off green leds
    for(int led: leds) {
      digitalWrite(led, LOW);
    }

    // turn off red led
    digitalWrite(LED_RED, LOW);

    // init 10s timer
    Timer1.initialize(10000000);  // lengh in microseconds
    Timer1.attachInterrupt(enableSleep);

    // enable B1 interrupt
    enableInterrupt(INTN, next_phase, FALLING);

    // print to serial line
    Serial.println("Welcome to the Restore the Light Game. Press Key B1 to Start");
  }

  /* public */
  STATUS phase(const bool isPhaseChanged) {
    if(isPhaseChanged){
      init();
    }

    // linear pulsing PWM
    analogWrite(LED_RED, out);
    value += inc;
    out = pow(255, value/100.0);
    if (value + inc >= 100 || value + inc <= 0) inc = -inc;

    delay(100);

    if(toSleep) sleep();

    if(exit) {
      // update difficulty
      unsigned int pot = analogRead(POT);
      if(pot <= 256) {
        difficulty = easy;
      } else if(pot <= 512) {
        difficulty = medium;
      } else if(pot <= 768) {
        difficulty = hard;
      } else { // <= 1024
        difficulty = extreme;
      }
      return go_next_phase;
    } else {
      return ok;
    }
  }
}
