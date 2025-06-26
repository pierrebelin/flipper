# Branchement Affichage 4 Chiffres - STM32 NUCLEO-F411RE

## Configuration matérielle

**Affichage**: 4 chiffres 7-segments à cathode commune
**Pins utilisées**: 11 pins (7 segments + 4 sélecteurs)
**Technique**: Multiplexage temporel pour affichage simultané

## Branchement optimisé - Connecteur CN10

### Mapping pins affichage ↔ Fonction
- **Pin 1**: Segment E
- **Pin 2**: Segment D  
- **Pin 3**: Point décimal (DP)
- **Pin 4**: Segment C
- **Pin 5**: Segment G
- **Pin 6**: Digit 4 (cathode commune)
- **Pin 7**: Segment B
- **Pin 8**: Digit 3 (cathode commune)
- **Pin 9**: Digit 2 (cathode commune)
- **Pin 10**: Segment F
- **Pin 11**: Segment A
- **Pin 12**: Digit 1 (cathode commune)

### Branchement STM32 NUCLEO-F411RE (CN10)
**Segments (partagés entre tous les chiffres):**
- **Segment A**: PA3 (CN10-37) ← Pin 11 affichage
- **Segment B**: PA2 (CN10-35) ← Pin 7 affichage
- **Segment C**: PA10 (CN10-33) ← Pin 4 affichage
- **Segment D**: PB3 (CN10-31) ← Pin 2 affichage
- **Segment E**: PB5 (CN10-29) ← Pin 1 affichage
- **Segment F**: PB4 (CN10-27) ← Pin 10 affichage
- **Segment G**: PB13 (CN10-30) ← Pin 5 affichage

**Sélecteurs de chiffres (cathodes communes):**
- **Digit 1**: PB14 (CN10-26) ← Pin 12 affichage
- **Digit 2**: PB12 (CN10-25) ← Pin 9 affichage
- **Digit 3**: PB15 (CN10-24) ← Pin 8 affichage
- **Digit 4**: PA8 (CN10-23) ← Pin 6 affichage

**Point décimal (optionnel):**
- **DP**: PB10 (CN10-30) ← Pin 3 affichage

## Schéma de branchement avec breadboard

```
STM32 NUCLEO-F411RE                    BREADBOARD                    AFFICHAGE 4 CHIFFRES
                                                                      
    CN10                                                              ┌──────────────────┐
                                                                      │ 6  5  4  3  2  1 │ ← Pins haut
┌─ Pin 37 (PA3)  ────────────● Ligne rouge ─────── [330Ω] ────────── │[1][2][3][4]      │ ← Pin 11 (Seg A)
│                                                                     │                  │
├─ Pin 35 (PA2)  ────────────● Ligne orange ───── [330Ω] ────────── │ 7  8  9 10 11 12 │ ← Pin 7 (Seg B)
│                                                                     └──────────────────┘ ← Pins bas
├─ Pin 33 (PA10) ────────────● Ligne jaune ────── [330Ω] ──────────────────────────────── Pin 4 (Seg C)
│
├─ Pin 31 (PB3)  ────────────● Ligne verte ────── [330Ω] ──────────────────────────────── Pin 2 (Seg D)
│
├─ Pin 29 (PB5)  ────────────● Ligne bleue ────── [330Ω] ──────────────────────────────── Pin 1 (Seg E)
│
├─ Pin 27 (PB4)  ────────────● Ligne violette ─── [330Ω] ──────────────────────────────── Pin 10 (Seg F)
│
├─ Pin 28 (PB14) ────────────● Ligne grise ────── [330Ω] ──────────────────────────────── Pin 5 (Seg G)
│
├─ Pin 30 (PB13) ────────────● Ligne marron ───── [330Ω] ──────────────────────────────── Pin 3 (DP)
│
├─ Pin 26 (PB15) ────────────● Ligne blanche ──── DIRECT ─────────────────────────────── Pin 12 (Digit 1)
│
├─ Pin 25 (PB12) ────────────● Ligne noire ────── DIRECT ─────────────────────────────── Pin 9 (Digit 2)
│
├─ Pin 24 (PB1) ────────────● Ligne rose ─────── DIRECT ─────────────────────────────── Pin 8 (Digit 3)
│
├─ Pin 23 (PA8)  ────────────● Ligne turquoise ── DIRECT ─────────────────────────────── Pin 6 (Digit 4)
│
└─ Pin 20 (GND)  ────────────● Rail GND ──────── Breadboard GND rail ──────────────── (Pas de pin affichage - Alimentation)
```

### Instructions de câblage étape par étape

**Matériel nécessaire :**
- 1 breadboard
- 8 résistances 330Ω 
- 13 fils de couleurs différentes (12 + 1 GND)
- 1 affichage 4 chiffres 7-segments


4. **Connecter GND** : 
   - Relier Pin 20 (GND) du STM32 au rail négatif (-) de la breadboard
   - **Important** : L'affichage 4-chiffres n'a pas de pin GND dédié car il utilise des cathodes communes
   - Les cathodes communes (Digits 1-4) servent de retour de courant (équivalent GND pour chaque chiffre)
