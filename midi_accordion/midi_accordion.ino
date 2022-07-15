/*
  MIDI Accordion
  by Nathan Douglas <github@tenesm.us>
*/

#include <SoftwareSerial.h>

// Uncomment this line to print serial messages.
// #define DEBUG

const char midiPin = 3;
const char leftHandPins[] = { 7, 6, 5 };
const char rightHandPins[] = { 13, 12, 11, 10, 9, 8 };
const char noteOnCommand = 0x90;
const char noteOffCommand = 0x80;
const char leftHandChannel = 0;
const char rightHandChannel = 0;

int leftHandStatus[] = {
  B0000000,
  B0000000,
  B0000000,
};

int rightHandStatus[] = {
  B0000000,
  B0000000,
  B0000000,
  B0000000,
  B0000000,
  B0000000, 
};

const char leftHandNotes[][8] = {
  { 38, 39, 40, 41, 50, 51, 52, 53, },  // 7
  { 46, 47, 36, 37, 58, 59, 48, 49, },  // 6
  { 42, 43, 44, 45, 54, 55, 56, 57, },  // 5
};

const char rightHandNotes[][8] = {
  {65,64,62,60,59,57,55,53},  // 13
  {79,77,76,74,72,71,69,67},  // 12
  {70,68,66,63,61,58,56,54},  // 11
  {93,91,89,88,86,84,83,81},  // 10
  {90,87,85,82,80,78,75,73},  // 09
  {92,0,0,0,0,0,0,0}          // 08
};
SoftwareSerial midiSerial(2, midiPin);

void setup() {
  #ifdef DEBUG
    Serial.begin(115200);
  #endif
  for (int i = 0; i < sizeof(leftHandPins); i++) {
    pinMode(leftHandPins[i], OUTPUT);
    digitalWrite(leftHandPins[i], LOW);
    pinMode(leftHandPins[i], INPUT);
  }
  for (int i = 0; i < sizeof(rightHandPins); i++) {
    pinMode(rightHandPins[i], OUTPUT);
    digitalWrite(rightHandPins[i], LOW);
    pinMode(rightHandPins[i], INPUT);
  }
  // Pins 07-00 (Left Hand)
  DDRD = B00000000;
  PORTD = B11111111;
  // Pins 13-08 (Right Hand)
  DDRB = B00000000;
  PORTB = B11111111;
  pinMode(midiPin, OUTPUT);
  midiSerial.begin(31250);
}

void loop() {
  int button1State, button2State;
  button1State = digitalRead(rightHandPins[0]);
  button2State = digitalRead(rightHandPins[1]);
  if (button1State == LOW) {
    sendMidiCommand(0x90, 61, 127);
  } else {
    sendMidiCommand(0x80, 61, 127);
  }
  if (button2State == LOW) {
    sendMidiCommand(0x90, 72, 127);
  } else {
    sendMidiCommand(0x80, 72, 127);
  }
}

// Sends a MIDI command.
void sendMidiCommand(int cmd, int pitch, int velocity) {
  midiSerial.write(cmd);
  midiSerial.write(pitch);
  midiSerial.write(velocity);
  #ifdef DEBUG
    Serial.print("cmd: ");
    Serial.print(cmd);
    Serial.print(", pitch: ");
    Serial.print(pitch);
    Serial.print(", velocity: ");
    Serial.println(velocity);
  #endif
}
