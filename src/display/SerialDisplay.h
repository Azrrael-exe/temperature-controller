#ifndef SERIAL_DISPLAY_H
#define SERIAL_DISPLAY_H

#include <Arduino.h>
#include "Display.h"

class SerialDisplay : public Display {
private:
    Stream& stream;
    
public:
    SerialDisplay(Stream& serialStream) : stream(serialStream) {}
    
    void begin() override {}
    void clear() override { stream.println("----"); }
    
    void displayNumber(int number, bool leadingZeros = false) override {
        if (leadingZeros) {
            stream.print(number < 1000 ? "0" : "");
            stream.print(number < 100 ? "0" : "");
            stream.print(number < 10 ? "0" : "");
            stream.println(number);
        } else {
            stream.println(number);
        }
    }
    
    void refresh() override {}
};

#endif 