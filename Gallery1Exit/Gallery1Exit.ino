/////////////////////////////////////////////////////////////////////////////////////////////////
//
//
// ARDUINO NANO - ARDUINO NANO - ARDUINO NANO - ARDUINO NANO - ARDUINO NANO - ARDUINO NANO
//
//
////////////////////////////////////////////////////////////////////////////////////////////////

#include <LightChannel.h>
#include <MotionTrigger.h>
#include <SoftwareSerial.h>
#include <MP3Trigger.h>

/////////////////////////////////////////////////////////////////////////////////////////////////
// CONFIGURATION
////////////////////////////////////////////////////////////////////////////////////////////////

#define PING_PIN 7
#define RANGE_NEAR 79
#define RANGE_FAR 82

#define MP3_RX 3
#define MP3_TX 4

#define HERO_LIGHT_PIN 5
#define HERO_LIGHT_FLASH_DURATION_MS 0
#define HERO_LIGHT_FADE_DURATION_MS 1000

#define SERIAL_BAUD 57600

/////////////////////////////////////////////////////////////////////////////////////////////////
// DECLARATIONS
////////////////////////////////////////////////////////////////////////////////////////////////

LightChannel herolight(HERO_LIGHT_PIN,HERO_LIGHT_FLASH_DURATION_MS,HERO_LIGHT_FADE_DURATION_MS);
MotionTrigger motiontrigger(PING_PIN,RANGE_NEAR,RANGE_FAR);
SoftwareSerial trigSerial = SoftwareSerial(MP3_RX, MP3_TX);
MP3Trigger trigger;

/////////////////////////////////////////////////////////////////////////////////////////////////
// ARDUINO LIFECYCLE
////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(SERIAL_BAUD);
  motiontrigger.begin(&onTrigger,&onDetrigger);
  herolight.begin();
  setupAudio();
}

void loop() {
  motiontrigger.loop();
  herolight.loop();
  loopAudio();
  delay(20);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// CALLBACKS FOR MOTION TRIGGER
////////////////////////////////////////////////////////////////////////////////////////////////

void onTrigger(){
  Serial.println("TRIGGER");
  herolight.on();
  audioPlay();
}

void onDetrigger(){
  Serial.println("RELAX");
  herolight.cue();
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// MP3 TRIGGER SHIELD
////////////////////////////////////////////////////////////////////////////////////////////////

void setupAudio(){
  trigger.setup(&trigSerial);
  trigSerial.begin( MP3Trigger::serialRate() );
}

void loopAudio(){
  trigger.update();
}

void audioPlay(){
  trigger.play(2);
}

