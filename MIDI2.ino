/* @file MultiKey.ino
This keypad library MUST be V 3 or above of keypad from
https://github.com/Nullkraft/Keypad
Do a get code as zip  - this saves as Keypad-master.zip
Then do a Sketch,Include Library
Add .zip Library
Select the downloaded zip file
 
If you get an error
Multiple libraries were found for "Keypad.h"
you have to go to documents, arduino,libraries and delete Keypad directory
There should be a directory called Keypad-master
*/
#include "ardumidi.h"
#include <Keypad.h>
//#define DEBUG
//#define DEBUGKEYS  // if defines will print out on serial the keys states
/* these are the sequences sent to midi controller
  from the key presses.
  Possibe 30 sequences for each key as I had no idea
  Change it with maxsequence
  we start at key zero
 
  note then end of the sequence has to be -1 !!!
*/
const int maxsequence = 3;                    // 3 codes byte channel, byte key, byte velocity
byte keyspressedsequence[20][maxsequence] =
{
  {0, MIDI_C, 127 },
  {0, MIDI_E + MIDI_FLAT + MIDI_OCTAVE, 127},
  {0, MIDI_G + MIDI_OCTAVE, 127},
  { -1},
  { -1},
  { -1},
  { -1},
  { -1},
  { -1},
  { -1},
  { -1},
  { -1},
  { -1},
  { -1},
  { -1},
  { -1},
  { -1},
  { -1},
  { -1},
  { -1}
};
 
 
 
 
const byte ROWS = 5; //four rows
const byte COLS = 2; //three columns
 
// these keys are coverted from char to ascii - 65  - so the first one MUST be A
char keys[ROWS][COLS] = {
  {'A', 'B'},
  {'C', 'D'},
  {'E', 'F'},
  {'G', 'H'},
  {'I', 'J'}
};
 
byte rowPins[ROWS] = {3, 4, 5, 6,7}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {13, 12,};    //connect to the column pinouts of the kpd
int codeIndex;                     // the index to the keyspressedsequence
String msg;
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
 
 
void setup() {
  Serial.begin(9600);
  //calls function "keyEventListener" during any kpd.getKeys() call.
  kpd.addStatedEventListener( keyEventListener );
}
 
//will be called on change in key state
void keyEventListener(char key, KeyState kpadState)
{
  codeIndex = key - 65;    // convert the key char to an int  so A = 0 and so on
  //note the change in key state
  switch (kpadState)     // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
  {
#ifdef DEBUG
      Serial.print(" codeIndex = ");
      Serial.print(codeIndex);
#endif
 
 
    case PRESSED:
      msg = " PRESSED ";
      #ifdef DEBUGKEYS
            Serial.print(msg );
      #endif
      //   byte channel, byte key, byte velocity
      midi_note_on(keyspressedsequence[codeIndex][0],keyspressedsequence[codeIndex][1],keyspressedsequence[codeIndex][1]);
            #ifdef DEBUGKEYS
            Serial.println();
            Serial.print(keyspressedsequence[codeIndex][0],DEC);
            Serial.println();
            Serial.print(keyspressedsequence[codeIndex][1],DEC);
            Serial.println();
            Serial.print(keyspressedsequence[codeIndex][2],DEC);
            Serial.println();
      #endif
      break;
    
    
    case HOLD:
      msg = " HOLD.";
                          #ifdef DEBUGKEYS
                                Serial.print(msg );
                          #endif
      break;
    case RELEASED:
      msg = " RELEASED.";
                          #ifdef DEBUGKEYS
                                Serial.print(msg );
                          #endif
      break;
    case IDLE:
      msg = " IDLE.";
                          #ifdef DEBUGKEYS
                                Serial.print(msg );
                          #endif
      break;
  }
}
 
void loop() {
 
  // Fills kpd.key[ ] array with up-to 10 active keys.
  // Returns true if there are ANY active keys.
  // But we don't care, because "keyEventListener" takes care of it all now.
  kpd.getKeys();
}  // End loop
