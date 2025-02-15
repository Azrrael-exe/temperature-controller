#include "LM35.h"

void LM35::begin() {
    pinMode(pin, INPUT);
}

float LM35::readTemperature() {
    // Leer el valor analógico
    int rawValue = analogRead(pin);
    
    // Convertir a voltaje (asumiendo referencia de 5V y resolución de 10 bits)
    float voltage = (rawValue * 5.0) / 1024.0;
    
    // Convertir a temperatura (LM35 tiene una escala de 10mV/°C)
    float temperature = voltage * 100.0;
    
    // Actualizar el buffer circular
    readings[readIndex] = temperature;
    readIndex = (readIndex + 1) % BUFFER_SIZE;
    
    if (readIndex == 0) {
        bufferFilled = true;
    }
    
    // Calcular el promedio
    float sum = 0;
    int count = bufferFilled ? BUFFER_SIZE : readIndex;
    
    for(int i = 0; i < count; i++) {
        sum += readings[i];
    }
    
    lastReading = sum / count;
    return lastReading;
}