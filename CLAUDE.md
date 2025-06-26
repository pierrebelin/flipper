# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a "flipper" project for the STM32 NUCLEO-F411RE microcontroller using the Mbed framework. The device counts detections from multiple sources and triggers a solenoid mechanism:
- A push button (resets counter to 0)
- A toggle button (increments counter, triggers solenoid)  
- A PIR motion sensor (increments counter)

The count is displayed on both a 7-segment display (single digit) and optionally a 4-digit display, with counter range 0-9999.

## Build and Development Commands   

NEVER run pio or platform command. Always ask me to do it.

## Hardware Configuration

- **Board**: STM32 NUCLEO-F411RE
- **Framework**: Mbed OS
- **Main button**: BUTTON1 (built-in, resets counter)
- **Toggle button**: PC_10 (with PullUp, increments counter)
- **PIR sensor**: D12/PA_6 (with PullDown, increments counter)
- **Solenoid control**: PA_7 (D11, triggered by toggle button)
- **7-segment display**: D2-D8 (segments A-G)
- **4-digit display**: CN10 connector with multiplexed segments and digit selectors
- **Serial logging**: USBTX/USBRX at 9600 baud for debugging

## Code Architecture

### Main Application (`src/main.cpp`)
Implements a polling-based state machine that:
1. Reads three input sources with debouncing (50ms delay)
2. Detects rising/falling edges for event triggering
3. Manages a 4-digit counter (0-9999) with wraparound
4. Controls dual display outputs and solenoid activation
5. Provides serial logging for all events

### Display Classes
- **`SevenSegmentDisplay`** (`src/SevenSegmentDisplay.h/cpp`): Single 7-segment display showing last digit only
- **`FourDigitDisplay`** (`src/FourDigitDisplay.h/cpp`): 4-digit multiplexed display with ticker-based refresh

### Hardware Multiplexing
The 4-digit display uses time-division multiplexing with shared segment pins and individual digit selector pins (cathode switching). Pin mappings are documented in `AFFICHAGE-4-CHIFFRES.md`.

## Testing

Tests use the Unity framework and are located in the `test/` directory. Current test structure includes basic functionality tests.