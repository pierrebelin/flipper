#include "mbed.h"
#include "SevenSegmentDisplay.h"

// Serial port for debugging
UnbufferedSerial pc(USBTX, USBRX, 9600);

void log(const char* msg) {
    pc.write(msg, strlen(msg));
}

int main() {
    // Hardware configuration according to CLAUDE.md
    DigitalIn resetButton(BUTTON1);           // Built-in button (resets counter)
    DigitalIn toggleButton(PC_10, PullUp);    // Toggle button (increments counter)
    DigitalIn pirSensor(PA_6, PullDown);      // PIR motion sensor (increments counter)
    
    // 7-segment display: PA_10, PB_3, PB_5, PB_4, PB_10, PA_8, PA_9 (segments A-G)
    SevenSegmentDisplay display(PA_10, PB_3, PB_5, PB_4, PB_10, PA_8, PA_9);
    
    // State variables
    int counter = 0;
    bool lastResetState = false;
    bool lastToggleState = false;
    bool lastPirState = false;
    
    // Initialize display to show 0
    display.displayDigit(0);
    log("[INIT] Flipper system initialized - Counter: 0\r\n");
    
    while (true) {
        // Read current states
        bool currentResetState = resetButton.read();
        bool currentToggleState = !toggleButton.read();  // Inverted because of PullUp
        bool currentPirState = pirSensor.read();
        
        // Reset button detection (falling edge for built-in button)
        if (!currentResetState && lastResetState) {
            counter = 0;
            display.displayDigit(counter);
            log("[RESET] Counter reset to 0\r\n");
        }
        
        // Toggle button detection (rising edge)
        if (currentToggleState && !lastToggleState) {
            counter = (counter + 1) % 10;  // Keep counter 0-9
            display.displayDigit(counter);
            log("[TOGGLE] Counter incremented to ");
            char buffer[10];
            sprintf(buffer, "%d\r\n", counter);
            log(buffer);
        }
        
        // PIR sensor detection (rising edge)
        if (currentPirState && !lastPirState) {
            counter = (counter + 1) % 10;  // Keep counter 0-9
            display.displayDigit(counter);
            log("[PIR] Motion detected - Counter incremented to ");
            char buffer[10];
            sprintf(buffer, "%d\r\n", counter);
            log(buffer);
        }
        
        // Save current states for next iteration
        lastResetState = currentResetState;
        lastToggleState = currentToggleState;
        lastPirState = currentPirState;
        
        // Debouncing delay
        ThisThread::sleep_for(50ms);
    }
}