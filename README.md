**Proto-Sniffer: Multi-Protocol Sniffer with Bare-Metal STM32**

**Overview**
This project implements a bare-metal, layered-architecture firmware for STM32F407 that monitors I2C and SPI data in real time and sends it to a UART terminal for logging and debugging.
It also supports SPI loopback testing and live Gyroscope/Accelerometer sensor data acquisition using I2C — all built from scratch with no HAL/CMSIS.


**Project Highlights**
 1) Layered Architecture (MCAL → ECUAL → Application) inspired by AUTOSAR principles.
 2) Multi-Protocol Support.
 3) UART for terminal logging.
 4) I2C for Gy-521 Gyroscope/Accelerometer Sensor data acquisition.
 5) SPI for loopback testing with live PASS/FAIL results.
 6) Polling + Interrupt Handling.
 7) Interrupts for UART commands and SPI loopback events.
 8) Polling for I2C sensor data (with awareness of why interrupts can fail in I2C read cycles).
 9) Circular Buffers for both SPI and I2C data streams before UART logging.
10) SPI Loopback Mode to test Tx/Rx paths with real-time PASS/FAIL status.
11) Live Gyroscope Data (Linear acceleration across X, Y, Z axes) displayed on UART terminal.
12) Fully bare-metal: direct register access for GPIO, SPI, I2C, and UART — no drivers, no libraries.
13) Modular and scalable design with separate layers for hardware and application logic.

**Features Implemented**
1) Protocol Sniffer Menu over UART.
2) SPI Loopback Testing with PASS/FAIL results in real time.
3) Accelerometer Data Acquisition over I2C with proper data framing & formatting.
4) Circular Buffer Management for asynchronous data handling.
5) Polling + Interrupt Hybrid Design for responsiveness & stability.
6) Awareness of race conditions and why interrupts are avoided in some I2C scenarios.


**Hardware Requirements**
1)STM32F407 Discovery Board (or compatible Cortex-M4 MCU).
2)GY-521 Gyroscope Module (I2C).
3)UART-USB Bridge (e.g., CP2102) for terminal output.
4)SPI Loopback jumper (MISO ↔ MOSI).
5)Logic Level Shifter for interfacing MCU with GY-521 (if required).

**Software Requirements**
1)STM32CubeIDE / Bare-metal Toolchain.
2)TeraTerm / PuTTY for UART terminal logging.
3)Git for version control.
