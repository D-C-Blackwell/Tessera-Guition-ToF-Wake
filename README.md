# Tessera Guition ToF Wake

A Tessera plugin for the Guition ESP32-S3-4848S040 display. A VL53L0X proximity sensor wakes the screen locally when
somebody approaches. Home Assistant receives one occupancy entity.

## Status

Beta. The sensor, local wake action and 1 m default distance were tested with a Guition 4-inch display. Plugin
installation still requires a screen build and hardware test.

## Hardware

- Guition ESP32-S3-4848S040 display running Tessera
- VL53L0X ToF breakout board
- Fine insulated wire
- Precision soldering equipment and magnification

The sensor shares the GT911 touchscreen I2C bus:

| VL53L0X | Guition | Function |
| --- | --- | --- |
| SDA | GPIO19 | I2C data |
| SCL | GPIO45 | I2C clock |
| GND | GND | Common ground |
| VIN | Compatible supply | Check the breakout board specification |

Confirm the board revision and supply voltage before soldering.

## Set up

1. Open **Plugins** in Tessera.
2. Choose **Add with a link**.
3. Enter `https://github.com/D-C-Blackwell/Tessera-Guition-ToF-Wake`.
4. Add **Guition ToF wake** to the Guition screen.
5. Build and install the screen firmware.
6. Hold the top bar and open **Settings**, **Plugins**, **ToF wake**.
7. Set the wake distance. The default is 100 cm.

The screen samples distance every 500 ms. Raw values remain internal. Home Assistant receives only detected and
cleared changes from **Screen approach**. The screen stays awake while approach remains detected.

## Existing local YAML

Remove the ToF blocks from `<screen-name>.local.yaml` before installing the plugin. Do not configure the same sensor,
I2C address or ESPHome IDs twice. Keep unrelated local settings, including relay definitions.

The previous local-YAML example remains in [`examples/tessera-tof.local.yaml`](examples/tessera-tof.local.yaml).

## Mounting

The sensor needs a clear optical path. A fixed reading near 0.04 m usually means the enclosure or cover is reflecting
the beam. Test the sensor outside the enclosure before final assembly.

## Safety

This modification requires fine soldering on the display PCB. Disconnect USB and mains power first. Inspect all joints
under magnification and check continuity before reconnecting power. Some Guition wallbox bases carry mains voltage.

## Licence

Released under the [MIT License](LICENSE).
