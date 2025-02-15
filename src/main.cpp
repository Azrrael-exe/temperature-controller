#include <Arduino.h>

void setup() {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(115200);
}

void loop() {
  // Print "Hello World!" every second
  Serial.println("Hello World!");
  delay(1000);  // Wait for 1 second
}
