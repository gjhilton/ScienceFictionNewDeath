#include "ofMain.h"
#include "testApp.h"

int main( ){
	ofSetupOpenGL(600,220,OF_WINDOW);
	ofRunApp(new testApp());
}
