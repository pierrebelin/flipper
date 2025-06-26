# Branchement Affichage 4 Chiffres - STM32 NUCLEO-F411RE

## Configuration matérielle

**Affichage**: 4 chiffres 7-segments à cathode commune
**Pins utilisées**: 11 pins (7 segments + 4 sélecteurs)
**Technique**: Multiplexage temporel pour affichage simultané

## Branchement optimisé - Connecteur CN10

### Mapping pins affichage ↔ Fonction (vue de face)
- **Pin 1** (haut gauche): Digit 4 (cathode commune)
- **Pin 2** (haut): Segment D  
- **Pin 3** (haut): Segment F
- **Pin 4** (haut): Digit 3 (cathode commune)
- **Pin 5** (haut): Digit 2 (cathode commune)
- **Pin 6** (haut droite): Segment E
- **Pin 7** (bas gauche): Segment B
- **Pin 8** (bas): Segment C
- **Pin 9** (bas): Point décimal (DP)
- **Pin 10** (bas): Segment A
- **Pin 11** (bas): Segment G
- **Pin 12** (bas droite): Digit 1 (cathode commune)

### Branchement STM32 NUCLEO-F411RE (CN10)
**Segments (partagés entre tous les chiffres):**
- **Segment A**: PC8 (CN10-2) ← Pin 10 (bas droite)
- **Segment B**: PC6 (CN10-4) ← Pin 7 (bas gauche)
- **Segment C**: PC5 (CN10-6) ← Pin 8 (bas)
- **Segment D**: PA12 (CN10-12) ← Pin 2 (haut)
- **Segment E**: PA11 (CN10-14) ← Pin 6 (haut droite)
- **Segment F**: PB2 (CN10-22) ← Pin 11 (milieu)
- **Segment G**: PB1 (CN10-24) ← Pin 3 (haut gauche)

**Sélecteurs de chiffres (cathodes communes):**
- **Digit 1**: PB15 (CN10-26) ← Pin 12
- **Digit 2**: PB14 (CN10-28) ← Pin 5
- **Digit 3**: PB13 (CN10-30) ← Pin 4
- **Digit 4**: PC4 (CN10-34) ← Pin 1

**Point décimal (optionnel):**
- **DP**: PB12 (CN10-16) ← Pin 9

## Schéma de branchement avec breadboard (VUE DE FACE)                                                      
┌──────────────────┐
│ 1  2  3  4  5  6 │ ← Pins haut
│[4]      [3][2]   │
│               [1]│
│ 7  8  9 10 11 12 │ ← Pins bas
└──────────────────┘