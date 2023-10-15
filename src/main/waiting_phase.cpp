#include "pins_arduino.h"
#include "HardwareSerial.h"
#include "Arduino.h"
#include "waiting_phase.h"
#include <TimerOne.h>
#include <avr/sleep.h>
#include <EnableInterrupt.h>

namespace waiting_phase {

  const uint8_t INTN = buttons[0];

  unsigned short value, out = 0;
  short inc = 5;
  volatile bool exit = false;
  long initilTime = 0;
  long currentTime = 0;
  long waitBeforeSleep = 10000; //10 sec

  static void wakeUp() {
    for(int button: buttons){
      disableInterrupt(button);
    }
  }

  static void next_phase() {
    exit = true;

    // disable B1 interrupt
    disableInterrupt(INTN);

  }

  static void sleep() {
    disableInterrupt(INTN);
    Timer1.detachInterrupt();

    for(int button: buttons){
      enableInterrupt(button, wakeUp, FALLING);
    }
    digitalWrite(LED_RED, LOW); // shut down red led to save power

    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_mode();
  }

  static void init() {
    exit = false;
    initilTime = millis();
    currentTime = millis();
    value = 0;
    if (inc < 0) inc = -inc;
    // turn off green leds
    for(int led: leds) {
      digitalWrite(led, LOW);
    }

    // turn off red led
    digitalWrite(LED_RED, LOW);

    // enable B1 interrupt
    enableInterrupt(INTN, next_phase, FALLING);

    // print to serial line
    Serial.println("Welcome to the Restore the Light Game. Press Key B1 to Start");
    Serial.flush();
  }

  /* public */
  STATUS phase(const bool isPhaseChanged) {
    if(isPhaseChanged){
      init();
    }

    // linear pulsing PWM
    analogWrite(LED_RED, out);
    value += inc;
    out = pow(255, value/200.0);
    if (value + inc >= 200 || value + inc <= 0) inc = -inc;

    delay(50);

    currentTime = millis();
    if(currentTime - initilTime >= waitBeforeSleep){
      sleep();
      init();
    }

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
