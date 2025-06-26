#include "FourDigitDisplay.h"

const bool FourDigitDisplay::segmentPatterns[10][7] = {
    {1, 1, 1, 1, 1, 0, 1}, 
    {1, 0, 0, 0, 1, 0, 0}, 
    {0, 1, 1, 1, 1, 1, 0}, 
    {1, 0, 1, 1, 1, 1, 0}, 
    {1, 0, 0, 0, 1, 1, 1}, 
    {1, 0, 1, 1, 0, 1, 1}, 
    {1, 1, 1, 1, 0, 1, 1}, 
    {1, 0, 0, 1, 1, 0, 0}, 
    {1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 1, 1, 1, 1} 
};

FourDigitDisplay::FourDigitDisplay(PinName a, PinName b, PinName c, PinName d, PinName e, PinName f, PinName g,
                                   PinName d1, PinName d2, PinName d3, PinName d4)
    : segA(a), segB(b), segC(c), segD(d), segE(e), segF(f), segG(g),
      digit1(d1), digit2(d2), digit3(d3), digit4(d4),
      currentValue(0), displayIndex(0) {
    
    // Force all segments OFF first (prevent ghosting during digit init)
    segA = 0; segB = 0; segC = 0; segD = 0;
    segE = 0; segF = 0; segG = 0;
    
    // Then turn off all digits with delay
    digit1 = 1;
    digit2 = 1;
    digit3 = 1;
    digit4 = 1;
    
    // Critical delay to ensure pins are stable
    wait_us(1000);
}

void FourDigitDisplay::displayNumber(int number) {
    if (number < 0) number = 0;
    if (number > 9999) number = 9999;
    currentValue = number;
}

void FourDigitDisplay::displayDigitAt(int position, int digit) {
    // Turn off all digits first
    digit1 = 1;
    digit2 = 1;
    digit3 = 1;
    digit4 = 1;
    segA = 0; segB = 0; segC = 0; segD = 0;
    segE = 0; segF = 0; segG = 0;

    // Set segments for the digit (mapping standard A-G)
    if (digit >= 0 && digit <= 9) {
        segA = segmentPatterns[digit][0]; // A direct
        segB = segmentPatterns[digit][1]; // B direct
        segC = segmentPatterns[digit][2]; // C direct
        segD = segmentPatterns[digit][3]; // D direct
        segE = segmentPatterns[digit][4]; // E direct
        segF = segmentPatterns[digit][5]; // F direct
        segG = segmentPatterns[digit][6]; // G direct
    }
    
    // Turn on the specific digit
    switch (position) {
        case 0: digit1 = 0; break;
        case 1: digit2 = 0; break;
        case 2: digit3 = 0; break; 
        case 3: digit4 = 0; break; 
    }
}

void FourDigitDisplay::updateDisplay() {
    // Extract digits from current value
    int thousands = (currentValue / 1000) % 10;
    int hundreds = (currentValue / 100) % 10;
    int tens = (currentValue / 10) % 10;
    int units = currentValue % 10;
    
    // Display current digit based on displayIndex (start from rightmost)
    switch (displayIndex) {
        case 0:
            displayDigitAt(3, units); // Digit 4 (rightmost)
            break;
        case 1:
            if (currentValue >= 10) {
                displayDigitAt(2, tens); // Digit 3
            } else {
                displayDigitAt(2, -1); // Turn off digit
            }
            break;
        case 2:
            if (currentValue >= 100) {
                displayDigitAt(1, hundreds); // Digit 2
            } else {
                displayDigitAt(1, -1); // Turn off digit
            }
            break;
        case 3:
            if (currentValue >= 1000) {
                displayDigitAt(0, thousands); // Digit 1 (leftmost)
            } else {
                displayDigitAt(0, -1); // Turn off digit
            }
            break;
    }
    
    // Move to next digit
    displayIndex = (displayIndex + 1) % 4;
}

void FourDigitDisplay::startMultiplexing() {
    displayTicker.attach(callback(this, &FourDigitDisplay::updateDisplay), 2ms);
}

void FourDigitDisplay::stopMultiplexing() {
    displayTicker.detach();
    // Turn off all digits
    digit1 = 1;
    digit2 = 1;
    digit3 = 1;
    digit4 = 1;
}