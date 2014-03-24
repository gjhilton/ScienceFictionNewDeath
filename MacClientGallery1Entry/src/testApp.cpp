#include "testApp.h"

#define VERSION 0.3

/////////////////////////////////////////////////////////////////////////////////////////////////
// OF LIFECYCLE
////////////////////////////////////////////////////////////////////////////////////////////////

void testApp::setup(){
	setupConsole();
	setupAudio();
	setupUI();
	setupSerial();
}

void testApp::update(){
	updateSerial();
	ofSoundUpdate();
}

void testApp::draw(){
	font.drawString(title, 10, 20);
	font.drawString(consoleToString(), 10, 36);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// CONSOLE
////////////////////////////////////////////////////////////////////////////////////////////////

void testApp::setupConsole(){
	for (int i=0; i< CONSOLE_NLINES; i++){
		console[i] = "";
	}
}

void testApp::appendToConsole(string s){
	for (int i=CONSOLE_NLINES-1; i>0; i--){
		console[i] = console[i-1];
	}
	// escape newlines in input
	ofStringReplace(s, "\n", "\\n");
	// not a very efficient way to build the string
	console[0] = ofToString(ofGetHours()) + ":" + ofToString(ofGetMinutes()) + ":" + ofToString(ofGetSeconds()) + " " + s;
}

string testApp::consoleToString(){
	string s;
	for (int i=0; i< CONSOLE_NLINES; i++){
		s += "\n" + console[i];
	}
	return s;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// UI
////////////////////////////////////////////////////////////////////////////////////////////////

void testApp::setupUI(){
	ofBackground(0);
	font.loadFont("DIN.otf", 11);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// AUDIO
////////////////////////////////////////////////////////////////////////////////////////////////

void testApp::setupAudio(){
	trigger.loadSound("start.mp3");
	trigger.setVolume(0.75f);
	loop.loadSound("loop.mp3");
	loop.setVolume(0.75f);
	loop.setLoop(true);
	release.loadSound("release.mp3");
	release.setVolume(0.75f);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// SERIAL COMMS
////////////////////////////////////////////////////////////////////////////////////////////////

void testApp::setupSerial(){
	isConnected = false;
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
	string serialDeviceName = deviceList[0].getDeviceName();
	if (!ofIsStringInString(serialDeviceName,"Bluetooth")){
		isConnected = serial.setup(0, SERIAL_BAUD_RATE);
	}
	if (isConnected){
		title = "GILES (v" + ofToString(VERSION) + ") is watching " + serialDeviceName + " [" + ofToString(SERIAL_BAUD_RATE) + " baud]";
	} else {
		string allDevices;
		for(int k = 0; k < (int)deviceList.size(); k++){
			allDevices += "\n - " + deviceList[k].getDeviceName();
		}
		title = "Help! I'm not connected to anything.\nNone of these ports taste like Arduino:\n" + allDevices + "\n\nCheck connections? Restart me? Turn everything off then on again?";
		ofSetColor(255,0,0);
	}
}

void testApp::updateSerial(){
	if (isConnected){
		static vector<unsigned char> bytesToProcess;
		int bytesToRead = serial.available();
		if (bytesToRead>0) {
			bytesToProcess.resize(bytesToRead);
			serial.readBytes(&bytesToProcess[0], bytesToRead);
			for (int i = 0; i < bytesToRead; i++) {
				processSerialData((char)(bytesToProcess[i]));
			}
		}
	}
}

void testApp::processSerialData(unsigned char inputData){
	string input = ofToString(inputData);
	if (
		(input!= "\r") &&	// arduino Serial.println sends str + \r\n -- ignore carriage return
		(inputData < 127)	// for some reason, high ascii junk sometimes get randomly sent at startup
	){
		if (input == "\n"){ // use \n to terminate command string
			handleSerialCommand(buffer);
			buffer = "";
		} else {
			buffer = buffer + input;
		}
	}
}

void testApp::handleSerialCommand(string command){
	appendToConsole("rx: " + command);
	if (command == "TRIGGER"){
		if (release.getIsPlaying()){
			release.stop();
		}
		trigger.play();
		loop.play();
	}
	if (command == "RELAX"){
		if (loop.getIsPlaying()){
			loop.stop();
		}
		release.play();
	}
}