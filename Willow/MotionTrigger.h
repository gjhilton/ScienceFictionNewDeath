#ifndef __MotionTrigger__
#define __MotionTrigger__

#include "Arduino.h"

// #define SENSOR_CALIBRATION_MODE // uncomment to enable calibration | comment to run normally
#define SENSOR_READ_INTERVAL_MS 20
#define NODETECT_INTERVAL_BEFORE_RELAX_MS 500

typedef void (*CallbackFunc)();

enum TriggerStatus {
  TRIGGER_STATUS_IDLE,
  TRIGGER_STATUS_TRIGGERED
};

class MotionTrigger{

public:
	
	MotionTrigger(int _pin, int near, int far);

	void begin(CallbackFunc _triggerfunc,CallbackFunc _relaxfunc);
	void loop();

	void trigger();
	void relax();

private:
	
	int pin;
	CallbackFunc onTriggerCallback;
	CallbackFunc onRelaxCallback;
	TriggerStatus status;

	unsigned long lastReadTime;
	unsigned long lastDetectTime;

	int triggerThresholdNearCM;
	int triggerThresholdFarCM;
	int readInterval;
	int durationBeforeRelax;
	long lastDistance;

	void setRelaxCallback(CallbackFunc _func);
	void setTriggerCallback(CallbackFunc _func);

	void updateState();
	void startResetTimer();
	boolean personDetected();
	long microsecondsToCentimetres(long microseconds);

	#ifdef SENSOR_CALIBRATION_MODE

	int minDistance;
	int maxDistance;

	#endif
};

#endif
