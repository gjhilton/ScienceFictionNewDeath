#include "FanChannel.h"
#include "LightChannel.h"
#include "LightChase.h"
#include "Relay.h"
#include "MotionTrigger.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
// CONFIGURATION
////////////////////////////////////////////////////////////////////////////////////////////////

#define PING_PIN 5 //13
#define RANGE_NEAR 50
#define RANGE_FAR 300
// #define SENSOR_CALIBRATION_MODE // uncomment to enable calibration | comment to run normally

#define DRYER_PIN 18
#define FAN_PIN_LEFT 11
#define FAN_PIN_RIGHT 10

#define HERO_LIGHT_PIN 5
#define HERO_LIGHT_FLASH_DURATION_MS 0
#define HERO_LIGHT_FADE_DURATION_MS 5000

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
  /*
  herolight.begin();
  dryer.begin();
  chase.begin();
  fans.begin();
  */
}

void loop() {
  motiontrigger.loop();
  /*
  chase.loop();
  herolight.loop();
  fans.loop();
  */
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// CALLBACKS FOR MOTION TRIGGER
////////////////////////////////////////////////////////////////////////////////////////////////

void onTrigger(){
  Serial.println("TRIGGER");
  herolight.on();
  dryer.on();
}

void onDetrigger(){
  Serial.println("RELAX");
  herolight.reset();
  dryer.off();
}

