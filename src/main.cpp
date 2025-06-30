#include "mbed.h"
#include "SevenSegmentDisplay.h"
#include "FourDigitDisplay.h"

// Serial port for debugging
UnbufferedSerial pc(USBTX, USBRX, 9600);

void log(const char* msg) {
    pc.write(msg, strlen(msg));
}

void triggerSolenoid(PwmOut& solenoid, int durationMs = 200) {
    solenoid.write(0.0f); 
    ThisThread::sleep_for(chrono::milliseconds(durationMs));
    solenoid.write(1.0f);  
}

int main() {
    // Hardware configuration according to CLAUDE.md
    DigitalIn resetButton(BUTTON1);           // Built-in button (resets counter)
    DigitalIn toggleButton(PC_10, PullUp);    // Toggle button (increments counter)
    DigitalIn pirSensor(D12, PullDown);      // PIR motion sensor (increments counter)
    
    // 7-segment display: D2-D8 (segments A-G) sur CN9
    SevenSegmentDisplay display(D2, D3, D4, D5, D6, D7, D8);
    
    // 4-digit display selon AFFICHAGE-4-CHIFFRES.md (CN10):
    // Segments A-G: PC8(Pin10), PC6(Pin7), PC5(Pin8), PA12(Pin2), PA11(Pin6), PB2(Pin3), PB1(Pin11)
    // Digits 1-4: PB15(Pin12), PB14(Pin5), PB13(Pin4), PC4(Pin1)
    FourDigitDisplay fourDigitDisplay(PC_8, PC_6, PC_5, PA_12, PA_11, PB_2, PB_1,
                                      PB_15, PB_14, PB_13, PC_4);
    
    // Solenoid control via PWM MOSFET module on PA7 (D11) - Module needs 4-20V input!
    // ATTENTION: Le module nécessite 4-20V, PA_7 ne donne que 3.3V
    PwmOut solenoidControl(PA_7);
    solenoidControl.period(0.020f); // 20ms = 50Hz (fréquence standard)

    // State variables
    int counter = 0;
    bool lastResetState = false;
    bool lastToggleState = false;
    bool lastPirState = false;
    
    // Initialize displays to show 0
    display.displayDigit(0);
    fourDigitDisplay.displayNumber(0);
    fourDigitDisplay.startMultiplexing();
    
    solenoidControl.write(1.0f);  // PWM module: 0% duty cycle = OFF (default state) 
    log("[INIT] Flipper system initialized - All segments ON for testing\r\n");
    
    while (true) {
        // Read current states
        bool currentResetState = resetButton.read();
        bool currentToggleState = !toggleButton.read();  // Inverted because of PullUp
        bool currentPirState = pirSensor.read();
        
        // Reset button detection (falling edge for built-in button)
        if (!currentResetState && lastResetState) {
            counter = 0;
            display.displayDigit(counter);
            fourDigitDisplay.displayNumber(counter);
            log("[RESET] Counter reset to 0\r\n");
        }
        
        // Toggle button detection (rising edge)
        if (currentToggleState && !lastToggleState) {
            counter = (counter + 1) % 10000;  // Keep counter 0-9999 for 4-digit display
            display.displayDigit(counter % 10);  // Show only last digit on 7-segment
            fourDigitDisplay.displayNumber(counter);
            log("[TOGGLE] Counter incremented to ");
            char buffer[10];
            sprintf(buffer, "%d\r\n", counter);
            log(buffer);
            triggerSolenoid(solenoidControl);
        }
        
        // PIR sensor detection (rising edge)
        if (currentPirState && !lastPirState) {
            counter = (counter + 1) % 10000;  // Keep counter 0-9999 for 4-digit display
            display.displayDigit(counter % 10);  // Show only last digit on 7-segment
            fourDigitDisplay.displayNumber(counter);
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