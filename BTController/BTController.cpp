#include "Arduino.h"
#include "BTController.h"

BTController::BTController(int rx, int tx) :
        BTController(rx, tx, 9600) {
}

BTController::BTController(int rx, int tx, int baudRate) :
        serial(rx, tx) {
    this->baudRate = baudRate;
    this->state = START;
    serial.begin(baudRate);
}

bool BTController::read() {
    bool success = false;
    String newValue = String("");
    this->value = String("");

    while (serial.available()) {
        char c = serial.read();

        switch (state) {
            case START:
                if (c == '#') {
                    state = KEY;
                }
                break;
            case KEY:
                // we only support buttons now, no gyroscope,
                // so we wait until we get it
                if (c == 'b') {
                    state = EQUALS;
                }
                break;
            case EQUALS:
                if (c == '=') {
                    state = VALUE;
                }
                break;
            case VALUE:
                // we are finished with the value,
                // store it if we have some and get back to start
                if (c == '#' && newValue.length() > 0) {
                    state = START;
                    this->value = newValue;
                    success = true;
                } else {
                    newValue += String(c);
                }
                break;
        }
    }

    return success;
}

String BTController::getValue() {
    return value;
}
