#ifndef __LightChase__
#define __LightChase__

#include "Arduino.h"

#define N_PINS 10

class LightChase{

public:
	
	LightChase(int i);

	void begin();
	void loop();

private:
	
	int pins[N_PINS];

};

#endif

/*


bool LOOP_CHASE = true; // if set, chasing lights will loop

int chaseStep = 0;
unsigned long nextChaseTime = 0;


#define N_LEDS_IN_CHASE 10 // nb must be same as length of CHASE_LED_PINS
#define CHASE_MILLIS_PER_STEP 70 // nb this may be aliased by loop delay

/////////////////////////////////////////////////////////////////////////////////////////////////
// CHASING LIGHTS
////////////////////////////////////////////////////////////////////////////////////////////////
/*
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
  herolight.cue();
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
*/
