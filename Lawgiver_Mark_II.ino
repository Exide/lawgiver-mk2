#include "LED.cpp"
#include "Button.cpp"
#include "VoiceController.cpp"

const long SERIAL_BAUD_RATE = 115200;

const int BARREL_LED_COUNT = 5;
const int BARREL_LED_0_PIN = 8;
const int BARREL_LED_1_PIN = 10;
const int BARREL_LED_2_PIN = 11;
const int BARREL_LED_3_PIN = 12;
const int BARREL_LED_4_PIN = 13;

const int DNA_SUCCESS_LED_PIN = 4;
const int DNA_FAILURE_LED_PIN = 2;

const int TRIGGER_PIN = 15;
const int SLIDE_PIN = 6;
const int SPEAKER_PIN = 7;
const int TARGETING_SENSOR_PIN = 9;

const int VOICE_RX_PIN = 2;
const int VOICE_TX_PIN = 3;
const int VOICE_COMMAND_GROUP = 1;
const int VOICE_COMMAND_DEBUG = 0x1;
const int VOICE_COMMAND_GRENADE = 0x2;
const int VOICE_COMMAND_RAPID_FIRE = 0x3;
const int VOICE_COMMAND_ARMOR_PIERCING = 0x4;
const int VOICE_COMMAND_SIGNAL_FLARE = 0x5;
const int VOICE_COMMAND_DOUBLE_WHAMMY = 0x6;

// ------------------------------------------------------

LED barrelLEDs[] = {
  BARREL_LED_0_PIN,
  BARREL_LED_1_PIN,
  BARREL_LED_2_PIN,
  BARREL_LED_3_PIN,
  BARREL_LED_4_PIN
};

Button trigger(TRIGGER_PIN);
LED slide(SLIDE_PIN);
LED speaker(SPEAKER_PIN);
LED targetingSensor(TARGETING_SENSOR_PIN);
VoiceController voiceController(VOICE_RX_PIN, VOICE_TX_PIN);

// ------------------------------------------------------

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);

  for (auto i = 0; i < BARREL_LED_COUNT; i++) {
    barrelLEDs[i].initialize();
  }

  trigger.initialize();
  slide.initialize();
  speaker.initialize();
  targetingSensor.initialize();
  voiceController.initialize(VOICE_COMMAND_GROUP);
}

void loop() {
  if (trigger.isPressed()) {
    slide.turnOn();
  } else {
    slide.turnOff();
  }

  for (auto i = 0; i < BARREL_LED_COUNT; i++) {
    if (barrelLEDs[i].isOff()) {
      barrelLEDs[i].turnOn();
    }
  }

  int command = voiceController.checkForCommand();
  if (command != 0) {
    parseCommand(command);
  }
}

void parseCommand(int command) {
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
      Serial.println("voice command: unknown");
  }
}

