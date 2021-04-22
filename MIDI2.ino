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
 
*/
const int maxsequence = 3;                    // 3 codes byte channel, byte key, byte velocity
                                              // 99 in first position disables
byte keysPRESSEDsequence[20][maxsequence] =
{
  {0, MIDI_C4, 127 },
  {0, MIDI_E4 + MIDI_FLAT + MIDI_OCTAVE, 127},
  {0, MIDI_G4 + MIDI_OCTAVE, 127},
  {0, MIDI_G4 + MIDI_OCTAVE, 127},
  {0, MIDI_A3 + MIDI_OCTAVE, 127},
  {0, MIDI_B3 + MIDI_OCTAVE, 127},
  {0, MIDI_C3 + MIDI_OCTAVE, 127},
  {0, MIDI_D3 + MIDI_OCTAVE, 127},
  {0, MIDI_E3 + MIDI_OCTAVE, 127},
  {0, MIDI_F3 + MIDI_OCTAVE, 127},
  {0, MIDI_G3 + MIDI_OCTAVE, 127},
  {0, MIDI_A2 + MIDI_FLAT, 127},
  {0, MIDI_B2 + MIDI_FLAT, 127},
  {0, MIDI_D2 + MIDI_FLAT, 127},
  {0, MIDI_D2 + MIDI_FLAT, 127},
  {0, MIDI_E2 + MIDI_FLAT, 127},
  {0, MIDI_F2 + MIDI_FLAT, 127},
  {0, MIDI_G2 + MIDI_FLAT, 127},
  {0, MIDI_A3, 127},
  {0, MIDI_B3, 127}
};

 // 99 in first position disables
 byte keysHELDsequence[20][maxsequence] =
{
  {0, MIDI_B3 + MIDI_OCTAVE, 127 },
  {99, MIDI_E4 + MIDI_FLAT + MIDI_OCTAVE, 127},
  {99, MIDI_G4 + MIDI_OCTAVE, 127},
  {99, MIDI_G4 + MIDI_OCTAVE, 127},
  {99, MIDI_A3 + MIDI_OCTAVE, 127},
  {99, MIDI_B3 + MIDI_OCTAVE, 127},
  {99, MIDI_C3 + MIDI_OCTAVE, 127},
  {99, MIDI_D3 + MIDI_OCTAVE, 127},
  {99, MIDI_E3 + MIDI_OCTAVE, 127},
  {99, MIDI_F3 + MIDI_OCTAVE, 127},
  {99, MIDI_G3 + MIDI_OCTAVE, 127},
  {99, MIDI_A2 + MIDI_FLAT, 127},
  {99, MIDI_B2 + MIDI_FLAT, 127},
  {99, MIDI_D2 + MIDI_FLAT, 127},
  {99, MIDI_D2 + MIDI_FLAT, 127},
  {99, MIDI_E2 + MIDI_FLAT, 127},
  {99, MIDI_F2 + MIDI_FLAT, 127},
  {99, MIDI_G2 + MIDI_FLAT, 127},
  {99, MIDI_A3, 127},
  {99, MIDI_B3, 127}
};

 // 99 in first position disables
 byte keysRELEASEDsequence[20][maxsequence] =
{
  {0, MIDI_G3 + MIDI_OCTAVE, 127 },
  {99, MIDI_E4 + MIDI_FLAT + MIDI_OCTAVE, 127},
  {99, MIDI_G4 + MIDI_OCTAVE, 127},
  {99, MIDI_G4 + MIDI_OCTAVE, 127},
  {99, MIDI_A3 + MIDI_OCTAVE, 127},
  {99, MIDI_B3 + MIDI_OCTAVE, 127},
  {99, MIDI_C3 + MIDI_OCTAVE, 127},
  {99, MIDI_D3 + MIDI_OCTAVE, 127},
  {99, MIDI_E3 + MIDI_OCTAVE, 127},
  {99, MIDI_F3 + MIDI_OCTAVE, 127},
  {99, MIDI_G3 + MIDI_OCTAVE, 127},
  {99, MIDI_A2 + MIDI_FLAT, 127},
  {99, MIDI_B2 + MIDI_FLAT, 127},
  {99, MIDI_D2 + MIDI_FLAT, 127},
  {99, MIDI_D2 + MIDI_FLAT, 127},
  {99, MIDI_E2 + MIDI_FLAT, 127},
  {99, MIDI_F2 + MIDI_FLAT, 127},
  {99, MIDI_G2 + MIDI_FLAT, 127},
  {99, MIDI_A3, 127},
  {99, MIDI_B3, 127}
}; 

