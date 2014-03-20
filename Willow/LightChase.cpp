#include "LightChase.h"

LightChase::LightChase(int i){
	loopPlayback = true;
  chase = false;
  flip = true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// ARDUINO LIFECYCLE
////////////////////////////////////////////////////////////////////////////////////////////////

// must call begin only after all pins added
void LightChase::begin(){
	for (int i=0; i<N_PINS; i++){
		pinMode(pins[i], OUTPUT);
	}
}

void LightChase::loop(){
	unsigned long now = millis();
	if (now >nextStepTime) {
		nextStepTime = now + MILLIS_PER_STEP;
		if (chase) {
			step(currentStep);
			currentStep++;
			if (currentStep >N_PINS){
				if (loopPlayback){
					currentStep = 1;
				} else {
          			currentStep = 0;
          			stopChase();
        		}
      		}
    	} else {
    		// flip = !flip;
    		for (int i=0; i<N_PINS; i++){
        		if (flip){
          			if (i % 2){
            			LEDOn(pins[i]);
          			} else {
            			LEDOff(pins[i]);
          			}
        		} else {
          			if (i % 2){
            			LEDOff(pins[i]);
          			} else {
            			LEDOn(pins[i]);
        			}
				}
      		}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC API
////////////////////////////////////////////////////////////////////////////////////////////////

void LightChase::addPinAtIndex(int pin, int index){
	pins[index] = pin;
}

void LightChase::startChase(){
	currentStep = 1;
  nextStepTime = 0;
  chase = true;
}

void LightChase::stopChase(){
  currentStep = 0;
  allOff();
  chase = false;
}

void LightChase::allOn(){
  for (int i=0; i<4; i++){
    LEDOn(pins[i]);
  }
}

void LightChase::allOff(){
  for (int i=0; i<N_PINS; i++){
    LEDOff(pins[i]);
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE IMPLEMENTATION
////////////////////////////////////////////////////////////////////////////////////////////////

void LightChase::step(int s){
  int pin = pins[s-1];
  allOff();
  LEDOn(pin);
}

void LightChase::LEDOn(int pin){
  digitalWrite(pin, HIGH);
}

void LightChase::LEDOff(int pin){
  digitalWrite(pin, LOW);
}
