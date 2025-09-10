#include "laser_security.h"

void setup() {
    securityInit();
}

void loop() {
    checkLaserSecurity();
    delay(100);
}
