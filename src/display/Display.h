#ifndef DISPLAY_H
#define DISPLAY_H

class Display {
public:
    virtual ~Display() = default;
    
    // Métodos abstractos que deben ser implementados por las clases derivadas
    virtual void begin() = 0;
    virtual void clear() = 0;
    virtual void displayNumber(int number, bool leadingZeros = false) = 0;
    virtual void refresh() = 0;
};

#endif 