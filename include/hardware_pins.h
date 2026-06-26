#ifndef HARDWARE_PINS_H
#define HARDWARE_PINS_H

#include <Arduino.h>

// ESP32-C3 SuperMini + two nRF24L01+ modules.
// Both radios share the SPI bus. Each radio needs its own CE and CSN.
static const uint8_t NRF24_SCK_PIN = 4;
static const uint8_t NRF24_MISO_PIN = 5;
static const uint8_t NRF24_MOSI_PIN = 6;

static const uint8_t NRF24_1_CSN_PIN = 7;
static const uint8_t NRF24_1_CE_PIN = 3;

static const uint8_t NRF24_2_CSN_PIN = 10;
static const uint8_t NRF24_2_CE_PIN = 1;

#endif
