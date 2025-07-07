import processing.serial.*; //Import Serial Library
PImage img; //Image Object
Serial port; //Serial Port Object

void setup()
{
  size(640, 256); //Size of HSV Image
  img = loadImage("hsv.jpg"); //Load in Background Image
  port = new Serial(this, "COM4", 9600); //Open Serial port
}

void draw()
{
  background(0); //Black Background
  image(img, 0, 0); //Overlay image
}

void mousePressed()
{
  color c = get(mouseX, mouseY); //Get the RGB color where mouse was pressed
  int r = int(map(red(c), 0, 255, 0, 100));
  int g = int(map(green(c), 0, 255, 0, 100));
  int b = int(map(blue(c), 0, 255, 0, 100));
  String colors = r+","+g+","+b+"\n"; //extract values from color
  print(colors); //print colors for debugging
  port.write(colors); //Send values to Arduino
}
