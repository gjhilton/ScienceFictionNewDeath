#pragma once

#include "ofMain.h"

#define CONSOLE_NLINES 10
#define SERIAL_BAUD_RATE 57600

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void setupConsole();
		void appendToConsole(string s);
		string consoleToString();

		void setupSerial();
		void updateSerial();
		void processSerialData(unsigned char inputData);
		void handleSerialCommand(string command);

		void setupAudio();
		void setupUI();

		ofTrueTypeFont font;
		ofSerial serial;
		ofSoundPlayer loop;
		ofSoundPlayer release;

		string buffer="";
		string title;
		string console[CONSOLE_NLINES];
		bool isConnected;

};
