#ifndef SEVEN_SEGMENT_DISPLAY_H
#define SEVEN_SEGMENT_DISPLAY_H

#include "mbed.h"

// Classe pour gérer l'afficheur 7 segments
class SevenSegmentDisplay {
public:
    // Constructeur avec les broches pour chaque segment
    SevenSegmentDisplay(PinName pinA, PinName pinB, PinName pinC, PinName pinD, 
                        PinName pinE, PinName pinF, PinName pinG);
    
    // Méthodes pour afficher les chiffres
    void displayDigit(int digit);
    void clearDisplay();
    
private:
    // Méthodes privées pour afficher chaque chiffre
    void displayDigit0();
    void displayDigit1();
    void displayDigit2();
    void displayDigit3();
    void displayDigit4();
    void displayDigit5();
    void displayDigit6();
    void displayDigit7();
    void displayDigit8();
    void displayDigit9();
    
    // Segments de l'afficheur
    DigitalOut segmentA;
    DigitalOut segmentB;
    DigitalOut segmentC;
    DigitalOut segmentD;
    DigitalOut segmentE;
    DigitalOut segmentF;
    DigitalOut segmentG;
};

#endif // SEVEN_SEGMENT_DISPLAY_H 