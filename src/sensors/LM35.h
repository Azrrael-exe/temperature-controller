#ifndef LM35_H
#define LM35_H

#include "TempSensor.h"

class LM35 : public TempSensor {
private:
    float lastReading;
    static const int BUFFER_SIZE = 10;
    float readings[BUFFER_SIZE];
    int readIndex = 0;
    bool bufferFilled = false;

public:
    // Constructor
    explicit LM35(uint8_t pin) : TempSensor(pin), lastReading(0.0f) {
        // Inicializar el buffer con ceros
        for(int i = 0; i < BUFFER_SIZE; i++) {
            readings[i] = 0.0f;
        }
    }

    // Implementación de los métodos virtuales
    void begin() override;
    float readTemperature() override;
    float getLastReading() const override {
        return lastReading;
    }
};

#endif // LM35_H 