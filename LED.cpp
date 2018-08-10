#include <Arduino.h>

class LED {

  private:
    int pin;

  public:
    LED(int pin) {
      this->pin = pin;
    }

    void initialize() {
      Serial.println(String("initializing LED on pin ") + this->pin);
      pinMode(this->pin, OUTPUT);
    }
  
    void turnOn() {
      Serial.println(String("turning on LED at pin ") + this->pin);
      digitalWrite(this->pin, HIGH);
    }
  
    void turnOff() {
      Serial.println(String("turning off LED at pin ") + this->pin);
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

