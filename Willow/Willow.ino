#include "FanChannel.h"
#include "LightChannel.h"
#include "LightChase.h"
#include "Relay.h"
#include "MotionTrigger.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
// CONFIGURATION
////////////////////////////////////////////////////////////////////////////////////////////////

int CHASE_PINS[] = {15,14,9,8,17,16,7,4,3,2};

#define PING_PIN 13
#define RANGE_NEAR 76
#define RANGE_FAR 80

#define DRYER_PIN 18
#define FAN_PIN_LEFT 11
#define FAN_PIN_RIGHT 10

#define HERO_LIGHT_PIN 6
#define HERO_LIGHT_FLASH_DURATION_MS 0
#define HERO_LIGHT_FADE_DURATION_MS 1000

#define SERIAL_BAUD 57600

/////////////////////////////////////////////////////////////////////////////////////////////////
// DECLARATIONS
////////////////////////////////////////////////////////////////////////////////////////////////

LightChannel herolight(HERO_LIGHT_PIN,HERO_LIGHT_FLASH_DURATION_MS,HERO_LIGHT_FADE_DURATION_MS);
MotionTrigger motiontrigger(PING_PIN,RANGE_NEAR,RANGE_FAR);
Relay dryer(DRYER_PIN);
LightChase chase(2);
FanChannel fans(FAN_PIN_LEFT,FAN_PIN_RIGHT);

/////////////////////////////////////////////////////////////////////////////////////////////////
// ARDUINO LIFECYCLE
////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(SERIAL_BAUD);
  motiontrigger.begin(&onTrigger,&onDetrigger);
  herolight.begin();
  dryer.begin();
  for (int i=0; i<10; i++){
    int pin = CHASE_PINS[i];
    chase.addPinAtIndex(pin,i);
  }
  chase.begin();
}

void loop() {
  motiontrigger.loop();
  chase.loop();
  herolight.loop();
  delay(5);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// CALLBACKS FOR MOTION TRIGGER
////////////////////////////////////////////////////////////////////////////////////////////////

void onTrigger(){
  Serial.println("TRIGGER");
  herolight.on();
  dryer.on();
  fans.on();
  chase.stopChase();
  // chase.allOn();
}

void onDetrigger(){
  Serial.println("RELAX");
  herolight.cue();
  dryer.off();
  fans.off();
  chase.startChase();
}