// 99 in first position disables
  byte keysIDLEsequence[20][maxsequence] =
{
  {0, MIDI_B3, 127 },
  {99, MIDI_E4 + MIDI_FLAT + MIDI_OCTAVE, 127},
  {99, MIDI_G4 + MIDI_OCTAVE, 127},
  {99, MIDI_G4 + MIDI_OCTAVE, 127},
  {99, MIDI_A3 + MIDI_OCTAVE, 127},
  {99, MIDI_B3 + MIDI_OCTAVE, 127},
  {99, MIDI_C3 + MIDI_OCTAVE, 127},
  {99, MIDI_D3 + MIDI_OCTAVE, 127},
  {99, MIDI_E3 + MIDI_OCTAVE, 127},
  {99, MIDI_F3 + MIDI_OCTAVE, 127},
  {99, MIDI_G3 + MIDI_OCTAVE, 127},
  {99, MIDI_A2 + MIDI_FLAT, 127},
  {99, MIDI_B2 + MIDI_FLAT, 127},
  {99, MIDI_D2 + MIDI_FLAT, 127},
  {99, MIDI_D2 + MIDI_FLAT, 127},
  {99, MIDI_E2 + MIDI_FLAT, 127},
  {99, MIDI_F2 + MIDI_FLAT, 127},
  {99, MIDI_G2 + MIDI_FLAT, 127},
  {99, MIDI_A3, 127},
  {99, MIDI_B3, 127}
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
      if (keysPRESSEDsequence[codeIndex][0] != 99)
      {
      midi_note_on(keysPRESSEDsequence[codeIndex][0],keysPRESSEDsequence[codeIndex][1],keysPRESSEDsequence[codeIndex][2]);
            #ifdef DEBUGKEYS
            Serial.println();
            Serial.print(keysPRESSEDsequence[codeIndex][0],DEC);
            Serial.println();
            Serial.print(keysPRESSEDsequence[codeIndex][1],DEC);
            Serial.println();
            Serial.print(keysPRESSEDsequence[codeIndex][2],DEC);
            Serial.println();
      #endif
      }
      break;
    
    
    case HOLD:
msg = " HELD ";
      #ifdef DEBUGKEYS
            Serial.print(msg );
      #endif
      //   byte channel, byte key, byte velocity
      if (keysHELDsequence[codeIndex][0] != 99)
      {
      midi_note_on(keysHELDsequence[codeIndex][0],keysHELDsequence[codeIndex][1],keysHELDsequence[codeIndex][2]);
            #ifdef DEBUGKEYS
            Serial.println();
            Serial.print(keysHELDsequence[codeIndex][0],DEC);
            Serial.println();
            Serial.print(keysHELDsequence[codeIndex][1],DEC);
            Serial.println();
            Serial.print(keysHELDsequence[codeIndex][2],DEC);
            Serial.println();
      #endif
      }
      break;
      
    case RELEASED:
      msg = " RELEASED.";
      #ifdef DEBUGKEYS
            Serial.print(msg );
      #endif
      //   byte channel, byte key, byte velocity
      if (keysRELEASEDsequence[codeIndex][0] != 99)
      {
      midi_note_on(keysRELEASEDsequence[codeIndex][0],keysRELEASEDsequence[codeIndex][1],keysRELEASEDsequence[codeIndex][2]);
            #ifdef DEBUGKEYS
            Serial.println();
            Serial.print(keysRELEASEDsequence[codeIndex][0],DEC);
            Serial.println();
            Serial.print(keysRELEASEDsequence[codeIndex][1],DEC);
            Serial.println();
            Serial.print(keysRELEASEDsequence[codeIndex][2],DEC);
            Serial.println();
      #endif
      }
      break;
    case IDLE:
      #ifdef DEBUGKEYS
            Serial.print(msg );
      #endif
      //   byte channel, byte key, byte velocity
      if (keysIDLEsequence[codeIndex][0] != 99)
      {
      midi_note_on(keysIDLEsequence[codeIndex][0],keysIDLEsequence[codeIndex][1],keysIDLEsequence[codeIndex][2]);
            #ifdef DEBUGKEYS
            Serial.println();
            Serial.print(keysIDLEsequence[codeIndex][0],DEC);
            Serial.println();
            Serial.print(keysIDLEsequence[codeIndex][1],DEC);
            Serial.println();
            Serial.print(keysIDLEsequence[codeIndex][2],DEC);
            Serial.println();
      #endif
      }
      break;
  }
}
 
void loop() {
 
  // Fills kpd.key[ ] array with up-to 10 active keys.
  // Returns true if there are ANY active keys.
  // But we don't care, because "keyEventListener" takes care of it all now.
  kpd.getKeys();
}  // End loop
