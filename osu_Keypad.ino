/*
 Created by Brandon Wang
 May 29, 2019
 osu! Keypad
    A two-button keypad used to play the Rhythm game osu! 
    Meant to be ran with an Arduino/ Genuino Micro or Leonardo Board in Arduino 1.8.9
    Must install libraries: 
      Keyboard Library: https://github.com/arduino-libraries/Keyboard 
      Bounce2: https://github.com/thomasfredericks/Bounce2
*/

// Including libraries: Keyboard Library & Debouncer (Bounce2)
#include <Keyboard.h>     
#include <Bounce2.h>

// Defining Pins
#define key1Pin 6 //button pin 1
#define key2Pin 7 //button pin 2
#define key1 'z' //122 //Letter z
#define key2 'x' //120 //Letter x

// Button states (prevents overlapping input) 
boolean state1 = true;   // if button1 has not been pushed
boolean state2 = true;   // if button2 has not been pushed

//creating bounce objects
Bounce debouncer1 = Bounce();
Bounce debouncer2 = Bounce();

void setup() {

  // So resistor is not required
  // Uses internal Arduino PCB resistor 
  pinMode(key1Pin, INPUT_PULLUP);   
  pinMode(key2Pin, INPUT_PULLUP);

  //attaching the buttons to the bouncer
  debouncer1.attach(key1Pin);
  debouncer2.attach(key2Pin);

  //time in Msec to wait to remove bounces
  debouncer1.interval(3);
  debouncer2.interval(3);
  
  Keyboard.begin();
}

void loop() {
  //loop checks if button is pushed 
  debouncer1.update();   
  debouncer2.update();   

  if (debouncer1.read() == LOW & state1) { // if statement checks for debouncer LOW and boolean: true         
    Keyboard.press(key1);   // send keypress for key1 
    state1 = false;         // boolean false, for later key release
    
  }
  if (debouncer1.read() == HIGH & !state1) { // if statement checks debouncer HIGH and boolean: false
    Keyboard.release(key1);   // release key1
    state1 = true;            // boolean set back to true
  }

  if (debouncer2.read() == LOW & state2) { // Send keypress
    Keyboard.press(key2);
    state2 = false;
 }
 
  if (debouncer2.read() == HIGH & !state2) { // Release key 2
    Keyboard.release(key2);
    state2 = true;
  }
}
