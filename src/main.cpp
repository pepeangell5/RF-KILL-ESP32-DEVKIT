#include <Arduino.h>
#include "bt_jammer.h"
#include "bt_jammer_hardware.h"

void setup() {
  btJammerHardwareSetup();
  btJammerSetup();
}

void loop() {
  btJammerLoop();
}
