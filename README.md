# Hardware PID Controller

This repository contains the code and schematics for a hardware PID controller, designed to control the temperature of a small system.

## Overview

The Hardware PID Controller is an electronic device that uses a PID (Proportional, Integral, Derivative) algorithm to control the temperature of a system. It is designed to be easily adaptable to various systems and can be configured to work with different temperature sensors and actuators. This project was developed using the STM32 microcontroller and provides an affordable, easy-to-use solution for temperature control in various applications.

## Features

- STM32-based microcontroller for efficient and accurate temperature control
- Supports various temperature sensors (e.g., thermocouples, RTDs, thermistors)
- Configurable PID algorithm parameters
- Easy-to-use user interface for setting and monitoring the temperature
- Detailed schematics and design files provided for easy hardware customization
- Comprehensive documentation for getting started and customizing the hardware and software

## Getting Started

### Prerequisites

- STM32 development environment (e.g., STM32CubeIDE, Keil uVision, IAR Embedded Workbench)
- Temperature sensor and actuator compatible with the hardware design
- Basic electronics tools and equipment (e.g., soldering iron, multimeter)

### Building the Hardware

1. Clone this repository and download the schematics and design files.
2. Assemble the hardware according to the provided schematics and design files.
3. Connect the temperature sensor and actuator to the hardware.

### Configuring the Software

1. Open the project in your preferred STM32 development environment.
2. Configure the PID algorithm parameters in the source code.
3. Compile and flash the firmware onto the STM32 microcontroller.

### Running the Hardware PID Controller

1. Power on the hardware and connect it to the system you want to control.
2. Use the user interface to set the desired temperature and monitor the system's temperature.
3. Adjust the PID algorithm parameters as needed for optimal performance.

## Customization

The Hardware PID Controller can be customized to suit your specific application requirements. You can modify the hardware design files to add or change components, and you can adjust the software to support different temperature sensors and actuators. Refer to the provided documentation for more information on customizing the Hardware PID Controller.

## License

This project is licensed under the [MIT License](LICENSE).

## Acknowledgments

- Special thanks to [STM32](https://www.st.com/en/microcontrollers-microprocessors/stm32-32-bit-arm-cortex-mcus.html) for providing the microcontroller used in this project.
- The project was inspired by various open-source PID controller projects available online.
