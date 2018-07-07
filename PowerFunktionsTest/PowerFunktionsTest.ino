#include <Wire.h>
#include <Servo.h>
#include <NXShield.h>

NXShield nxshield; 
Servo myservo;  
 
int pos = 0;    
 
void setup() 
{ 
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  Serial.begin(9600);
  nxshield.init(SH_SoftwareI2C); 
  Serial.println ("Press GO button to continue");
  nxshield.waitForButtonPress(BTN_GO); 
  
} 
 
 
void loop() 
{
  analogWrite(2,0);
  for(int i = 0; i<255; i+=10){
    analogWrite(3,i);
    delay(200);
  }  
  
  analogWrite(4,0);
  analogWrite(5,255);
  nxshield.ledSetRGB(8,0,0);
  delay(5000);
  nxshield.ledSetRGB(0,0,0);
  analogWrite(2,255);
  analogWrite(3,0);
  analogWrite(4,255);
  analogWrite(5,0);
  delay(5000);
}
