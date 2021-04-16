/*
    This file is part of ttymidi.

    ttymidi is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ttymidi is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ttymidi.  If not, see <http://www.gnu.org/licenses/>.
*/
// file version 0.60

#ifndef ardumidi_h
#define ardumidi_h

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
#include "WProgram.h"
#endif

// MIDI notes
#define MIDI_A0            21
#define MIDI_B0            22

#define MIDI_C1            24
#define MIDI_D1            26
#define MIDI_E1            28
#define MIDI_F1            29
#define MIDI_G1            31
#define MIDI_A1            33
#define MIDI_B1            35

#define MIDI_C2            36
#define MIDI_D2            38
#define MIDI_E2            40
#define MIDI_F2            41
#define MIDI_G2            43
#define MIDI_A2            45
#define MIDI_B2            47


#define MIDI_C3            48
#define MIDI_D3            50
#define MIDI_E3            52
#define MIDI_F3            53
#define MIDI_G3            55
#define MIDI_A3            57
#define MIDI_B3            59




#define MIDI_C4            60
#define MIDI_D4            62
#define MIDI_E4            64
#define MIDI_F4            65
#define MIDI_G4            67
#define MIDI_A4            69
#define MIDI_B4            71


#define MIDI_SHARP         1
#define MIDI_FLAT         -1
#define MIDI_OCTAVE       12

// MIDI out
#define MIDI_NOTE_OFF          0x80
#define MIDI_NOTE_ON           0x90
#define MIDI_PRESSURE          0xA0
#define MIDI_CONTROLLER_CHANGE 0xB0
#define MIDI_PROGRAM_CHANGE    0xC0
#define MIDI_CHANNEL_PRESSURE  0xD0
#define MIDI_PITCH_BEND        0xE0

struct MidiMessage {
	byte command;
	byte channel;
	byte param1;
	byte param2;
};

// MIDI in
void midi_note_off(byte channel, byte key, byte velocity);
void midi_note_on(byte channel, byte key, byte velocity);
void midi_key_pressure(byte channel, byte key, byte value);
void midi_controller_change(byte channel, byte control, byte value);
void midi_program_change(byte channel, byte program);
void midi_channel_pressure(byte channel, byte value);
void midi_pitch_bend(byte channel, int value);
void midi_command(byte command, byte channel, byte param1, byte param2);
void midi_command_short(byte command, byte channel, byte param1);

// MIDI out
int midi_message_available();
MidiMessage read_midi_message();
int get_pitch_bend(MidiMessage msg);

// Other 
void midi_print(char* msg, int len);
void midi_comment(char* msg);

#endif
