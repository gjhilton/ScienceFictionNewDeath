#ifndef __Throbber__
#define __Throbber__

#include "Arduino.h"

enum ThrobberState {
	BRIGHTNESS_INCREASING,
	BRIGHTNESS_DECREASING,
	BRIGHTNESS_CONSTANT
};

class Throbber{

public:
	
	Throbber(int _pin_top,int _pin_left,int _pin_right);

	void setup();
	void loop();

	void cue();
	void reset();

ThrobberState state;

private:
	
	int pin_top;
	int pin_left;
	int pin_right;

        int throb_max;
        int throb_min;
        int fullon;
        
        int brightness;

	void setBrightness(int brightness);
};

#endif
