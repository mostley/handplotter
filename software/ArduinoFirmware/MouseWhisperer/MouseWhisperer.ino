#include "PS2Mouse.h"
#define DATA_PIN 12
#define CLOCK_PIN 11

PS2Mouse mouse(CLOCK_PIN, DATA_PIN);

int x=0;
int y=0;

void setup() {
  pinMode(CLOCK_PIN, INPUT);
  pinMode(DATA_PIN, INPUT);
  
  Serial.begin(9600);
  while(!Serial); 
  Serial.println("Setup");
  mouse.initialize();
  Serial.println("initialized");
}

void loop() {
    MouseData data = mouse.readData();
    /*int dx = abs(x - data.position.x);
    int dy = abs(y - data.position.y);
    if (dx > 100 || dy > 100) {
      Serial.print(".");
      x = data.position.x;
      y = data.position.y;
      delay(20);
      return;
    }*/
    Serial.print(data.status, BIN);
    Serial.print("\tx=");
    Serial.print(data.position.x);
    Serial.print("\ty=");
    Serial.print(data.position.y);
    Serial.print("\twheel=");
    Serial.print(data.wheel);
    Serial.println();
    x = data.position.x;
    y = data.position.y;
    delay(20);
}
