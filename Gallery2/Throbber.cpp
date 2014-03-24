#include "Throbber.h"
#include "interpolation.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////////////////////

Throbber::Throbber(int _pin_top, int _pin_left, int _pin_right) {
  pin_top = _pin_top;
  pin_left  = _pin_left;
  pin_right = _pin_right;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// ARDUINO LIFECYCLE
////////////////////////////////////////////////////////////////////////////////////////////////

void Throbber::setup() {
  pinMode(pin_top, OUTPUT);
  pinMode(pin_left, OUTPUT);
  pinMode(pin_right, OUTPUT);
  brightness = 0;
}

void Throbber::loop() {
  switch (state) {
    case BRIGHTNESS_CONSTANT:
      break;
    case BRIGHTNESS_DECREASING:
      brightness-=2;
      if(brightness <=5){
       state = BRIGHTNESS_INCREASING;
      } 
      break;
    case BRIGHTNESS_INCREASING:
      brightness+=2;
      if(brightness >=100){
       state = BRIGHTNESS_DECREASING;
      } 
      break;
  }
  setBrightness(brightness);
  Serial.println(state);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC API
////////////////////////////////////////////////////////////////////////////////////////////////

void Throbber::cue() {
  state = BRIGHTNESS_CONSTANT;
  brightness = 255;
}

void Throbber::reset() {
  state = BRIGHTNESS_DECREASING;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE IMPLEMENTATION
////////////////////////////////////////////////////////////////////////////////////////////////

//float bright = interpolate(t, 255, -255, fadeDurationMS, LINEAR);

void Throbber::setBrightness(int level) {
  Serial.println(level);
  analogWrite(pin_top, level);
  analogWrite(pin_left, level);
  analogWrite(pin_right, level);
}
