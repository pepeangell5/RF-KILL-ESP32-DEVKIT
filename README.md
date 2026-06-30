# RF-KILL ESP32-WROOM DevKit

![PlatformIO](https://img.shields.io/badge/PlatformIO-ESP32-orange)
![Framework](https://img.shields.io/badge/Framework-Arduino-00979D)
![Board](https://img.shields.io/badge/Board-ESP32--WROOM%20DevKit-2F80ED)
![Radio](https://img.shields.io/badge/Radio-2x%20nRF24L01%2B-35C759)
![Interface](https://img.shields.io/badge/UI-Headless-8E8E93)
![License](https://img.shields.io/badge/License-MIT-black)

Proyecto de tesis basado en un ESP32-WROOM DevKit y dos modulos nRF24L01+. Esta version adapta el firmware a una ejecucion **headless**: sin pantalla, sin botones y con arranque automatico al energizar la placa desde USB, powerbank, bateria o cargador de pared.

> Uso previsto: demostracion academica, laboratorio controlado y practicas autorizadas de electronica/RF. Respeta siempre la normativa local y usa el proyecto solo en entornos permitidos.

## Indice

- [Vista General](#vista-general)
- [Caracteristicas](#caracteristicas)
- [Hardware](#hardware)
- [Conexiones](#conexiones)
- [Estructura Del Proyecto](#estructura-del-proyecto)
- [Configuracion De Pines En Codigo](#configuracion-de-pines-en-codigo)
- [Compilacion Con PlatformIO](#compilacion-con-platformio)
- [Metodos De Flasheo](#metodos-de-flasheo)
- [Web Flasher](#web-flasher)
- [Galeria](#galeria)
- [Solucion De Problemas](#solucion-de-problemas)
- [Redes Sociales](#redes-sociales)
- [Licencia](#licencia)

## Vista General

<p align="center">
  <img src="img/conexiones-devkit.jpg" width="64%" alt="Conexiones ESP32-WROOM DevKit con dos nRF24L01+">
  <img src="img/2NRF24.png" width="32%" alt="Dos modulos nRF24L01+">
</p>

[Regresar al indice](#indice)

## Caracteristicas

| Estado | Caracteristica |
| --- | --- |
| ![Auto](https://img.shields.io/badge/-AUTO-35C759) | Arranque automatico al encender el ESP32-WROOM DevKit. |
| ![OLED](https://img.shields.io/badge/-NO%20OLED-2F80ED) | Firmware sin dependencia de pantalla OLED. |
| ![Buttons](https://img.shields.io/badge/-NO%20BOTONES-FFD60A) | Firmware sin dependencia de botones fisicos. |
| ![RF](https://img.shields.io/badge/-2x%20NRF24-FF9500) | Dos nRF24L01+ en bus SPI compartido. |
| ![Serial](https://img.shields.io/badge/-SERIAL-8E44AD) | Diagnostico por Monitor Serie a `115200` baudios. |
| ![Web](https://img.shields.io/badge/-WEB%20FLASHER-FF3B30) | Web Flasher incluido para instalacion desde navegador compatible. |

[Regresar al indice](#indice)

## Hardware

| Componente | Cantidad | Notas |
| --- | ---: | --- |
| ESP32-WROOM DevKit | 1 | Placa principal del proyecto. |
| nRF24L01+ | 2 | Modulos RF conectados al mismo bus SPI. |
| Capacitor 10 uF a 100 uF | 2 | Recomendado entre VCC y GND de cada nRF24. |
| Jumpers Dupont | Varios | Para SPI, CE, CSN, 3V3 y GND. |
| Fuente USB / powerbank | 1 | Alimentacion de la placa. |

<p align="center">
  <img src="img/esp32U.png" width="38%" alt="ESP32-WROOM DevKit">
  <img src="img/NRF24.png" width="25%" alt="Modulo nRF24L01+">
  <img src="img/2NRF24.png" width="25%" alt="Dos modulos nRF24L01+">
</p>

[Regresar al indice](#indice)

## Conexiones

Los dos nRF24L01+ comparten `SCK`, `MISO` y `MOSI`. Cada modulo usa su propio `CE` y `CSN`.

| Senal nRF24L01+ | ESP32-WROOM DevKit | Uso |
| --- | --- | --- |
| VCC | 3V3 | Alimentacion del modulo. |
| GND | GND | Tierra comun. |
| SCK | GPIO18 | SPI Clock compartido. |
| MISO | GPIO19 | SPI MISO compartido. |
| MOSI | GPIO23 | SPI MOSI compartido. |
| CSN nRF24 #1 | GPIO17 | Chip Select del modulo 1. |
| CE nRF24 #1 | GPIO5 | Chip Enable del modulo 1. |
| CSN nRF24 #2 | GPIO4 | Chip Select del modulo 2. |
| CE nRF24 #2 | GPIO16 | Chip Enable del modulo 2. |

```mermaid
flowchart LR
  ESP["ESP32-WROOM DevKit"]
  R1["nRF24L01+ #1"]
  R2["nRF24L01+ #2"]

  ESP -- "3V3" --> R1
  ESP -- "GND" --> R1
  ESP -- "GPIO18 / SCK" --> R1
  ESP -- "GPIO19 / MISO" --> R1
  ESP -- "GPIO23 / MOSI" --> R1
  ESP -- "GPIO17 / CSN" --> R1
  ESP -- "GPIO5 / CE" --> R1

  ESP -- "3V3" --> R2
  ESP -- "GND" --> R2
  ESP -- "GPIO18 / SCK" --> R2
  ESP -- "GPIO19 / MISO" --> R2
  ESP -- "GPIO23 / MOSI" --> R2
  ESP -- "GPIO4 / CSN" --> R2
  ESP -- "GPIO16 / CE" --> R2
```

<p align="center">
  <img src="img/conexiones-devkit.jpg" width="78%" alt="Diagrama de conexiones ESP32-WROOM DevKit con dos nRF24L01+">
  <br>
  <img src="img/Pines-NRF24.png" width="45%" alt="Pinout nRF24L01+">
</p>

[Regresar al indice](#indice)

## Estructura Del Proyecto

```text
.
|-- binarios/
|   |-- boot_app0.bin
|   |-- bootloader.bin
|   |-- firmware.bin
|   |-- partitions.bin
|   `-- rf-kill-esp32-devkit-web-v2.bin
|-- include/
|   |-- bt_jammer.h
|   |-- bt_jammer_hardware.h
|   `-- hardware_pins.h
|-- img/
|-- src/
|   |-- bt_jammer.cpp
|   |-- bt_jammer_hardware.cpp
|   `-- main.cpp
|-- index.html
|-- manifest.json
|-- platformio.ini
`-- README.md
```

[Regresar al indice](#indice)

## Configuracion De Pines En Codigo

Los pines usados por el firmware se encuentran en `include/hardware_pins.h`.

```cpp
static const uint8_t NRF24_SCK_PIN = 18;
static const uint8_t NRF24_MISO_PIN = 19;
static const uint8_t NRF24_MOSI_PIN = 23;

static const uint8_t NRF24_1_CSN_PIN = 17;
static const uint8_t NRF24_1_CE_PIN = 5;

static const uint8_t NRF24_2_CSN_PIN = 4;
static const uint8_t NRF24_2_CE_PIN = 16;
```

[Regresar al indice](#indice)

## Compilacion Con PlatformIO

Requisitos:

- Visual Studio Code
- Extension PlatformIO
- Cable USB de datos
- ESP32-WROOM DevKit

Compilar:

```bash
pio run
```

Subir por USB:

```bash
pio run --target upload
```

Monitor Serie:

```bash
pio device monitor --baud 115200
```

[Regresar al indice](#indice)

## Metodos De Flasheo

### 1. PlatformIO

Metodo recomendado durante desarrollo:

```bash
pio run --target upload
```

### 2. Web Flasher

El repositorio incluye `index.html`, `manifest.json` y los binarios necesarios en `binarios/`.

Cuando el repositorio este publicado en GitHub Pages, el instalador quedara disponible en:

[https://pepeangell5.github.io/RF-KILL-ESP32-DEVKIT/](https://pepeangell5.github.io/RF-KILL-ESP32-DEVKIT/)

Pasos:

1. Abre el enlace en Chrome o Edge de escritorio.
2. Conecta el ESP32-WROOM DevKit por USB.
3. Presiona **Instalar firmware**.
4. Selecciona el puerto serial del ESP32.
5. Espera a que termine el flasheo.

### 3. esptool.py

Tambien puedes flashear manualmente con los binarios incluidos:

```bash
esptool.py --chip esp32 --baud 460800 write_flash -z \
  0x1000 binarios/bootloader.bin \
  0x8000 binarios/partitions.bin \
  0xe000 binarios/boot_app0.bin \
  0x10000 binarios/firmware.bin
```

Offsets usados por el Web Flasher:

| Archivo | Offset |
| --- | ---: |
| `rf-kill-esp32-devkit-web-v2.bin` | `0x0` |

[Regresar al indice](#indice)

## Web Flasher

El archivo `manifest.json` apunta a:

```json
{
  "chipFamily": "ESP32",
  "parts": [
    { "path": "binarios/rf-kill-esp32-devkit-web-v2.bin", "offset": 0 }
  ]
}
```


[Regresar al indice](#indice)

## Galeria

<p align="center">
  <img src="img/conexiones-devkit.jpg" width="58%" alt="Conexiones ESP32-WROOM DevKit">
  <img src="img/esp32U.png" width="36%" alt="ESP32-WROOM DevKit">
</p>

[Regresar al indice](#indice)

## Solucion De Problemas

| Problema | Revision recomendada |
| --- | --- |
| El ESP32 no aparece en el navegador | Usa Chrome/Edge de escritorio y un cable USB de datos. |
| PlatformIO no detecta la placa | Revisa driver USB, puerto COM y cable. |
| nRF24 muestra `FALLO` | Revisa 3V3, GND comun, MISO/MOSI y capacitores. |
| Reinicios al arrancar | Usa alimentacion estable y capacitores cerca de cada nRF24. |
| Web Flasher no descarga binarios | Verifica que GitHub Pages publique `binarios/` y `manifest.json`. |

[Regresar al indice](#indice)

## Redes Sociales

| Red | Enlace |
| --- | --- |
| Facebook | <a href="https://www.facebook.com/esp32-tools" target="_blank" rel="noopener noreferrer">esp32-tools</a> |
| Instagram | <a href="https://www.instagram.com/pepeangelll/" target="_blank" rel="noopener noreferrer">pepeangelll</a> |
| YouTube | <a href="https://www.youtube.com/@esp32-tools" target="_blank" rel="noopener noreferrer">esp32-tools</a> |
| Pagina web | <a href="https://pepeangell.dev" target="_blank" rel="noopener noreferrer">pepeangell.dev</a> |

[Regresar al indice](#indice)

## Licencia

Este proyecto se distribuye bajo licencia MIT. Consulta `LICENSE` para mas detalles.

[Regresar al indice](#indice)
