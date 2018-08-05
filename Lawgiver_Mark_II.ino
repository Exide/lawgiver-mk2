#include <SoftwareSerial.h>
#include <SimpleVR.h>
#include "LED.cpp"

class Button {

  private:
    

  public:
    

};

const long SERIAL_BAUD_RATE = 115200;

//const int BARREL_LED_COUNT = 5;
//const int BARREL_LED_0_PIN = 8;
//const int BARREL_LED_1_PIN = 10;
//const int BARREL_LED_2_PIN = 11;
//const int BARREL_LED_3_PIN = 12;
//const int BARREL_LED_4_PIN = 13;

//const int DNA_SUCCESS_BUTTON_PIN = 14;
//const int DNA_SUCCESS_LED_PIN = 4;

//const int DNA_FAILURE_BUTTON_PIN = 19;
//const int DNA_FAILURE_LED_PIN = 2;

//const int TRIGGER_PIN = 15;
//const int SLIDE_PIN = 6; // green

//const int TARGETING_SENSOR_PIN = 9; // white
//const int SPEAKER_PIN = 7; // yellow

//const int BUTTON_PRESSED = 0; // inverted due to pullup resistor

const int VOICE_RX_PIN = 2;
const int VOICE_TX_PIN = 3;
const int VOICE_BAUD_RATE = 9600;
const int VOICE_BUFFER_SIZE = 64;
const int VOICE_COMMAND_GROUP = 1;
const int VOICE_COMMAND_DEBUG = 0x1;
const int VOICE_COMMAND_GRENADE = 0x2;
const int VOICE_COMMAND_RAPID_FIRE = 0x3;
const int VOICE_COMMAND_ARMOR_PIERCING = 0x4;
const int VOICE_COMMAND_SIGNAL_FLARE = 0x5;
const int VOICE_COMMAND_DOUBLE_WHAMMY = 0x6;

//LED barrelLEDs[] = {
//  BARREL_LED_0_PIN,
//  BARREL_LED_1_PIN,
//  BARREL_LED_2_PIN,
//  BARREL_LED_3_PIN,
//  BARREL_LED_4_PIN
//};

VR voiceRecognition(VOICE_RX_PIN, VOICE_TX_PIN);
uint8_t voiceBuffer[VOICE_BUFFER_SIZE];

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);

//  for (auto i = 0; i < BARREL_LED_COUNT; i++) {
//    barrelLEDs[i].initialize();
//  }

//  pinMode(DNA_SUCCESS_LED_PIN, OUTPUT);
//  pinMode(DNA_FAILURE_LED_PIN, OUTPUT);
//  pinMode(SLIDE_PIN, OUTPUT);
//  pinMode(SPEAKER_PIN, OUTPUT);
//  pinMode(TARGETING_SENSOR_PIN, OUTPUT);

//  pinMode(DNA_SUCCESS_BUTTON_PIN, INPUT_PULLUP);
//  pinMode(DNA_FAILURE_BUTTON_PIN, INPUT_PULLUP);
//  pinMode(TRIGGER_PIN, INPUT_PULLUP);

  initializeVR();
}

