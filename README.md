# iot-smarthome.v2-firmware

**Angaza Elimu Smarthome v2 project - firmware**

Welcome to the firmware repository for the Angaza Elimu Smarthome version 2 project. This repository contains firmware and Arduino libraries designed to control the various components of the Smarthome system. The target platform is ESP32 family devices(tested on ESP32-S2), utilizing board library versions 2.17 and above. The firmware is written in C++ and developed specifically for the Arduino IDE.

## Description

This repository holds the firmware for the Angaza Elimu Smarthome v2 project. The Smarthome project is built around the ESP32 platform, using various sensors and actuators to automate and control different elements of a Smarthome kit. Version 2 of the firmware introduces more robust handling of sensor data, control mechanisms, and enhanced communication features.

### Target Platform

- **Device**: ESP32-S2
- **Arduino Core Version**: 1.18 and above
- **Firmware Language**: C++

## Features

- **Modular Sensor Libraries**: Every sensor library is self-contained in a zip file with all necessary support files.
- **Basic Sensor Example Code**: Each sensor library includes a basic `.ino` example to help users get started quickly.
- **EEPROM-Based Configuration**: Persistent settings using ESP32’s EEPROM.
- **Secure HTTP Client**: Built-in support for secure communication with cloud services.
- **Servos, LEDs, Fans and Sensors Control**: Simple functions for events actuation, notification and monitoring environmental data.

## How to Use This Repository

### Installation Instructions

To use the firmware files and sensor libraries from this repository, follow the instructions below:

1. **Clone the Repository**  
   Clone the `iot-smarthome.v2-firmware` repository from GitHub:
   ```bash
   git clone https://github.com/Angaza-Elimu/iot-smarthome.v2-firmware.git
   ```
   - With this approach, the whole repository files will be available on your local machine.

2. **Download and Install Individual Sensor Libraries**
   - Each sensor library is packaged as a zip file, containing all the support files for controlling the specific sensor.
   - Download the zipped file from the repository under desired sensor directory/folder.
   - Open Arduino IDE and follow these steps:
     - Go to `Sketch` -> `Include Library` -> `Add .ZIP Library...`
     - Select the downloaded sensor zip file from your local machine and click **Ok**.
     - The library will now be available in the Arduino IDE.

3. **Access Example Files**
   - After the sensor library is installed, a basic `.ino` example file will be available for testing and getting started.
   - To access the example file:
     - Go to `File` -> `Examples` -> `Installed_Library_Name`
     - Open the example `.ino` file.
   - Alternatively, you can navigate directly to the `examples` folder in each sensor library directory within the GitHub repository.

### Quick Start Guide for Using Sensor Libraries

1. **Download Sensor Firmware**  
   Download the sensor firmware zip file from the corresponding folder in the repo.

2. **Install Sensor Library**  
   In Arduino IDE, navigate to:
   - `Sketch` -> `Include Library` -> `Add .ZIP Library...`
   - Select the downloaded zip file.

3. **Load Example Sketch**  
   Go to:
   - `File` -> `Examples` -> `Installed_Library_Name`
   - Load the example sketch, modify the necessary parameters:
      - Sensor `pins` in `pin_configuration.h` file,
      - `WiFi credentials` and `API Key` under `secrets.h` file, and upload it to your ESP32 board.

**NOTE**
  - Every `.ino` file has a `cert.h` file attached.
    - This holds server certificate for secure connection - `DO NOT` edit it

### Example Sensor Libraries

- **SmartDoorControl**  
   Control and automate door opening&locking mechanisms using servos, keypad and remote set server details.

   - Example location:  
     `examples/SmartDoorControl/SmartDoorControlExample.ino`

- **MQ2SmokeMonitor**  
   Monitor, detect smoke levels and invoke safety controls using a buzzer alarm for notification.

   - Example location:  
     `examples/MQ2SmokeMonitor/MQ2SmokeMonitorExample.ino`

- **SmartWindowControl**  
   Open and close windows using servos for ventilation control.

   - Example location:  
     `examples/SmartWindowControl/SmartWindowControlExample.ino`

### Additional Notes

- **WiFi Configuration**: Ensure that you have configured the correct `ssid` and `password` values in your firmware for WiFi connectivity.
- **Secure Communication**: This firmware supports secure HTTP communication. Make sure NOT to tamper with the provided root certificate for secure connections when required.
- **Platform connection**: For successful platform connection, ensure to provide a valid project `API Key`(generated after new project creation).

### Supported Sensors and Devices

- Door and Window Control with Servo and Keypad
- Smoke Detection (MQ2 sensor and Buzzer)
- Temperature and Humidity Monitoring (DHT sensor and Fan)
- Intrusion detection (PIR sensor and Buzzer)
- Rain detection (moisture sensor)
- Light intensity monitoring (LDR sensor)


---

Feel free to open an issue or submit a pull request to enhance or report problems with the **Angaza Elimu - Smarthome** library.

Happy Coding! 😊
