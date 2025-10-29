# 🏷️RFID Based Attendance System

An automated attendance tracking system using RFID technology that records student attendance and generates detailed reports. This is done using `AT89S52` Microcontroller, `EM-18` RFID reader module and `FT232` USB - UART module.

## 📝Overview

This RFID-based attendance system automatically records student attendance when they place their RFID cards near the `EM-18` reader module. The system displays student information on an LCD screen and logs attendance data with timestamps to a CSV file. Additional Python scripts provide attendance summary reports with percentage calculations.

## 🚀Features

- ***Real-time Display***: Shows student name and attendance status on LCD.
- ***Automated Logging***: Records attendance with precise timestamps.
- ***CSV Export***: Stores data in comma-separated values format for easy analysis.
- ***Attendance Reports***: Generates summary with percentage attendance.
- ***UART Communication***: Enables seamless data transfer between microcontroller and computer.
- ***Multi-student Support***: Capable of handling multiple RFID cards.

## ⚙️Components Required

| Component | Quantity |
|-----------|----------|
| `AT89S52` Microcontroller | 1 |
| `EM-18` RFID Reader Module | 1 |
| `16x2` LCD Display | 1 |
| RFID Cards/Tags | Multiple |
| `FT232` USB-UART Module | 1 |
| `220Ω` Resistor | 1 |
| `10K` Potentiometer | 1 |
| Jumper Wires | Multiple |
| Breadboard | 1 |
| Power Supply | 1 |

## 🔧Hardware Connections

### 📺**LCD** (16x2) **Connections** -

| LCD Pin | Connection |
|---------|------------|
| Pin 1 (`GND`) | `GND` rail |
| Pin 2 (`VCC`) | `+5V` rail |
| Pin 3 (`VEE`) | Potentiometer middle pin |
| Pin 4 (`RS`) | `P3.2` |
| Pin 5 (`RW`) | `GND` |
| Pin 6 (`EN`) | `P3.3` |
| Pin 11 (`D4`) | `P2.4` |
| Pin 12 (`D5`) | `P2.5` |
| Pin 13 (`D6`) | `P2.6` |
| Pin 14 (`D7`) | `P2.7` |
| Pin 15 (`LED+`) | `+5V` (via `220Ω` resistor) |
| Pin 16 (`LED-`) | `GND` |

### 🪪**RFID Module Connections** - 

| Pin | Connection |
|----------|------------|
| `VCC` | `+5V` rail |
| `GND` | `GND` rail |
| `TX` | `P3.0` (`RXD` of 8051) |

### 🔌**UART Module Connections** - 

| Pin | Connection |
|----------|------------|
| `VCC` | `+5V` rail |
| `GND` | `GND` rail |
| `RXD` | `P3.1` (`TXD` of 8051) |
| `TXD` | (Optional) `P3.0` |

## 🪜Procedure

1. Connect the circuit as per the hardware connections.  
2. To get the unique RFID IDs of each card, burn the HEX file from the `RFID ID` folder into your `AT89S52` microcontroller (UART module connection not required).  
3. After burning the HEX file, place your RFID card in front of the `EM-18` module and note down the RFID ID displayed on the LCD.  
4. For the attendance system, replace the card IDs and student names with your own in the `RFID Attendance` folder. Burn the HEX file into the `AT89S52`. When you place the card near the `EM-18`, the student name and “PRESENT” will be shown on the LCD.  
5. For attendance logging, connect the `FT232` UART module as per the given connections. Connect it to your PC/laptop, check the `COM` port, and replace it in 1Attendance-Logger.py`.  
6. Run the program — raw data (`Student Name PRESENT at Timestamp`) will appear in the terminal and also be saved in `attendance.txt` (CSV format).  
7. Run `Attendance-Tracker.py` to view each student’s attendance details, total classes attended, and attendance percentage in the terminal.

## 💻Software Requirements

### ***For Microcontroller*** - 
- Keil μVision IDE
- 8051 compiler

### ***For Python Scripts*** - 
- Python 3.6 or higher
- Required packages:
  - `pyserial`
  - `datetime`

## 📂Folders Explanation

- `RFID ID`: Get the unique 10-character ID number of the RFID card displayed on the LCD.
- `RFID Attendance`: Display the student name and "present" on the LCD based on the RFID number.
- `Attendance-Logger.py`: Log the Name, Attendance Status and Time Stamp of each student in a .txt file.
- `Attendance-Tracker.py`: Show the No. of classes attended and Attendance Percentage of each student.
