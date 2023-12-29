#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);        // select the pins used on the LCD panel
// To use ArduinoGraphics APIs, please include BEFORE Arduino_LED_Matrix
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"
#include <AccelStepper.h> //Include the AccelStepper library

ArduinoLEDMatrix matrix;


#define Pressure 2 //Low Pressure Relay
#define Cylinder 0 //Pneumatic Switch
#define MP1  A1 // IN1 on the ULN2003
#define MP2  A2 // IN2 on the ULN2003
#define MP3  A3 // IN3 on the ULN2003
#define MP4  A4 // IN4 on the ULN2003
#define MotorInterfaceType 8 // Define the interface type as 8 = 4 wires * step factor (2 for half step)
AccelStepper stepper = AccelStepper(MotorInterfaceType, MP1, MP3, MP2, MP4);//Define the pin sequence (IN1-IN3-IN2-IN4)
const int SPR = 2048;//Steps per revolution

#define MOSFET 11 //Nitrogen Boiler



int button;

void setup() {

pinMode(A5,INPUT);

  // put your setup code here, to run once:
  stepper.setMaxSpeed(1600);//Set the maximum motor speed in steps per second
  stepper.setAcceleration(1000);//Set the maximum acceleration in steps per second^2

lcd.begin(16, 2);   // start the library
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("CISR-EM");
lcd.setCursor(0,8);
lcd.print("Intializing");
matrix.begin();

  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  char text[] = "OK!";
  matrix.textFont(Font_4x6);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(text);
  matrix.endText();
matrix.endDraw();
//pinmodes for relays


pinMode(Pressure, OUTPUT); //Low Pressure Relay
pinMode(Cylinder, OUTPUT); //Blow Off

//turn on nitrogen heater
analogWrite(MOSFET, 100); //Start Heater

//

//Make sure unit starts in correct configuration
  //Clear out the lines
digitalWrite(Cylinder, LOW);
digitalWrite(Pressure, LOW);



//Starting position
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Ready   ");
//lcd.setCursor(0,8);
//lcd.print("HP   LP   PP");
//lcd.setCursor(8,0);
//lcd.print("Heat:");




button = 0;
}



