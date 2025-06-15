#include "SevenSegmentDisplay.h"

//    A
//  F   B
//    G
//  E   C
//    D

SevenSegmentDisplay::SevenSegmentDisplay(PinName pinA, PinName pinB, PinName pinC, PinName pinD, PinName pinE, PinName pinF, PinName pinG)
    : segmentA(pinA), segmentB(pinB), segmentC(pinC), segmentD(pinD),
      segmentE(pinE), segmentF(pinF), segmentG(pinG) {
    clearDisplay();
}

void SevenSegmentDisplay::clearDisplay() {
    segmentA = 0;
    segmentB = 0;
    segmentC = 0;
    segmentD = 0;
    segmentE = 0;
    segmentF = 0;
    segmentG = 0;
}

void SevenSegmentDisplay::displayDigit0() {
    // Segments: A, B, C, D, E, F (tous sauf G)
    segmentA = 1;
    segmentB = 1;
    segmentC = 1;
    segmentD = 1;
    segmentE = 1;
    segmentF = 1;
    segmentG = 0;
}

void SevenSegmentDisplay::displayDigit1() {
    // Segments: B, C
    segmentA = 0;
    segmentB = 1;
    segmentC = 1;
    segmentD = 0;
    segmentE = 0;
    segmentF = 0;
    segmentG = 0;
}

void SevenSegmentDisplay::displayDigit2() {
    // Segments: A, B, G, E, D
    segmentA = 1;
    segmentB = 1;
    segmentC = 0;
    segmentD = 1;
    segmentE = 1;
    segmentF = 0;
    segmentG = 1;
}

void SevenSegmentDisplay::displayDigit3() {
    // Segments: A, B, G, C, D
    segmentA = 1;
    segmentB = 1;
    segmentC = 1;
    segmentD = 1;
    segmentE = 0;
    segmentF = 0;
    segmentG = 1;
}

void SevenSegmentDisplay::displayDigit4() {
    // Segments: F, G, B, C
    segmentA = 0;
    segmentB = 1;
    segmentC = 1;
    segmentD = 0;
    segmentE = 0;
    segmentF = 1;
    segmentG = 1;
}

void SevenSegmentDisplay::displayDigit5() {
    // Segments: A, F, G, C, D
    segmentA = 1;
    segmentB = 0;
    segmentC = 1;
    segmentD = 1;
    segmentE = 0;
    segmentF = 1;
    segmentG = 1;
}

void SevenSegmentDisplay::displayDigit6() {
    // Segments: A, F, G, E, D, C
    segmentA = 1;
    segmentB = 0;
    segmentC = 1;
    segmentD = 1;
    segmentE = 1;
    segmentF = 1;
    segmentG = 1;
}

void SevenSegmentDisplay::displayDigit7() {
    // Segments: A, B, C
    segmentA = 1;
    segmentB = 1;
    segmentC = 1;
    segmentD = 0;
    segmentE = 0;
    segmentF = 0;
    segmentG = 0;
}

void SevenSegmentDisplay::displayDigit8() {
    // Tous les segments
    segmentA = 1;
    segmentB = 1;
    segmentC = 1;
    segmentD = 1;
    segmentE = 1;
    segmentF = 1;
    segmentG = 1;
}

void SevenSegmentDisplay::displayDigit9() {
    // Segments: A, B, F, G, C, D
    segmentA = 1;
    segmentB = 1;
    segmentC = 1;
    segmentD = 1;
    segmentE = 0;
    segmentF = 1;
    segmentG = 1;
}

void SevenSegmentDisplay::displayDigit(int digit) {
    clearDisplay();
    
    switch (digit) {
        case 0:
            displayDigit0();
            break;
        case 1:
            displayDigit1();
            break;
        case 2:
            displayDigit2();
            break;
        case 3:
            displayDigit3();
            break;
        case 4:
            displayDigit4();
            break;
        case 5:
            displayDigit5();
            break;
        case 6:
            displayDigit6();
            break;
        case 7:
            displayDigit7();
            break;
        case 8:
            displayDigit8();
            break;
        case 9:
            displayDigit9();
            break;
        default:
            // Si le chiffre n'est pas entre 0 et 9, on efface l'affichage
            clearDisplay();
            break;
    }
} 