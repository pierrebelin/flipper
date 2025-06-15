# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a "flipper" project for the STM32 NUCLEO-F411RE microcontroller using the Mbed framework. The device counts detections from multiple sources:
- A push button (resets counter)
- A toggle button (increments counter)  
- A PIR motion sensor (increments counter)

The count is displayed on a 7-segment display and ranges from 0-9.

## Build Commands

The project uses PlatformIO for building and deployment:

```bash
# Build the project
pio run

# Run tests
pio test
```

Do not upload the project, I'll do it manually

## Hardware Configuration

- **Board**: STM32 NUCLEO-F411RE
- **Framework**: Mbed
- **Main button**: BUTTON1 (built-in)
- **Toggle button**: PC_10 (with PullUp)
- **PIR sensor**: PA_6/D12 (with PullDown)
- **7-segment display**: Connected to pins PA_10, PB_3, PB_5, PB_4, PB_10, PA_8, PA_9 (segments A-G)
- **Serial logging**: USBTX/USBRX at 9600 baud for debugging

## Code Architecture

The main application (`src/main.cpp`) implements a simple state machine that:
1. Polls three input sources in the main loop
2. Handles button debouncing and edge detection
3. Updates a digit counter (0-9) based on inputs
4. Displays the current count on the 7-segment display
5. Logs events via serial for debugging

The `SevenSegmentDisplay` class (`src/SevenSegmentDisplay.h/cpp`) encapsulates:
- Pin management for all 7 segments (A-G)
- Digit pattern definitions for 0-9
- Display control methods

## Testing

Tests use the Unity framework and are located in the `test/` directory. The test structure includes a basic test template for PIR functionality.