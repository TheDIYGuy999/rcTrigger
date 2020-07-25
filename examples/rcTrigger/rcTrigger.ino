/*
 rcTrigger.cpp - Library for RC signal detection (in microseconds) and actions triggering
 Created by TheDIYGuy999 June 2020
 Released into the public domain.
 V1.0
 */

 // Wiring see pictures on GitHub

#include <rcTrigger.h>

//
// =======================================================================================================
// PIN ASSIGNMENTS & GLOBAL VARIABLES
// =======================================================================================================
//
// Pin assignment 
#define SERVO1_PIN 13 // connect to RC receiver servo output channel 1 (aileron, steering)
#define SERVO2_PIN 12 // connect to RC receiver servo output channel 2 (elevator, 3 pos. switch for shifting) (left throttle in CATERPILLAR_MODE)
#define SERVO3_PIN 14 // connect to RC receiver servo output channel 3 (throttle) (right throttle in CATERPILLAR_MODE)
#define SERVO4_PIN 27 // connect to RC receiver servo output channel 4 (rudder, pot)

// Global variables
uint32_t pulseWidth[4]; // Current RC signal pulse width [0] = steering, [1] = 3p. switch, [2] = throttle, [3] = pot

// rcTrigger objects
rcTrigger gear1(500); // 500 is the target time in ms for short / long button press detection
rcTrigger gear2(500);
rcTrigger gear3(500);

rcTrigger button1(500);
rcTrigger button2(500);
rcTrigger button3(500);

rcTrigger button1toggle(500);
rcTrigger button2toggle(500);
rcTrigger button3toggle(500);

rcTrigger button1toggleLong(500);
rcTrigger button2toggleLong(500);
rcTrigger button3toggleLong(500);

//
// =======================================================================================================
// MAIN ARDUINO SETUP (1x during startup)
// =======================================================================================================
//

void setup() {

  // Pin modes
  pinMode(SERVO1_PIN, INPUT_PULLDOWN);
  pinMode(SERVO2_PIN, INPUT_PULLDOWN);
  pinMode(SERVO3_PIN, INPUT_PULLDOWN);
  pinMode(SERVO4_PIN, INPUT_PULLDOWN);

  // Serial setup
  Serial.begin(115200); // USB serial (for DEBUG)
}

//
// =======================================================================================================
// READ PWM RC SIGNALS
// =======================================================================================================
//

void readRcSignals() {
  // measure RC signal pulsewidth:

  // CH1 Steering 
  pulseWidth[0] = pulseIn(SERVO1_PIN, HIGH, 50000);   

  // CH2 Gearbox servo (3 position switch wired to analog channel)
  pulseWidth[1] = pulseIn(SERVO2_PIN, HIGH, 50000);

  // CH3 Throttle
  pulseWidth[2] = pulseIn(SERVO3_PIN, HIGH, 50000);

  // CH4 (buttons wired to analog channel, using voltage divider resistors)
  pulseWidth[3] = pulseIn(SERVO4_PIN, HIGH, 50000);
}

//
// =======================================================================================================
// RC TRIGGER TEST SECTION
// =======================================================================================================
//

unsigned long rcTrigger() {

  Serial.println(pulseWidth[1]); // Use this to determine your target points (change [X])

  // True as long as in position
  if (gear1.momentary(pulseWidth[1], 1000)) Serial.println("Gear 1");
  if (gear2.momentary(pulseWidth[1], 1500)) Serial.println("Gear 2");
  if (gear3.momentary(pulseWidth[1], 2000)) Serial.println("Gear 3");

  // Toggle true / false, if in position < 500ms
  if (button1toggle.toggle(pulseWidth[3], 1000)) Serial.println("Button toggle 1");
  if (button2toggle.toggle(pulseWidth[3], 1150)) Serial.println("Button toggle 2");
  if (button3toggle.toggle(pulseWidth[3], 2000)) Serial.println("Button toggle 3");

  // Toggle true / false, if in position > 500ms
  if (button1toggleLong.toggleLong(pulseWidth[3], 1000)) Serial.println("Button toggle 1 long");
  if (button2toggleLong.toggleLong(pulseWidth[3], 1150)) Serial.println("Button toggle 2 long");
  if (button3toggleLong.toggleLong(pulseWidth[3], 2000)) Serial.println("Button toggle 3 long");
}

//
// =======================================================================================================
// MAIN LOOP
// =======================================================================================================
//

void loop() {

  // measure RC signals mark space ratio
  readRcSignals();

  
  // Triggering actions
  rcTrigger();
}
