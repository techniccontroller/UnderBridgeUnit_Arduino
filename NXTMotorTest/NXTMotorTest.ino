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
  myservo.attach(7);  
  Serial.println ("Press GO button to continue");
  nxshield.waitForButtonPress(BTN_GO);
  nxshield.bank_b.motorReset(); 
  
} 
 
 
void loop() 
{
  while(true){
  
  if(nxshield.getButtonState(BTN_LEFT) && nxshield.getButtonState(BTN_GO)){
    nxshield.bank_b.motorStop(SH_Motor_1, SH_Next_Action_Brake);
    nxshield.bank_b.motorRunUnlimited(SH_Motor_2, SH_Direction_Forward,50);
  }
  
  else if(nxshield.getButtonState(BTN_RIGHT) && nxshield.getButtonState(BTN_GO)){
    nxshield.bank_b.motorStop(SH_Motor_2, SH_Next_Action_Brake);
    nxshield.bank_b.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward,80);
  }
  else if(nxshield.getButtonState(BTN_LEFT)){
    nxshield.bank_b.motorStop(SH_Motor_1, SH_Next_Action_Brake);
    nxshield.bank_b.motorRunUnlimited(SH_Motor_2, SH_Direction_Reverse,50);
  }
  else if(nxshield.getButtonState(BTN_RIGHT)){
    nxshield.bank_b.motorStop(SH_Motor_2, SH_Next_Action_Brake);
    nxshield.bank_b.motorRunUnlimited(SH_Motor_1, SH_Direction_Reverse,50);
  }
  else {
    nxshield.bank_b.motorStop(SH_Motor_2, SH_Next_Action_Brake);
    nxshield.bank_b.motorStop(SH_Motor_1, SH_Next_Action_Brake);
  }
  delay(20);
  }
}
