
#include <StandardCplusplus.h>
#include <serstream>

/////////////////////////////////////////////////////////////////////////////////////////////////
// CONFIGURATION
////////////////////////////////////////////////////////////////////////////////////////////////

// no assumption that led pins are contiguous.
// sequence as played back is as ordered in array
int CHASE_LED_PINS[] = {11,10,9,8,7,6,5,4,3,2};

#define PING_PIN 12
#define DRYER_RELAY_PIN 16

#define SERIAL_BAUD 57600
#define MS_BEFORE_RESET 1500 // duration in miliseconds during which doorway must be empty before reset
#define TRIGGER_THRESHOLD_CM 170 // distance from sensor closer than which we conclude somebody is there
#define LOOP_DELAY 35 // doesn't like being less than 35on the duemillanoldie
#define N_LEDS_IN_CHASE 10 // nb must be same as length of CHASE_LED_PINS
#define CHASE_MILLIS_PER_STEP 70 // nb this may be aliased by loop delay

/////////////////////////////////////////////////////////////////////////////////////////////////
// DECLARATIONS
////////////////////////////////////////////////////////////////////////////////////////////////

bool LOOP_CHASE = true; // if set, chasing lights will loop

enum SensorStatus {
  SENSOR_STATUS_IDLE,
  SENSOR_STATUS_TRIGGERED
};

int chaseStep = 0;
unsigned long nextChaseTime = 0;

int currentStatus = SENSOR_STATUS_IDLE;
unsigned long lastDetectTime;

using namespace std;
namespace std {
  ohserialstream cout(Serial);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// ARDUINO LIFECYCLE
////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(SERIAL_BAUD);
  initChase();
  initDryer();
  goToIdleState();
}

void loop() {
  serviceSensor();
  serviceChase();
  delay(LOOP_DELAY);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// STATE MACHINE
////////////////////////////////////////////////////////////////////////////////////////////////

void goToTriggeredState(){
  currentStatus = SENSOR_STATUS_TRIGGERED;
  cout << F("TRIGGERED") << endl;
  stopChase();
  chaseAllOn();
  dryerOn();
  startResetTimer();
}

void goToIdleState(){
  currentStatus = SENSOR_STATUS_IDLE;
  chaseAllOff();
  startChase();
  dryerOff();
  cout << F("-> IDLE") << endl;
}

void startResetTimer(){
   lastDetectTime = millis();
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// RANGE SENSOR
////////////////////////////////////////////////////////////////////////////////////////////////

void serviceSensor(){
   switch (currentStatus) {
    case SENSOR_STATUS_IDLE:
      if (personDetected()){
        goToTriggeredState();
      }
      break;
    case SENSOR_STATUS_TRIGGERED:
      if (personDetected()){
         startResetTimer();
      } else {
        if ((millis() - lastDetectTime) > MS_BEFORE_RESET) {
          goToIdleState();
        }
      }
      break;
  }
}

boolean personDetected(){
  pinMode(PING_PIN, OUTPUT);
  digitalWrite(PING_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(PING_PIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(PING_PIN, LOW);
  pinMode(PING_PIN, INPUT);
  unsigned long duration = pulseIn(PING_PIN, HIGH);
  unsigned long distance = microsecondsToCentimetres(duration);
  // cout << "distance " << distance << endl;
  if (distance <= TRIGGER_THRESHOLD_CM){
    return true;
  }
  return false;
}

long microsecondsToCentimetres(long microseconds){
  return microseconds / 29 / 2;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// HAND DRYER
////////////////////////////////////////////////////////////////////////////////////////////////

void initDryer(){
  pinMode(DRYER_RELAY_PIN, OUTPUT);
  digitalWrite(DRYER_RELAY_PIN, HIGH); // pull high to inhibit
}

void dryerOn(){
  digitalWrite(DRYER_RELAY_PIN, LOW); // pull low to activate
}

void dryerOff(){
  digitalWrite(DRYER_RELAY_PIN, HIGH);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// CHASING LIGHTS
////////////////////////////////////////////////////////////////////////////////////////////////

void initChase(){
  for (int i=0; i<N_LEDS_IN_CHASE; i++){
    pinMode(CHASE_LED_PINS[i], OUTPUT);
  }
}

void startChase(){
  chaseStep = 1;
  nextChaseTime = 0;
}

void stopChase(){
  chaseStep = 0;
  chaseAllOff();
}

void chaseAllOff(){
  for (int i=0; i<N_LEDS_IN_CHASE; i++){
    chaseLEDOff(CHASE_LED_PINS[i]);
  }
}

void chaseAllOn(){
  for (int i=0; i<N_LEDS_IN_CHASE; i++){
    chaseLEDOn(CHASE_LED_PINS[i]);
  }
}

void serviceChase(){
  if (chaseStep > 0) {
    unsigned long now = millis();
    if (now >nextChaseTime) {
      doChaseStep(chaseStep);
      nextChaseTime = now + CHASE_MILLIS_PER_STEP;
      chaseStep++;
      if (chaseStep > N_LEDS_IN_CHASE){
        if (LOOP_CHASE){
          chaseStep = 1;
        } else {
          chaseStep = 0;
          stopChase();
        }
      }
    }
  }
}

void doChaseStep(int step){
  int pin = CHASE_LED_PINS[step-1];
  chaseAllOff();
  chaseLEDOn(pin);
}

void chaseLEDOn(int pin){
  digitalWrite(pin, HIGH);
}

void chaseLEDOff(int pin){
  digitalWrite(pin, LOW);
}
