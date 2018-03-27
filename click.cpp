/*
  click.h - Library for detecting clicks, double clicks and more
  Created by dandavis, 2016-10-7
  Released into the public domain.
  
  action durations:
  
  button is pressed for:
  
  0ms - 49ms : pulse
  50 - 499 : click
  499 - 2499: long click  
  5000+ : reset   
  
*/

#include "Arduino.h"
#include "Click.h"

// constructor:
Click::Click(int pin)
{
  pinMode(pin, INPUT_PULLUP);
  _pin = pin;
}


// call this at end of setup()
void Click::start() {
	_state = digitalRead(_pin);
	_neutral = _state;
  	delay(1);
  	_time = millis();
}



// methods

void Click::setPin(int pin) { // manually fire an event
    _pin = pin;
	_state = digitalRead(_pin);
	_neutral = _state;
  	delay(1);
  	_time = millis();
}


void Click::fire(String type) { // manually fire an event
    _cbEvent(_pin, type);
}

void Click::monitor() {	// called in loop(), this state machine keeps on eye on pin changes
  int pin = digitalRead(_pin);
  String type="click";
  long dur = millis() - _time;
  long totalDur = millis() - _origTime;
	

	if(_stage == "ready"){
		if(pin != _state){
			_stage = "1stdown"; 
			_state = pin;
			_time = millis();
			_origTime = _time;
			return;
		}
		
		if(dur > _RESET_DURATION_MS ){
			_state = pin;
			_time = millis();
			return;
		}	
	} // end ready
		
	
	if(_stage == "1stdown"){
		if(pin != _state){
			_stage = "1stup"; 
			_state = pin;
			_time = millis();
			return;
		}
		if(dur > _RESET_DURATION_MS ){
			_stage = "stale"; 
			type = "reset";
			_time = millis();
			_cbEvent(_pin, type );
		}		
		return;
	}//end 1st down
	
	
	if(_stage == "1stup"){
		if(pin != _state){
			_stage = "2nddown";
			_state = pin;
			_time = millis();
			return;
		}	
		if(dur > _DOUBLE_CLICK_PAUSE ){
			_stage = "ready"; 
			_state = pin;
			type= "click";
			if(totalDur- dur < _PULSE_LENGTH ) type="pulse";
			if(totalDur > _CLICK_LENGTH) type="longclick";
			_cbEvent(_pin, type );
		}		
		return;
	}//end 1st up
	

		
	if(_stage == "2nddown"){
		if(pin != _state){
			_stage = "ready";
			_state = pin;
			_time = millis();
			type = "dblclick";
			_cbEvent(_pin, type);
		}	
		return;
	}//end 2nddown
		
	if(_stage == "stale"){
		if(pin != _state){
			_stage = "ready"; 
			_state = pin;
			_time = millis();
			
			return;
		}	
		
		return;
	}//end stale
	
    
}

/**
 * set callback - only one per instance at this time, spawn more instance to watch more than one button
 */
void Click::onEvent(ClickEvent cbEvent) {
    _cbEvent = cbEvent;
}
