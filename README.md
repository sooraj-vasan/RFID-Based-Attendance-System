# RFID Based Attendance System

An automated attendance tracking system using RFID technology that records student attendance and generates detailed reports.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Components Required](#components-required)
- [Hardware Connections](#hardware-connections)
- [Software Requirements](#software-requirements)
- [Installation & Setup](#installation--setup)
- [Usage](#usage)
- [File Structure](#file-structure)
- [Customization Options](#customization-options)
- [Troubleshooting](#troubleshooting)

## Overview

This RFID-based attendance system automatically records student attendance when they place their RFID cards near the EM-18 reader module. The system displays student information on an LCD screen and logs attendance data with timestamps to a CSV file. Additional Python scripts provide attendance summary reports with percentage calculations.

## Features

- **Real-time Display**: Shows student name and attendance status on LCD
- **Automated Logging**: Records attendance with precise timestamps
- **CSV Export**: Stores data in comma-separated values format for easy analysis
- **Attendance Reports**: Generates summary with percentage attendance
- **UART Communication**: Enables seamless data transfer between microcontroller and computer
- **Multi-student Support**: Capable of handling multiple RFID cards

## Components Required

| Component | Quantity |
|-----------|----------|
| AT89S52 Microcontroller | 1 |
| EM-18 RFID Reader Module | 1 |
| 16x2 LCD Display | 1 |
| RFID Cards/Tags | Multiple |
| FT232 USB-UART Module | 1 |
| 220Ω Resistor | 1 |
| 10K Potentiometer | 1 |
| Jumper Wires | Multiple |
| Breadboard | 1 |
| Power Supply | 1 |

## Hardware Connections

### LCD (16x2) Connections - 

| LCD Pin | Connection |
|---------|------------|
| Pin 1 (GND) | GND rail |
| Pin 2 (VCC) | +5V rail |
| Pin 3 (VEE) | Potentiometer middle pin |
| Pin 4 (RS) | P3.2 |
| Pin 5 (RW) | GND |
| Pin 6 (EN) | P3.3 |
| Pin 11 (D4) | P2.4 |
| Pin 12 (D5) | P2.5 |
| Pin 13 (D6) | P2.6 |
| Pin 14 (D7) | P2.7 |
| Pin 15 (LED+) | +5V (via 220Ω resistor) |
| Pin 16 (LED-) | GND |

### RFID Module Connections - 

| RFID Pin | Connection |
|----------|------------|
| VCC | +5V rail |
| GND | GND rail |
| TX | P3.0 (RXD of 8051) |

### USB-UART Module Connections - 

| UART Pin | Connection |
|----------|------------|
| VCC | +5V rail |
| GND | GND rail |
| RXD | P3.1 (TXD of 8051) |
| TXD | (Optional) P3.0 |

## Software Requirements

### For Microcontroller:
- Keil μVision IDE
- 8051 compiler
- Flash magic (for programming)

### For Python Scripts:
- Python 3.6 or higher
- Required packages:
  - `pyserial`
  - `datetime`

