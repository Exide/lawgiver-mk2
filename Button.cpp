#include <Arduino.h>

class Button {

  private:
    int pin;

  public:
    Button(int pin) {
      this->pin = pin;
    }

    void initialize() {
      Serial.println("initializing Button on pin " + this->pin);
      pinMode(this->pin, INPUT_PULLUP);
    }

    boolean isPressed() {
      int state = digitalRead(this->pin);
      return state == HIGH;
    }

};

