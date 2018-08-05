#include <Arduino.h>

class LED {

  private:
    int pin;

  public:
    LED(int pin) {
      this->pin = pin;
    }

    void initialize() {
      Serial.println("initializing LED on pin " + this->pin);
      pinMode(this->pin, OUTPUT);
    }
  
    void turnOn() {
      Serial.println("turning on LED at pin " + this->pin);
      digitalWrite(this->pin, HIGH);
      this->state
    }
  
    void turnOff() {
      Serial.println("turning off LED at pin " + this->pin);
      digitalWrite(this->pin, LOW);
    }

    bool isOn() {
      int state = digitalRead(this->pin);
      return state == HIGH;
    }

    bool isOff() {
      return !this->isOn();
    }

};

