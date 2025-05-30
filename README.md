# Honeywell-FMA-I2C-Arduino
## Description:

Arduino code and examples for interfacing with Honeywell FMA Series MicroForce Sensors over I²C. This repository supports only the I²C variants of the FMA Series sensors (e.g., FMAMSDXX005WC2C3, FMAMSDXX015WC2C3, FMAMSDXX025WC2C3) and excludes all SPI-based models.

The FMA Series are compact, piezoresistive force sensors with digital outputs, fully compensated for offset, sensitivity, and temperature effects via onboard ASICs. This code enables communication with these sensors using their I²C interface and allows for straightforward integration into Arduino-based systems.

## Features:

- I²C communication using standard Arduino Wire library

- Read force data in real-time

- Support for different I²C addresses (0x28, 0x38, 0x48, etc.)

- Basic sensor initialisation and diagnostic handling

## Technical Documentation
Sensor [datasheet](https://www.farnell.com/datasheets/2921324.pdf) here.

## Additional Notes
This repository does not include support for the SPI versions of the FMA sensors. Basic SPI library is provided [here](https://github.com/JayasinghePasan/Honeywell_SPI_FMA)

License: MIT