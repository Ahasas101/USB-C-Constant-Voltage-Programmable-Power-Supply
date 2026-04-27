100 W USB-C Power Delivery Based Programmable DC Power Supply
Overview

This project implements a compact, programmable DC power supply using USB-C Power Delivery (USB-PD). It negotiates multiple voltage levels from a USB-C charger and provides a regulated, adjustable DC output suitable for electronics development and testing.

The system is built using an STM32 microcontroller, a dedicated USB-PD controller, and a high-efficiency power conversion stage. It also includes an OLED display for real-time system feedback. Both hardware and firmware are developed from scratch .

Features
USB-C Power Delivery voltage negotiation (5V, 9V, 12V, 15V, 20V)
Programmable DC output
Dual operating modes:
Direct PD Mode (fixed voltage selection)
Adjustable Output Mode (via buck converter)
Real-time voltage and current monitoring
OLED display for live system parameters
High-efficiency power conversion
Compact and portable design
Custom PCB designed in KiCad
System Architecture
Power Path

USB-C Charger → PD Controller → Power ORing → Buck Converter → Output

Control and Monitoring

Microcontroller → INA226 Sensor → OLED Display → System Monitoring and Protection

The system architecture and block diagram are described in the project document (page 4) .

Hardware Components
STM32F030C8T6 Microcontroller
CH224K USB-PD Controller
INA226 Voltage and Current Monitor
MP1584EN Buck Converter
PMOS-based Power ORing Circuit
OLED Display (I2C)
Working Modes
1. Direct PD Mode

The PD controller negotiates and outputs fixed voltage levels directly from the USB-C charger.

2. Adjustable Output Mode

The negotiated voltage is fed into a buck converter to generate a variable DC output.

PCB Design
Designed using KiCad
Includes power stage, control circuitry, sensing modules, and display interface
High-current routing and thermal considerations implemented

Author

Ahasas Yadav
