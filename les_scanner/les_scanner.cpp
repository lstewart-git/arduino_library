
#include "Arduino.h"

#include "les_scanner.h"
#define  DATA_PIN  11
#define  CLOCK_PIN  12
#define  LATCH_PIN  13

les_scanner::les_scanner(int wait_time){
    // time in ms between led 'movement'
	  cycle_time = wait_time;
}

  void les_scanner::Setup()
  {
	   pinMode(DATA_PIN, OUTPUT);
     pinMode(CLOCK_PIN, OUTPUT);
     pinMode(LATCH_PIN, OUTPUT);
     last_update = 0;
     current_position = 0;
     array_argument = B11000000;
     direction = 1;
     current_mode = 0;
  }


  void les_scanner::Update()
  {
    // check to see if it's time to change internal state
  unsigned long currentMillis = millis();
	// check that delay timer fm last press expired
	if (currentMillis > last_update + cycle_time){
      last_update = currentMillis;
      // display the byte, except in mode 0 (startup)
      if (current_mode !=0) shiftDisplay(array_argument);
      if (current_mode == 1) calcArgsMode1();
      if (current_mode == 2) calcArgsMode2();
      if (current_mode == 3) calcArgsMode3();
      }
		} // END UPDATE


   void les_scanner::shiftDisplay(byte data) {
     digitalWrite(LATCH_PIN, LOW);
     shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, data);
     digitalWrite(LATCH_PIN, HIGH);
   }

   void les_scanner::calcArgsMode1() {
     if (direction == -1) array_argument = array_argument << 1;
     if (direction == 1) array_argument = array_argument >> 1;
     current_position = current_position + direction;
     if (current_position == 8) {
       direction = -1;
       array_argument = B00000001;
     }
     if (current_position == 0) {
       direction = 1;
       array_argument = B10000000;
       }
   }

void les_scanner::calcArgsMode2() {
  if (direction == -1) array_argument = array_argument << 1;
  if (direction == 1) array_argument = array_argument >> 1;
  current_position = current_position + direction;
  if (current_position == 8) {
    direction = -1;
    array_argument = B00000111;
  }
  if (current_position == 0) {
    direction = 1;
    array_argument = B11100000;
    }
}

void les_scanner::calcArgsMode3() {
  int rnd_byte = random(255);
  array_argument = rnd_byte;
  }
