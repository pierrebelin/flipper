#ifndef FOUR_DIGIT_DISPLAY_H
#define FOUR_DIGIT_DISPLAY_H

#include "mbed.h"

class FourDigitDisplay {
private:
    DigitalOut segA, segB, segC, segD, segE, segF, segG;
    DigitalOut digit1, digit2, digit3, digit4;
    
    int currentValue;
    int displayIndex;
    Ticker displayTicker;
    
    static const bool segmentPatterns[10][7];
    
    void updateDisplay();
    void displayDigitAt(int position, int digit);
    
public:
    FourDigitDisplay(PinName a, PinName b, PinName c, PinName d, PinName e, PinName f, PinName g,
                     PinName d1, PinName d2, PinName d3, PinName d4);
    
    void displayNumber(int number);
    void startMultiplexing();
    void stopMultiplexing();
};

#endif