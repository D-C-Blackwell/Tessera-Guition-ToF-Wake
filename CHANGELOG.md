# Changelog

## 0.2.0 - 2026-10-15

- Changed the default approach distance to 1.0 m.
- Kept raw distance measurements local to the screen.
- Published only detected and cleared state changes to Home Assistant.
- Limited routine ToF logs while retaining transition, warning and error logs.

## 0.1.0 - 2026-10-15

- Added a reusable Tessera local-YAML example.
- Added local 0.50 m approach detection with 0.65 m release hysteresis.
- Added local Tessera display wake and standby keep-alive behaviour.
- Separated the 500 ms local measurement from the five-second Home Assistant
  diagnostic update.
- Documented shared GT911 I2C wiring, installation, optical mounting and
  troubleshooting.
- Documented the precision soldering experience, microscope and inspection
  equipment required for the hardware modification.
