#include <Arduino.h>

class LED {

  private:
    int pin;
    bool state;

  public:
    LED(int pin) {
      this->pin = pin;
      this->state = false;
    }

    ~LED() {
      this->state = false;
    }
      
    void initialize() {
      Serial.println("initializing LED on pin " + this->pin);
      pinMode(this->pin, OUTPUT);
    }
  
    void turnOn() {
      Serial.println("turning on LED at pin " + this->pin);
      digitalWrite(this->pin, HIGH);
    }
  
    void turnOff() {
      Serial.println("turning off LED at pin " + this->pin);
      digitalWrite(this->pin, LOW);
    }

    bool isOn() {
      return this->state;
    }

    bool isOff() {
      return !this->isOn();
    }

};

