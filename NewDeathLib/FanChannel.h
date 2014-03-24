#ifndef __FanChannel__
#define __FanChannel__

class FanChannel{

public:
	
	FanChannel(int _pinLeft, int pinRight);

	void begin();
	void loop();

	void on();
	void off();

private:
	
	int pinLeft;
	int pinRight;

	void setSpeed(int speed);

};

#endif