void loop() {
  // put your main code here, to run repeatedly:

button = analogRead(A0);


//lcd.setCursor(8,3);  //checking button press code
//lcd.print(button);

 matrix.beginDraw();

  matrix.stroke(0xFFFFFFFF);
  matrix.textScrollSpeed(50);


if ((button > 750) && (button < 875)) {
//Reset
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Reset  ");
digitalWrite(Pressure, LOW); //close blow off
delay(200); //time for relay to close
digitalWrite(Cylinder, LOW); //blow off high pressure
delay(200); //time for pressure release
digitalWrite(Cylinder, HIGH); //close blow off
delay(200);
digitalWrite(Cylinder, LOW); //blow off high pressure
delay(200); //time for pressure release
digitalWrite(Cylinder, HIGH); //close blow off
delay(200);
digitalWrite(Cylinder, LOW); //blow off high pressure
delay(200); //time for pressure release
digitalWrite(Cylinder, HIGH); //close blow off
delay(200);
digitalWrite(Cylinder, LOW); //blow off high pressure
delay(200); //time for pressure release
digitalWrite(Cylinder, HIGH); //close blow off
delay(200);
digitalWrite(Cylinder, LOW); //blow off high pressure
delay(200); //time for pressure release
digitalWrite(Cylinder, HIGH); //close blow off
delay(200);
digitalWrite(Cylinder, LOW); //blow off high pressure
delay(200); //time for pressure release
digitalWrite(Cylinder, HIGH); //close blow off
delay(200);
digitalWrite(Cylinder, LOW); //blow off high pressure
delay(200); //time for pressure release
digitalWrite(Cylinder, HIGH); //close blow off
delay(200);
digitalWrite(Cylinder, LOW); //blow off high pressure







analogWrite(MOSFET, 100);  //Heater back to medium setting
lcd.setCursor(13,0);
lcd.print("50%");

digitalWrite(Pressure, LOW);
  matrix.textFont(Font_5x7);
  matrix.beginText(0, 1, 0xFF0000);
  matrix.println("  Reset  ");
  matrix.endText(SCROLL_LEFT);
  stepper.moveTo(SPR/6); //Set the target motor position (i.e. turn motor for 3 full revolutions)
  stepper.runToPosition(); // Run the motor to the target position

while(digitalRead(A5) == LOW){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Align Tweezer");
  delay(50); 

}
while(digitalRead(A5)==HIGH){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("In Position");
  stepper.moveTo(-SPR/6); //Set the target motor position (i.e. turn motor for 3 full revolutions)
  stepper.runToPosition(); // Run the motor to the target position

}
while(digitalRead(A5)== HIGH) {};

  stepper.moveTo(SPR/6); //Set the target motor position (i.e. turn motor for 3 full revolutions)
  stepper.runToPosition(); // Run the motor to the target position

}

if ((button > 350) && (button < 450)) {
//Start Slam
while(digitalRead(A5) == LOW){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Blot Switch");  
}
while(digitalRead(A5)==HIGH){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Blotting");
  stepper.moveTo(-SPR/6); //Set the target motor position (i.e. turn motor for 3 full revolutions)
  stepper.runToPosition(); // Run the motor to the target position
}
while(digitalRead(A5)== HIGH) {};

  stepper.moveTo(SPR/6); //Set the target motor position (i.e. turn motor for 3 full revolutions)
  stepper.runToPosition(); // Run the motor to the target position
delay(500);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Slam   ");
digitalWrite(Pressure, HIGH);
digitalWrite(Cylinder, HIGH);
analogWrite(MOSFET, 0); //Heater off during pneumatic transit
analogWrite(MOSFET, 255); //Nitrogen Vapor Max
lcd.setCursor(13,0);
lcd.print("Max");
  matrix.textFont(Font_5x7);
  matrix.beginText(0, 1, 0xFF0000);
  matrix.println("  Slam  ");
  matrix.endText(SCROLL_LEFT);
delay(3000);


//Pressure Dance

lcd.setCursor(0,0);
lcd.print("Cycle   ");
  matrix.textFont(Font_5x7);
  matrix.beginText(0, 1, 0xFF0000);
  matrix.println("  Resting  ");
  matrix.endText(SCROLL_LEFT);
digitalWrite(Pressure, LOW);
delay(200); //time for relay to close
digitalWrite(Cylinder, LOW); //blow off high pressure
delay(200); //time for pressure release
digitalWrite(Cylinder, HIGH); //close blow off
delay(200);
digitalWrite(Cylinder, LOW); //blow off high pressure
delay(200); //time for pressure release
digitalWrite(Cylinder, HIGH); //close blow off
delay(200);
digitalWrite(Cylinder, LOW); //blow off high pressure
delay(200); //time for pressure release
digitalWrite(Cylinder, HIGH); //close blow off
delay(200);
digitalWrite(Cylinder, LOW); //blow off high pressure
delay(200); //time for pressure release
digitalWrite(Cylinder, HIGH); //close blow off
delay(200);
digitalWrite(Cylinder, LOW); //blow off high pressure
delay(200); //time for pressure release
digitalWrite(Cylinder, HIGH); //close blow off
delay(200);
digitalWrite(Cylinder, LOW); //blow off high pressure
delay(200); //time for pressure release
digitalWrite(Cylinder, HIGH); //close blow off
delay(200);
digitalWrite(Cylinder, LOW); //blow off high pressure
delay(200); //time for pressure release
digitalWrite(Cylinder, HIGH); //close blow off
delay(200);
digitalWrite(Cylinder, LOW); //blow off high pressure
delay(200); //time for pressure release
digitalWrite(Cylinder, HIGH); //close blow off

}


if ((button > 150) && (button < 250)) {
//Retract
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Retract ");

digitalWrite(Cylinder, LOW);
delay(300);
digitalWrite(Pressure, HIGH); //open blow off


analogWrite(MOSFET, 100);  //Heater back to medium setting
lcd.setCursor(13,0);
lcd.print("50%");
delay(5000);

digitalWrite(Pressure, LOW);

  matrix.textFont(Font_5x7);
  matrix.beginText(0, 1, 0xFF0000);
  matrix.println("  Retract!  ");
  matrix.endText(SCROLL_LEFT);
}

if ((button < 675)  && (button > 600)) {

digitalWrite(Pressure, LOW);
  matrix.textFont(Font_5x7);
  matrix.beginText(0, 1, 0xFF0000);
  matrix.println("  Safe!  ");
  matrix.endText(SCROLL_LEFT);
//const char text[] = "    Hello World!    ";


}


  matrix.endDraw();

//lcd.setCursor(0,0);
//lcd.print(button);

//delay(1000);



}

