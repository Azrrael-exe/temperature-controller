#ifndef DISPLAY_7SEG_H
#define DISPLAY_7SEG_H

#include <Arduino.h>
#include "Display.h"

class Display7Seg : public Display {
private:
    const uint8_t LATCH_PIN;
    const uint8_t CLK_PIN;
    const uint8_t DATA_PIN;
    
    // Valores hexadecimales para cada dígito/segmento
    static const byte SEG_OFF = 0xFF;
    static const byte DIGITS[10];
    static const byte LETTERS[26];
    
    // Selectores de segmento
    static const byte SEGMENT_SELECT[4];

    // Buffer para almacenar los valores actuales
    byte displayBuffer[4];
    byte displayTypes[4];  // 0 para dígito, 1 para letra
    
public:
    Display7Seg(uint8_t latchPin, uint8_t clkPin, uint8_t dataPin);
    
    // Implementación de métodos virtuales de Display
    void begin() override;
    void clear() override;
    void displayNumber(int number, bool leadingZeros = false) override;
    void refresh() override;
    
    // Métodos específicos de Display7Seg
    void displayDigit(uint8_t position, uint8_t digit);
    void displayLetter(uint8_t position, char letter);
    void displayString(const char* str, unsigned long duration = 500);
    
private:
    void sendDataToSegment(byte segmentNo, byte hexValue);
};

#endif 