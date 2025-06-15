#include "mbed.h"

// Initialisation explicite du port série pour les logs
UnbufferedSerial pc(USBTX, USBRX, 9600); // TX, RX, baudrate

void log(const char* msg) {
    pc.write(msg, strlen(msg));
}

int main()
{
    // Bouton poussoir connecté sur PA_5 (D13) avec pull-down
    // Note: E5V mentionné dans la demande, j'utilise PA_5 comme pin digital standard
    DigitalIn pushButton(PA_5, PullDown);
    
    // Sortie pour contrôler le MOSFET du solénoïde 12V sur PA7 (D11)
    DigitalOut solenoidControl(PA_7);
    
    // Variables pour le debouncing
    bool lastButtonState = false;
    bool solenoidActive = false;
    
    // Initialisation
    solenoidControl = 0; // MOSFET désactivé au démarrage
    log("[INIT] Système de contrôle solénoïde initialisé\r\n");
    log("[INFO] Bouton: PA_5 (D13), Solénoïde: PA_7 (D11)\r\n");

    while (true) {
        // Lecture de l'état actuel du bouton
        bool currentButtonState = pushButton.read();
        
        // Détection d'un front montant (bouton pressé)
        if (currentButtonState && !lastButtonState) {
            if (!solenoidActive) {
                // Activation du solénoïde
                solenoidControl = 1;
                solenoidActive = true;
                log("[SOLENOID] Activation du solénoïde\r\n");
            } else {
                // Désactivation du solénoïde
                solenoidControl = 0;
                solenoidActive = false;
                log("[SOLENOID] Désactivation du solénoïde\r\n");
            }
        }
        
        // Sauvegarde de l'état du bouton pour le prochain cycle
        lastButtonState = currentButtonState;
        
        // Délai pour éviter le rebond et réduire la charge CPU
        ThisThread::sleep_for(50ms);
    }
}