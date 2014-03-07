#include "testApp.h"

#define SERIAL_BAUD_RATE 9600
#define VERSION 0.1

void testApp::setup(){

	// init audio
	bleep.loadSound("bleep.wav");
	bleep.setVolume(0.75f);

	// init graphics
	ofBackground(0);
	font.loadFont("DIN.otf", 11);
	title = "GILES (v" + ofToString(VERSION) + ") is watching ";

	// init serial
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
	int baud = SERIAL_BAUD_RATE;
	serial.setup(0, baud);
	title += deviceList[0].getDeviceName();


}

void testApp::update(){
	int nBytesRead = 0;
	int nRead  = 0;  // a temp variable to keep count per read
	char bytesReadString[4];
	unsigned char bytesReturned[3];

	memset(bytesReadString, 0, 4);
	memset(bytesReturned, 0, 3);

	while( (nRead = serial.readBytes( bytesReturned, 3)) > 0){
		nBytesRead = nRead;
	};

	memcpy(bytesReadString, bytesReturned, 3);
	if (nBytesRead > 0){
		string s;
		s = ofToString(bytesReadString);
		cout << "GOT: " << s << endl;
		bleep.play();
	}

	ofSoundUpdate();
}

void testApp::draw(){
	font.drawString(title, 10, 20);
}
