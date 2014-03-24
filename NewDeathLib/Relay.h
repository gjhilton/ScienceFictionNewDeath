#ifndef __Relay__
#define __Relay__

// #define RELAY_LOG_MODE // uncomment to enable serial output | comment to run normally

class Relay{

public:
	
	Relay(int _pin);

	void begin();

	void on();
	void off();

private:
	
	int pin;
	bool isON;

};

#endif