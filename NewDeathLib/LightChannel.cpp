#include "LightChannel.h"
#include "interpolation.h"

LightChannel::LightChannel(int _pin, int _flashDurationMS, int _fadeDurationMS){
	pin = _pin;
	flashDurationMS = _flashDurationMS;
	fadeDurationMS = _fadeDurationMS;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// ARDUINO LIFECYCLE
////////////////////////////////////////////////////////////////////////////////////////////////

void LightChannel::begin(){
	pinMode(pin, OUTPUT);
	reset();
}

void LightChannel::loop(){
 switch (state) {
	case CHANNEL_STATE_OFF:
		// nothing to do
		break;
	case CHANNEL_STATE_ON:
		if (millis() >= beginTime + flashDurationMS){
			startFade();
		}
		break;
	case CHANNEL_STATE_FADING:
		doFade();
		break;
  } 
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC API
////////////////////////////////////////////////////////////////////////////////////////////////

void LightChannel::cue(){
	flashThenFade();
}

void LightChannel::on(){
	setState(CHANNEL_STATE_OFF); // this is counterintuiitive. TODO: rename
	setBrightness(255);
}

void LightChannel::reset(){
	setState(CHANNEL_STATE_OFF);
	setBrightness(0);
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE IMPLEMENTATION
////////////////////////////////////////////////////////////////////////////////////////////////

void LightChannel::doFade(){
	unsigned long now = millis();
	if (now >= beginTime + fadeDurationMS){
		reset(); // fade is complete
	} else {
		float t = now - beginTime;
		float bright = interpolate(t, 255, -255, fadeDurationMS, LINEAR);
		setBrightness(bright);
	}
}

void LightChannel::flashThenFade(){
	setBrightness(255);
	setBeginTime();
	setState(CHANNEL_STATE_ON);
}

void LightChannel::setBrightness(int level){
	analogWrite(pin, level);
	brightness = level;
}

void LightChannel::startFade(){
	setState(CHANNEL_STATE_FADING);
	setBeginTime();
	setBrightness(255);
}

void LightChannel::setBeginTime(){
	beginTime = millis();
}

void LightChannel::setState(LightChannelState _state){
	state = _state;
}
