#ifndef __Relay__
#define __Relay__

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