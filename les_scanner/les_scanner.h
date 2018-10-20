/*
les larson scanner driver


 */

#ifndef les_scanner_h
#define les_scanner_h
#include "Arduino.h"

class les_scanner{

	public:
		les_scanner (int cycle_time);
		void Setup ();
		void Update ();
		void shiftDisplay (byte data);
		int current_mode;

	private:
				void calcArgsMode1();
				void calcArgsMode2();
				void calcArgsMode3();
        int cycle_time;
				unsigned long last_update;
				int current_position;
				byte array_argument;
				int direction;

};


#endif
