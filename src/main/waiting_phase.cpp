#include "pins_arduino.h"
#include "HardwareSerial.h"
#include "Arduino.h"
#include "waiting_phase.h"
#include <TimerOne.h>

namespace waiting_phase {

  const uint8_t INTN = digitalPinToInterrupt(buttons[0]);
  unsigned short value, out = 0;
  short inc = 1;
  volatile bool exit = false;

  static void next_phase() {
    exit = true;

    // disable B1 interrupt
    detachInterrupt(digitalPinToInterrupt(INTN));

    // disable Timer1 interrupt
    Timer1.detachInterrupt();
  }

  static void sleep() {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();
    next_phase();
  }

  static void init() {
    // turn off green leds
    for(int led: leds) {
      digitalWrite(led, LOW);
    }

    // turn off red led
    digitalWrite(LED_RED, HIGH);

    // init 10s timer
    Timer1.initialize(10000000);  // lengh in microseconds
    Timer1.attachInterrupt(sleep);

    // enable B1 interrupt
    attachInterrupt(digitalPinToInterrupt(INTN), next_phase, FALLING);

    // print to serial line
    Serial.println("Welcome to the Restore the Light Game. Press Key B1 to Start");
  }

  /* public */
  STATUS phase(bool isPhaseChanged) {
    if(isPhaseChanged){
      init();
    }

    // linear pulsing PWM
    analogWrite(LED_RED, out);
    value += inc;
    out = pow(255, value/100.0);
    if (value + inc >= 100 || value + inc <= 0) inc = -inc;

    delay(100);

    return exit ? ok : go_next_phase;
  }
}
