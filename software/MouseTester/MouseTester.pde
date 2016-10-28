import processing.serial.*;

Serial myPort;
String val;

float MIN_POSITION = 3;
float MAX_POSITION = 100;
float FACTOR = 10.0;

void setup()
{
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
}

void draw() {
  float x = clampM(mouseX / FACTOR);
  float y = clampM(mouseY / FACTOR);
  
  String pos = x + ":" + y;
  println(pos);
  
  if ( myPort.available() > 0) 
  {
    myPort.write(pos);
  } 
}

float clampM(float value) {
  float result = value;
  if (result < MIN_POSITION) {
    result = MIN_POSITION;
  } else if (result > MAX_POSITION) {
    result = MAX_POSITION;
  }
  
  return result;
}