#include <click.h>

Click click(7); //create a click event on pin7


// demo of Click library for arduino ide

// use a handler like this to capture button pulses, clicks, double clicks, long clicks, and really long clicks (reset)
void onClick(int pin, String type) { // just a demo, all it does is log the time, type and pin of the button event
  Serial.println( String(millis()) + "\t" + type + " on pin" + String(pin) );
}

void setup() { // you don't have to configure pin7 here, it's already setup as INPUT_PULLUP;
  pinMode(13, OUTPUT);
  Serial.begin(115200);

  click.onEvent(onClick); // bind the click event to your custom handler
  
  delay(10);
  Serial.println("ready!");
  delay(20); // buy time for inputs to settle, optional but recommended.

 // here are the default options, can be omnmited if they work for your hardware, otherwise tweak them. runtime editable.
  click._PULSE_LENGTH = 55; // set to 0 to disable pulses
  click._CLICK_LENGTH = 500;
  click._DOUBLE_CLICK_PAUSE = 150; // set to 0 to disable dblclicks
  click._RESET_DURATION_MS = 3500; // to disable, set this for longer than anyone would want to hold a button down...

  // required:
  click.start(); // start watching the pin for clicks and stuff
}

int count = 0;

void loop() {
  click.monitor(); // called to check for pin activity
  delay(2); // save some power. a value of no more than 5 is recommended if you want to capture pulse events
}
