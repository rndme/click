/*
  click.h - Library for detecting clicks, double clicks and more
  Created by dandavis, 2016-10-7
  Released into the public domain.
*/
#ifndef Click_h
#define Click_h

#include "Arduino.h"

class Click
{
	
  public:
    Click(int pin);
	
	typedef void (*ClickEvent)(int pin, String type);
	
	
	void onEvent(ClickEvent cbEvent);
    void fire(String type);
	void monitor();
    void start();
	void setPin(int pin);
	
	//options
	int _PULSE_LENGTH = 55;
	int _CLICK_LENGTH = 500;
	int _DOUBLE_CLICK_PAUSE = 150;
	int _RESET_DURATION_MS = 3500;
	
	 int _pin;
	 
  private:
   
	int _state;
	int _neutral;
	int _lastPressDuration;
	unsigned long _time;
	unsigned long _origTime;
	String _stage = "ready";
	ClickEvent _cbEvent;
	
	
};

#endif