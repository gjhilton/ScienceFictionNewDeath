#include "FanChannel.h"
#include "Arduino.h"

FanChannel::FanChannel(int _pinLeft, int _pinRight){
	pinLeft = _pinLeft;
	pinRight = _pinRight;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// ARDUINO LIFECYCLE
////////////////////////////////////////////////////////////////////////////////////////////////

void FanChannel::begin(){
	pinMode(pinLeft, OUTPUT);
	pinMode(pinRight, OUTPUT);
	off();
}

void FanChannel::loop(){
	//
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC API
////////////////////////////////////////////////////////////////////////////////////////////////

void FanChannel::on(){
	digitalWrite(pinLeft, HIGH);
	digitalWrite(pinRight, HIGH);
}

void FanChannel::off(){
	digitalWrite(pinRight, LOW);
	digitalWrite(pinRight, LOW);
}