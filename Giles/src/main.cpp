#include "ofMain.h"
#include "testApp.h"

int main( ){
	ofSetupOpenGL(600,200,OF_WINDOW);
	ofRunApp(new testApp());
}
