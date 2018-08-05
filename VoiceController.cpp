#include <Arduino.h>
#include <SoftwareSerial.h>
#include <SimpleVR.h>

class VoiceController {

  private:
    const static int DEFAULT_BUFFER_SIZE = 64;
    const static int SERIAL_BAUD_RATE = 9600;

    uint8_t buffer[DEFAULT_BUFFER_SIZE];
    VR vr;

    void logVersion() {
      Serial.print("checking SimpleVR version: ");
      if (vr.checkVersion(buffer) > 0){
        Serial.println("succeeded");
        
        int softwareVersionMajor = buffer[0];
        int softwareVersionMinor = buffer[1];
        int softwareVersionPatch = buffer[2];
        String softwareVersion = String(softwareVersionMajor, DEC) + "." + String(softwareVersionMinor, DEC) + "." + String(softwareVersionPatch, DEC);
        Serial.println("- software v" + softwareVersion);
    
        int hardwareVersionMajor = buffer[3];
        int hardwareVersionMinor = buffer[4];
        String hardwareVersion = String(hardwareVersionMajor, DEC) + "." + String(hardwareVersionMinor, DEC);
        Serial.println("- hardware v" + hardwareVersion);
      } else {
        Serial.println("failed");
      }
    }

    void logSettings() {
      Serial.print("checking SimpleVR settings: ");
      if (vr.checkSystemSettings(buffer) >= 0){
        Serial.println("succeeded");
        
        Serial.println(String("- is enabled? ") + String(buffer[0] ? "true" : "false"));
        Serial.println(String("- group selected: ") + buffer[1]);
    
        boolean hasThreshold = buffer[2] != 0xFF;
        Serial.println(String("- threshold value: ") + String(hasThreshold ? String(buffer[2]) : "none"));
      } else {
        Serial.println("failed");
      }
    }

    void setCommandGroup(int id) {
      Serial.print(String("setting voice command group to ") + id + String(": "));
      auto result = vr.setGroup(id);
      Serial.println(String(result >= 0 ? "succeeded" : "failed"));
    }
    
    void enableCommandGroup() {
      Serial.print(String("enabling voice command group: "));
      auto result = vr.setEnable(true);
      Serial.println(String(result >= 0 ? "succeeded" : "failed"));
    }

  public:

    /**
     * Arduino     SimpleVR
     *   RX <-------> TX
     *   TX <-------> RX
     */
    VoiceController(int rxPin, int txPin) : vr(rxPin, txPin) {}
  
    void initialize(int commandGroupID) {
      vr.begin(SERIAL_BAUD_RATE);
      logVersion();
      setCommandGroup(commandGroupID);
      enableCommandGroup();
      logSettings();
    }

    int checkForCommand() {
      int command = 0;
      auto result = vr.recognize(buffer, 50);
      if (result > 0) {
        command += buffer[0];
        command <<=8;
        command += buffer[1];
      }
      return command;
    }

};

