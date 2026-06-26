#include "bt_jammer_hardware.h"

#include <SPI.h>

#include "hardware_pins.h"

RF24 jam1(NRF24_1_CE_PIN, NRF24_1_CSN_PIN);
RF24 jam2(NRF24_2_CE_PIN, NRF24_2_CSN_PIN);

void btJammerHardwareSetup() {
  Serial.begin(115200);
  delay(800);

  pinMode(NRF24_1_CE_PIN, OUTPUT);
  pinMode(NRF24_1_CSN_PIN, OUTPUT);
  pinMode(NRF24_2_CE_PIN, OUTPUT);
  pinMode(NRF24_2_CSN_PIN, OUTPUT);

  digitalWrite(NRF24_1_CE_PIN, LOW);
  digitalWrite(NRF24_2_CE_PIN, LOW);
  digitalWrite(NRF24_1_CSN_PIN, HIGH);
  digitalWrite(NRF24_2_CSN_PIN, HIGH);

  SPI.begin(NRF24_SCK_PIN, NRF24_MISO_PIN, NRF24_MOSI_PIN);

  Serial.println("BT Jammer headless ESP32-C3 inicializado");
  Serial.println("SPI: SCK=GPIO4 MISO=GPIO5 MOSI=GPIO6");
  Serial.println("NRF1: CSN=GPIO7 CE=GPIO3");
  Serial.println("NRF2: CSN=GPIO10 CE=GPIO1");
  Serial.println("Sin pantalla, sin botones: arranque automatico.");
}

void btJammerStartCarrier(RF24 &radio, rf24_pa_dbm_e level, uint8_t channel) {
#ifdef BT_JAMMER_ENABLE_RF_TX
  radio.startConstCarrier(level, channel);
#else
  Serial.printf("SAFE MODE: RF TX bloqueado en canal %u\n", channel);
  (void)radio;
  (void)level;
#endif
}

void btJammerStopCarrier(RF24 &radio) {
#ifdef BT_JAMMER_ENABLE_RF_TX
  radio.stopConstCarrier();
#else
  (void)radio;
#endif
}
