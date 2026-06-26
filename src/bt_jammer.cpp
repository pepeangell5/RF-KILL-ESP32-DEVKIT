#include "bt_jammer.h"
#include <RF24.h>
#include "bt_jammer_hardware.h"

extern RF24 jam1;
extern RF24 jam2;

bool isBtJamming = false;
byte hopping_channel[] = { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80 };
int total_bt_chans = sizeof(hopping_channel);

void btJammerSetup() {
    jam1.begin(); jam2.begin();
    jam1.setAutoAck(false); jam1.setPALevel(RF24_PA_MAX, true);
    jam1.setDataRate(RF24_1MBPS); jam1.setCRCLength(RF24_CRC_DISABLED);
    jam2.setAutoAck(false); jam2.setPALevel(RF24_PA_MAX, true);
    jam2.setDataRate(RF24_1MBPS); jam2.setCRCLength(RF24_CRC_DISABLED);

    Serial.println("BT jammer headless iniciado");
    Serial.printf("nRF24 #1: %s\n", jam1.isChipConnected() ? "OK" : "FALLO");
    Serial.printf("nRF24 #2: %s\n", jam2.isChipConnected() ? "OK" : "FALLO");

    isBtJamming = true;
    btJammerStartCarrier(jam1, RF24_PA_MAX, hopping_channel[0]);
    btJammerStartCarrier(jam2, RF24_PA_MAX, hopping_channel[total_bt_chans - 1]);
}

void btJammerLoop() {
    if (isBtJamming) {
        while (isBtJamming) {
            for (int i = 0; i < total_bt_chans; i++) {
                jam1.setChannel(hopping_channel[i]);
                jam2.setChannel(hopping_channel[total_bt_chans - 1 - i]);
            }
        }
    }
}
