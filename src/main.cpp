#include <Arduino.h>
#include "display/Display.h"
#include "display/Display7Seg.h"
#include "sensors/TempSensor.h"
#include "sensors/LM35.h"
#include "display/SerialDisplay.h"

#define LATCH_PIN 4
#define CLK_PIN   7
#define DATA_PIN  8

LM35 lm35(A0);
// Display7Seg display(LATCH_PIN, CLK_PIN, DATA_PIN);
SerialDisplay serialDisplay(Serial);

unsigned long lastUpdate = 0;
const unsigned long UPDATE_INTERVAL = 5000;
int testNumber = 0;

void setup() {
    Serial.begin(115200);
    lm35.begin();
    // display.begin();
    serialDisplay.begin();
}

void printTemperature(TempSensor &tempSensor, Display &display) {
    display.displayNumber(tempSensor.readTemperature());
}

void loop() {
    unsigned long currentMillis = millis();
    
    if (currentMillis - lastUpdate >= UPDATE_INTERVAL) {
        int temp = lm35.readTemperature();
        // printTemperature(lm35, display);
        printTemperature(lm35, serialDisplay);
        lastUpdate = currentMillis;
    }
    
    // display.refresh();
    delay(5);
}
