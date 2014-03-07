
#include <StandardCplusplus.h>
#include <serstream>

/////////////////////////////////////////////////////////////////////////////////////////////////
// DECLARATIONS
////////////////////////////////////////////////////////////////////////////////////////////////

#define TRIG_PIN 7
#define ECHO_PIN 8
#define LED_PIN 13
#define SERIAL_BAUD 9600
#define MS_BEFORE_RESET 1000
#define TRIGGER_THRESHOLD_CM 10
#define LOOP_DELAY 50

enum SensorStatus {
  SENSOR_STATUS_IDLE,
  SENSOR_STATUS_TRIGGERED
};

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
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  serviceSensor();
  delay(LOOP_DELAY);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// STATE MACHINE
////////////////////////////////////////////////////////////////////////////////////////////////

void goToTriggeredState(){
  currentStatus = SENSOR_STATUS_TRIGGERED;
  cout << F("-> TRIGGERED") << endl;
  startResetTimer();
}

void goToIdleState(){
  currentStatus = SENSOR_STATUS_IDLE;
  cout << F("-> IDLE") << endl;
}

void startResetTimer(){
   lastDetectTime = millis();
   // cout << F("(still somebody there)") << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// RANGE SENSOR
////////////////////////////////////////////////////////////////////////////////////////////////

void serviceSensor(){
   switch (currentStatus) {
    case SENSOR_STATUS_IDLE:
      if (personDetected()){
        goToTriggeredState();
      } else {
        // cout << F(".") << endl;;
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
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, LOW);
  unsigned long duration = pulseIn(ECHO_PIN, HIGH);
  unsigned long distance = microsecondsToCentimetres(duration);
  if (distance <= TRIGGER_THRESHOLD_CM){
    return true;
  }
  return false; 
}

long microsecondsToCentimetres(long microseconds){
  return microseconds / 29 / 2;
}
