import processing.serial.*;
Serial myPort;

PImage logo;

int bgcolor = 0;

void setup(){
size(1, 1);
surface.setResizable(true);
colorMode(HSB, 255);
logo = loadImage("http://arduino.cc/arduino_logo.png");
surface.setSize(logo.width, logo.height);


myPort = new Serial(this, Serial.list()[2], 9600);
}

void draw(){
bgcolor = myPort.read();
println(bgcolor);
background(bgcolor, 255, 255);
image(logo, 0 ,0);
myPort.clear();
}
