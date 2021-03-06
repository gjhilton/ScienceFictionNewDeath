#include "MotionTrigger.h"

MotionTrigger::MotionTrigger(int _pin, int near, int far){
	pin = _pin;
	lastReadTime = 0;
	triggerThresholdNearCM = near;
	triggerThresholdFarCM = far;

	#ifdef SENSOR_CALIBRATION_MODE

	minDistance = 1000;
	maxDistance = 0;

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// ARDUINO LIFECYCLE
////////////////////////////////////////////////////////////////////////////////////////////////

void MotionTrigger::begin(CallbackFunc _triggerfunc,CallbackFunc _relaxfunc){
	#ifdef SENSOR_VERBOSE_MODE
		Serial.println("SENSOR VERBOSE MODE");
	#endif
	#ifdef SENSOR_CALIBRATION_MODE
		Serial.println("SENSOR CALIBRATION MODE");
	#else
		setTriggerCallback(_triggerfunc);
		setRelaxCallback(_relaxfunc);
		relax();
	#endif
}

void MotionTrigger::loop(){
	unsigned long now = millis();
	if ((now - lastReadTime) > SENSOR_READ_INTERVAL_MS){
		lastReadTime = now;
		updateState();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC API
////////////////////////////////////////////////////////////////////////////////////////////////

void MotionTrigger::relax(){
	status = TRIGGER_STATUS_IDLE;
	onRelaxCallback();
}

void MotionTrigger::trigger(){
	status = TRIGGER_STATUS_TRIGGERED;
	onTriggerCallback();
	startResetTimer();
}

void MotionTrigger::setTriggerCallback(CallbackFunc _func){
	onTriggerCallback = _func;
}


void MotionTrigger::setRelaxCallback(CallbackFunc _func){
	onRelaxCallback = _func;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE IMPLEMENTATION
////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef SENSOR_CALIBRATION_MODE

// in calibration mode, we just print the range to the serial device

void MotionTrigger::updateState(){
	personDetected();
	//
	bool update = false;
	if (lastDistance > maxDistance){
		maxDistance = lastDistance;
		update = true;
	}
	if (lastDistance < minDistance){
		minDistance = lastDistance;
		update = true;
	}
	if (update){
		Serial.print("Distance range: ");
		Serial.print(minDistance);
		Serial.print("-");
		Serial.println(maxDistance);
	}
}

#else

void MotionTrigger::updateState(){
	switch (status) {
		case TRIGGER_STATUS_IDLE:
		  if (personDetected()){
			trigger();
#ifdef SENSOR_VERBOSE_MODE
			Serial.print("trigger because distance = ");
			Serial.println(lastDistance);
#endif
		  }
		  break;
		case TRIGGER_STATUS_TRIGGERED:
		  if (personDetected()){
			 startResetTimer();
#ifdef SENSOR_VERBOSE_MODE
			 Serial.print("reset because distance = ");
			 Serial.println(lastDistance);
#endif
		  } else {
#ifdef SENSOR_VERBOSE_MODE
		  	Serial.print("nobody there because distance = ");
			Serial.println(lastDistance);
#endif
			if ((millis() - lastDetectTime) > NODETECT_INTERVAL_BEFORE_RELAX_MS) {
			  relax();
			}
		  }
		  break;
	  } 
}

#endif

void MotionTrigger::startResetTimer(){
	lastDetectTime = millis();
}

boolean MotionTrigger::personDetected(){
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
	delayMicroseconds(2);
	digitalWrite(pin, HIGH);
	delayMicroseconds(5);
	digitalWrite(pin, LOW);
	pinMode(pin, INPUT);
	unsigned long duration = pulseIn(pin, HIGH);
	unsigned long distance = microsecondsToCentimetres(duration);
	lastDistance = distance;
	if (distance <= 0){  // this is an erroneous reading - ignore it
		#ifdef SENSOR_VERBOSE_MODE
			 Serial.println("Error: distance 0 ");
		#endif
		return false;
	}
	if ((distance < triggerThresholdNearCM) || (distance > triggerThresholdFarCM)) {
		return true;
	}
	return false; 
}

long MotionTrigger::microsecondsToCentimetres(long microseconds){
  return microseconds / 29 / 2;
}
