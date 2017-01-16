#ifndef ARDUINO_H
#define ARDUINO_H

#define uint8_t int

const int INPUT = 1;
const int OUTPUT = 2;

const int LOW = 0;
const int HIGH = 1;

void yield() { }

void pinMode(int pin, int value) { }

void digitalWrite(int pin, int value) { }

double micros() {
  return 1.0;
}

#endif /* ARDUINO_H */
