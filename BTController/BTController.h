#ifndef LIBRARIES_BTCONTROLLER_BTCONTROLLER_H_
#define LIBRARIES_BTCONTROLLER_BTCONTROLLER_H_

#include "SoftwareSerial.h"

class BTController {
    public:
        BTController(int rx, int tx);
        BTController(int rx, int tx, int baudRate);
        bool read();
        String getValue();

    private:
        enum State {
            START, KEY, EQUALS, VALUE
        };

        int baudRate;
        SoftwareSerial serial;
        State state;
        String value;
};

#endif /* LIBRARIES_BTCONTROLLER_BTCONTROLLER_H_ */
