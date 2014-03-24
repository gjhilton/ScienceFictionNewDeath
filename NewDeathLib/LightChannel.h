#ifndef __LightChannel__
#define __LightChannel__

#include "Arduino.h"

enum LightChannelState {
	CHANNEL_STATE_OFF,
	CHANNEL_STATE_ON,
	CHANNEL_STATE_FADING
};

class LightChannel{

public:
	
	LightChannel(int _pin, int _flashDurationMS, int _fadeDurationMS);

	void begin();
	void loop();

	void cue();
	void reset();

	void on();

private:
	
	int brightness;
	int pin;
	LightChannelState state;
	unsigned long beginTime;
	int fadeDurationMS;
	int flashDurationMS;

	void setBrightness(int level);
	void startFade();
	void setBeginTime();
	void flashThenFade();
	void setState(LightChannelState _state);
	void doFade();

};

#endif
