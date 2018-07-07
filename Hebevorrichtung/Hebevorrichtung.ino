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
  nxshield.init(SH_HardwareI2C);
  myservo.attach(7);  
  Serial.println ("Press GO button to continue");
  nxshield.waitForButtonPress(BTN_GO);
  nxshield.bank_b.motorReset(); 
  
} 
 
 
void loop() 
{
  nxshield.bank_b.motorRunUnlimited(SH_Motor_2, SH_Direction_Reverse,50);
  while(!nxshield.getButtonState(BTN_LEFT));
  nxshield.bank_b.motorStop(SH_Motor_2, SH_Next_Action_Brake);
  delay(20000);
  //nxshield.bank_b.motorRunDegrees(SH_Motor_2,SH_Direction_Forward,100,180,SH_Completion_Wait_For, SH_Next_Action_Brake);
  //delay(2000);
  
}
