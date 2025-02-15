#include "Display7Seg.h"

// Definición de valores hexadecimales para dígitos 0-9
const byte Display7Seg::DIGITS[] = {
    0xC0, // 0
    0xF9, // 1
    0xA4, // 2
    0xB0, // 3
    0x99, // 4
    0x92, // 5
    0x82, // 6
    0xF8, // 7
    0x80, // 8
    0x90  // 9
};

// Definición de valores hexadecimales para letras A-Z
const byte Display7Seg::LETTERS[] = {
    0x88, // A
    0x83, // B
    0xC6, // C
    0xA1, // D
    0x86, // E
    0x8E, // F
    0xC2, // G
    0x89, // H
    0xF9, // I
    0xF1, // J
    0x8A, // K
    0xC7, // L
    0xC8, // M
    0xAB, // N
    0xC0, // O
    0x8C, // P
    0x98, // Q
    0xAF, // R
    0x92, // S
    0x87, // T
    0xC1, // U
    0xC1, // V
    0x85, // W
    0x89, // X
    0x91, // Y
    0xA4  // Z
};

const byte Display7Seg::SEGMENT_SELECT[] = {0xF1, 0xF2, 0xF4, 0xF8};

Display7Seg::Display7Seg(uint8_t latchPin, uint8_t clkPin, uint8_t dataPin)
    : LATCH_PIN(latchPin), CLK_PIN(clkPin), DATA_PIN(dataPin) {
    memset(displayBuffer, SEG_OFF, sizeof(displayBuffer));
    memset(displayTypes, 0, sizeof(displayTypes));
}

void Display7Seg::begin() {
    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLK_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);
    clear();
}

void Display7Seg::clear() {
    memset(displayBuffer, SEG_OFF, sizeof(displayBuffer));
    memset(displayTypes, 0, sizeof(displayTypes));
    for(uint8_t i = 0; i < 4; i++) {
        sendDataToSegment(SEGMENT_SELECT[i], SEG_OFF);
    }
}

void Display7Seg::displayDigit(uint8_t position, uint8_t digit) {
    if(position > 3 || digit > 9) return;
    displayBuffer[position] = DIGITS[digit];
    displayTypes[position] = 0;
}

void Display7Seg::displayLetter(uint8_t position, char letter) {
    if(position > 3 || !isalpha(letter)) return;
    uint8_t index = toupper(letter) - 'A';
    if(index < 26) {
        displayBuffer[position] = LETTERS[index];
        displayTypes[position] = 1;
    }
}

void Display7Seg::displayString(const char* str, unsigned long duration) {
    size_t len = strlen(str);
    for(size_t i = 0; i < len && i < 4; i++) {
        if(isdigit(str[i])) {
            displayDigit(i, str[i] - '0');
        } else if(isalpha(str[i])) {
            displayLetter(i, str[i]);
        }
        delay(duration);
    }
}

void Display7Seg::displayNumber(int number, bool leadingZeros) {
    if (number < 0 || number > 9999) {
        for(int i = 0; i < 4; i++) {
            displayBuffer[i] = 0x00;
            displayTypes[i] = 0;
        }
        return;
    }

    int digits[4];
    for(int i = 3; i >= 0; i--) {
        digits[i] = number % 10;
        number /= 10;
    }

    bool significantDigit = false;
    for(int i = 0; i < 4; i++) {
        if (digits[i] != 0) {
            significantDigit = true;
        }

        if (significantDigit || leadingZeros || i == 3) {
            displayBuffer[i] = DIGITS[digits[i]];
        } else {
            displayBuffer[i] = SEG_OFF;
        }
        displayTypes[i] = 0;
    }
}

void Display7Seg::refresh() {
    static uint8_t currentDigit = 0;
    sendDataToSegment(SEGMENT_SELECT[currentDigit], displayBuffer[currentDigit]);
    currentDigit = (currentDigit + 1) % 4;
}

void Display7Seg::sendDataToSegment(byte segmentNo, byte hexValue) {
    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, hexValue);
    shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, segmentNo);
    digitalWrite(LATCH_PIN, HIGH);
} 