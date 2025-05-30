//Processing Sketch to Read Value and Change Color on the Screen
//Import and initialize serial port library
import processing.serial.*;
Serial port;

float brightness = 0; //For holding value from pot

void setup()
{
  size(500, 500); //Window size
  port = new Serial(this, "COM3", 9600); //Set up serial
  port.bufferUntil('\n'); //Set up port to read until
  //newline
}

void draw()
{
  background(0, 0, brightness); //Updates the window
}

void serialEvent (Serial port)
{
  brightness = float(port.readStringUntil('\n')); //Gets value from Arduino
}
