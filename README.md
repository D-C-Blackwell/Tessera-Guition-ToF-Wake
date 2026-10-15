# Tessera Guition ToF Wake

ESPHome configuration for adding a VL53L0X Time-of-Flight proximity sensor to a
Guition ESP32-S3-4848S040 display running
[Tessera](https://github.com/MaxGramser/homeassistant_espscreen).

The sensor wakes the display locally when somebody approaches. Home Assistant
receives an occupancy entity and a slower diagnostic distance reading, but it is
not responsible for the wake action.

## Project status

This is an experimental hardware project.

- Confirmed: the VL53L0X communicates when sharing the Guition's existing GT911
  touchscreen I2C bus.
- Confirmed: approach detection and display wake run locally on the ESP32.
- Still being validated: permanent optical mounting that avoids enclosure
  reflections and false short-distance readings.

Test the sensor outside the enclosure before relying on it in a finished wall
installation.

## Hardware

- Guition ESP32-S3-4848S040, 480 x 480 display
- Tessera firmware
- VL53L0X ToF sensor breakout
- Suitable wiring and mounting hardware

## Required skills and tools

This modification requires soldering directly to small points on the Guition
PCB. It is intended for people who already have experience with fine-pitch
electronics soldering and board-level inspection.

The working prototype was assembled using a precision, temperature-controlled
soldering iron and a microscope. Recommended equipment includes:

- Fine soldering-iron tip
- Electronics microscope or strong magnification
- Fine insulated wire
- Suitable flux and fine-gauge solder
- Multimeter for continuity and voltage checks
- ESD-safe working area

Incorrect soldering can lift pads, bridge adjacent signals or permanently
damage the display, ESP32, touchscreen or sensor. Do not attempt the modification
without the tools and experience needed to identify and inspect the connections.

## Wiring

The VL53L0X shares the existing GT911 touchscreen I2C bus:

| VL53L0X | Guition | Function |
| --- | --- | --- |
| SDA | GPIO19 | I2C data |
| SCL | GPIO45 | I2C clock |
| GND | GND | Common ground |
| VIN | Compatible supply | Check the requirements of your breakout board |

The exact solder points may differ between Guition board revisions. Confirm the
board revision and connections before applying power.

Important pin notes:

- This project does not use the P1 UART connector as an I2C bus. GPIO43 and
  GPIO44 did not communicate reliably with the sensor in the test installation.
- Do not use GPIO8 or GPIO9. They carry green-channel RGB display data on this
  board.
- GPIO45 is a strapping pin; the supplied configuration retains Tessera's
  existing handling for it.

## Configuration

The ready-to-copy configuration is in
[`examples/tessera-tof.local.yaml`](examples/tessera-tof.local.yaml).

Merge it into the local file belonging to your Tessera screen:

```text
/config/esphome/<your-screen-name>.local.yaml
```

For example:

```text
/config/esphome/lcd-panel.local.yaml
```

Preserve other local configuration already present in that file, such as relay
definitions. Do not compile the `.local.yaml` file directly. Tessera's main
screen configuration includes it and is the file that must be compiled:

```text
/config/esphome/<your-screen-name>.yaml
```

The main YAML normally contains an include similar to:

```yaml
packages:
  local: !include lcd-panel.local.yaml
```

The key name may differ, but the included filename must match your screen.

## How it works

- The VL53L0X samples locally every 500 ms.
- Approach activates at 0.50 m or closer.
- It remains active until the measured distance exceeds 0.65 m.
- The separate activation and release distances prevent rapid switching around
  the threshold.
- Tessera's local `wake_button` wakes the display without a Home Assistant
  automation or network round-trip.
- While somebody remains nearby, Tessera's standby timer is refreshed every
  five seconds.
- The diagnostic distance entity is published to Home Assistant every five
  seconds, avoiding unnecessary recorder traffic while preserving responsive
  local detection.

Change the `0.50f` and `0.65f` values in the example if different activation and
release distances are required.

## Installation

1. Disconnect mains and USB power before opening or wiring the display.
2. Connect the sensor to the shared I2C bus.
3. Merge the example into `<your-screen-name>.local.yaml`.
4. Open `<your-screen-name>.yaml` in ESPHome Builder.
5. Validate the complete configuration.
6. Compile and install it over OTA or USB.
7. Confirm the logs detect I2C address `0x29`.
8. Check the raw distance with the sensor outside the enclosure.
9. Test standby, approach wake and release before final mounting.

A Home Assistant restart is not required.

## Optical mounting

The VL53L0X needs an unobstructed optical path. A constant reading around
`0.040-0.050 m` generally means it is seeing the enclosure, protective material
or internal reflections rather than the room.

- Ensure both optical windows face outward.
- Remove protective film.
- Do not place ordinary glass or plastic directly over the sensor.
- Keep the enclosure outside its field of view.
- Consider a black foam gasket or divider to reduce optical crosstalk.
- Validate readings before securing the sensor permanently.

Changing the software threshold does not correct a permanently obstructed
sensor.

## Troubleshooting

### Distance remains unknown

Check the ESPHome logs for address `0x29`. If it is absent, verify power, ground,
SDA, SCL, solder joints and the breakout board's voltage requirements.

### Distance is always approximately 4-5 cm

Move the sensor outside the enclosure and point it into open space. If the value
then changes, correct its position or optical isolation before mounting it.

### Touchscreen stops working

Ensure the local YAML still defines `touch_bus` with GPIO19 as SDA and GPIO45 as
SCL. Tessera's GT911 touchscreen and the VL53L0X must both reference that bus.

### Display colours or image become corrupted

Disconnect the sensor and verify it has not been attached to GPIO8 or GPIO9.
Those pins are part of the RGB display interface.

## Compatibility

The configuration currently depends on Tessera's internal IDs:

- `touch_bus`
- `wake_button`
- `last_touch_ms`

Review the configuration after a major Tessera firmware change in case those
internal IDs are renamed.

## Safety

Some Guition displays are installed on mains-powered relay bases. Disconnect all
sources of power before opening the enclosure or soldering. Verify the supply
and logic-voltage requirements of the exact VL53L0X breakout board being used.
Perform continuity checks and inspect every joint under magnification before
reconnecting USB or mains power.

## Licence

Released under the [MIT License](LICENSE).
