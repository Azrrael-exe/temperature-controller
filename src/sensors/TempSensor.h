#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H

#include <Arduino.h>

class TempSensor {
public:
    // Constructor
    explicit TempSensor(uint8_t pin) : pin(pin) {}

    // Métodos virtuales puros
    virtual void begin() = 0;
    virtual float readTemperature() = 0;
    virtual float getLastReading() const = 0;

    // Destructor virtual
    virtual ~TempSensor() = default;

protected:
    uint8_t pin;
};

#endif // TEMP_SENSOR_H
