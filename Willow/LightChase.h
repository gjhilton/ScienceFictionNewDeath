#ifndef __LightChase__
#define __LightChase__

#include "Arduino.h"

#define N_PINS 10
#define MILLIS_PER_STEP 70

class LightChase{

public:
	
	LightChase(int i);

	void begin();
	void loop();

  void addPinAtIndex(int pin, int index);
  void allOn();
  void allOff();
  void startChase();
  void stopChase();
  void status();

private:
	
	int pins[N_PINS];
  int currentStep;
  unsigned long nextStepTime;

  bool loopPlayback;
  bool chase;
  bool flip;

  void step(int step);
  void LEDOn(int pin);
  void LEDOff(int pin);

};

#endif