void initializeVR() {
  voiceRecognition.begin(VOICE_BAUD_RATE);

  if (voiceRecognition.checkVersion(voiceBuffer) > 0){
    int vrSoftwareVersionMajor = voiceBuffer[0];
    int vrSoftwareVersionMinor = voiceBuffer[1];
    int vrSoftwareVersionPatch = voiceBuffer[2];
    String vrSoftwareVersion = String(vrSoftwareVersionMajor, DEC) + "." + String(vrSoftwareVersionMinor, DEC) + "." + String(vrSoftwareVersionPatch, DEC);
    int vrHardwareVersionMajor = voiceBuffer[3];
    int vrHardwareVersionMinor = voiceBuffer[4];
    String vrHardwareVersion = String(vrHardwareVersionMajor, DEC) + "." + String(vrHardwareVersionMinor, DEC);

    Serial.println("SimpleVR detected");
    Serial.println("software version: " + vrSoftwareVersion);
    Serial.println("hardware version: " + vrHardwareVersion);
  } else {
    Serial.println("error checking voice recognition software and hardware versions");
  }

  Serial.print(String("setting voice command group to ") + VOICE_COMMAND_GROUP + String(": "));
  if (voiceRecognition.setGroup(VOICE_COMMAND_GROUP) >= 0){
    Serial.println("succeeded");
  } else {
    Serial.println("failed");
  }

  Serial.print(String("enabling voice command group: "));
  if (voiceRecognition.setEnable(true) >= 0){
    Serial.println("succeeded");
  } else {
    Serial.println("failed");
  }

  Serial.println("checking SimpleVR settings...");
  if (voiceRecognition.checkSystemSettings(voiceBuffer) >= 0){
    boolean vrIsEnabled = voiceBuffer[0];
    int vrGroup = voiceBuffer[1];
    boolean vrHasThreshold = voiceBuffer[2] != 0xFF;
    int vrThreshold = vrHasThreshold ? voiceBuffer[2] : 0;

    Serial.println(String("is enabled? ") + String(vrIsEnabled ? "true" : "false"));
    Serial.println(String("group selected: ") + vrGroup);
    Serial.println(String("threshold value: ") + String(vrHasThreshold ? String(vrThreshold) : "none"));
  } else {
    Serial.println("error checking voice recognition system settings");
  }
}

void loop() {
//  int triggerButton = digitalRead(TRIGGER_PIN);
//  int dnaSuccessButton = digitalRead(DNA_SUCCESS_BUTTON_PIN);
//  int dnaFailButton = digitalRead(DNA_FAILURE_BUTTON_PIN);

//  if (triggerButton == BUTTON_PRESSED) {
//    Serial.println("trigger button pressed");
//    digitalWrite(SLIDE_PIN, HIGH);
//  } else {
//    digitalWrite(SLIDE_PIN, LOW);
//  }

//  if (dnaSuccessButton == BUTTON_PRESSED) {
//    Serial.println("dna success button pressed");
//    digitalWrite(DNA_SUCCESS_LED_PIN, HIGH);
//  } else {
//    digitalWrite(DNA_SUCCESS_LED_PIN, LOW);
//  }
  
//  if (dnaFailButton == BUTTON_PRESSED) {
//    Serial.println("dna failure button pressed");
//    digitalWrite(DNA_FAILURE_LED_PIN, HIGH);
//  } else {
//    digitalWrite(DNA_FAILURE_LED_PIN, LOW);
//  }

//  for (auto i = 0; i < BARREL_LED_COUNT; i++) {
//    if (barrelLEDs[i].isOff()) {
//      barrelLEDs[i].turnOn();
//    }
//  }

  if (voiceRecognition.recognize(voiceBuffer, 50) > 0) {
    uint16_t command = 0;
    command += voiceBuffer[0];
    command <<=8;
    command += voiceBuffer[1];
    Serial.println(String("voice command received: ") + command);

    switch (command) {

      case VOICE_COMMAND_DEBUG:
        Serial.println("voice command: debug");
        break;
        
      case VOICE_COMMAND_GRENADE:
        Serial.println("voice command: grenade");
        break;
        
      case VOICE_COMMAND_RAPID_FIRE:
        Serial.println("voice command: rapid fire");
        break;
        
      case VOICE_COMMAND_ARMOR_PIERCING:
        Serial.println("voice command: armor piercing");
        break;
        
      case VOICE_COMMAND_SIGNAL_FLARE:
        Serial.println("voice command: signal flare");
        break;
        
      case VOICE_COMMAND_DOUBLE_WHAMMY:
        Serial.println("voice command: double whammy");
        break;
        
      default:
        Serial.println("unknown command");
    }
  }
}

