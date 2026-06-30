# Pinout ESP32-WROOM DevKit con 2 nRF24L01+

Este pinout corresponde al firmware configurado en `include/hardware_pins.h`.

## Bus SPI compartido

| nRF24L01+ | ESP32-WROOM DevKit |
| --- | --- |
| VCC | 3V3 |
| GND | GND |
| SCK | GPIO18 |
| MISO | GPIO19 |
| MOSI | GPIO23 |

## nRF24 #1

| nRF24L01+ | ESP32-WROOM DevKit |
| --- | --- |
| CSN | GPIO17 |
| CE | GPIO5 |

## nRF24 #2

| nRF24L01+ | ESP32-WROOM DevKit |
| --- | --- |
| CSN | GPIO4 |
| CE | GPIO16 |

## Notas de alimentacion

- Usa solo 3V3 para VCC del nRF24L01+.
- No conectes VCC del nRF24 a 5V.
- Coloca un capacitor de 10 uF a 100 uF entre VCC y GND de cada modulo nRF24.
- Si el monitor serie muestra `FALLO`, revisa primero GND compartido, VCC estable y que MISO/MOSI no esten invertidos.

## Resultado esperado en Monitor Serie

Con ambos modulos conectados correctamente debe aparecer:

```text
nRF24 #1: OK
nRF24 #2: OK
```
