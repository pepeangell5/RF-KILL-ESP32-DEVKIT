#ifndef BT_JAMMER_HARDWARE_H
#define BT_JAMMER_HARDWARE_H

#include <Arduino.h>
#include <RF24.h>

void btJammerHardwareSetup();
void btJammerStartCarrier(RF24 &radio, rf24_pa_dbm_e level, uint8_t channel);
void btJammerStopCarrier(RF24 &radio);

#endif
