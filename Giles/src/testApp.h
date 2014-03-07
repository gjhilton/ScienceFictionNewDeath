#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		ofTrueTypeFont font;
		ofSerial serial;
		ofSoundPlayer bleep;

		string title;

};
