#include <Wire.h>
#include <Servo.h>
#include <NXShield.h>
#include <NXTTouch.h>

NXShield nxshield;
NXTTouch touch1;
NXTTouch touch2;
Servo myservo;  
 
int pos = 90;    
int mode = 0;

void setup() 
{ 
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  Serial.begin(9600);
  nxshield.init(SH_SoftwareI2C);
  
  Serial.println ("Press GO button to continue");
  nxshield.waitForButtonPress(BTN_GO);
  myservo.attach(6);  
  // initialize the analog sensors.
  touch1.init( &nxshield, SH_BBS1 );
  touch2.init( &nxshield, SH_BBS2 );
  // reset motors
  nxshield.bank_b.motorReset(); 
  
} 
 
 
void loop() 
{
  while(true){
  switch(mode){
    // MODE 1 -------------------------------------------------------------------//
    case 0:
      nxshield.ledSetRGB(8,0,0);
      if(nxshield.getButtonState(BTN_LEFT)){
        mode=2;
        delay(900);
      }
      else if(nxshield.getButtonState(BTN_RIGHT)){
        mode=1;
        delay(900);
      }
      else if(touch1.isPressed() && nxshield.getButtonState(BTN_GO)){
        analogWrite(2,0);
        analogWrite(3,255);
      }
      else if(touch1.isPressed()){
        analogWrite(2,255);
        analogWrite(3,0);
      } 
      else if(touch2.isPressed() && nxshield.getButtonState(BTN_GO)){
        analogWrite(4,0);
        analogWrite(5,255);
      }
      else if(touch2.isPressed()){
        analogWrite(4,255);
        analogWrite(5,0);
      } 
      else {
        nxshield.bank_b.motorStop(SH_Motor_2, SH_Next_Action_Brake);
        nxshield.bank_b.motorStop(SH_Motor_1, SH_Next_Action_Brake);
        analogWrite(2,0);
        analogWrite(3,0);
        analogWrite(4,0);
        analogWrite(5,0);
      }
      delay(20);
      break;
      
    // MODE 2 --------------------------------------------------------------------------//
    case 1:
      nxshield.ledSetRGB(0,8,0);
      if(nxshield.getButtonState(BTN_LEFT)){
        mode=0;
        delay(900);
      }
      else if(nxshield.getButtonState(BTN_RIGHT)){
        mode=2;
        delay(900);
      }
      else if(touch1.isPressed() && nxshield.getButtonState(BTN_GO)){
        nxshield.bank_b.motorStop(SH_Motor_1, SH_Next_Action_Brake);
        nxshield.bank_b.motorRunUnlimited(SH_Motor_2, SH_Direction_Forward,50);
      }
      else if(touch1.isPressed()){
        nxshield.bank_b.motorStop(SH_Motor_1, SH_Next_Action_Brake);
        nxshield.bank_b.motorRunUnlimited(SH_Motor_2, SH_Direction_Reverse,50);
      } 
      else if(touch2.isPressed() && nxshield.getButtonState(BTN_GO)){
        nxshield.bank_b.motorStop(SH_Motor_2, SH_Next_Action_Brake);
        nxshield.bank_b.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward,30);
      }
      else if(touch2.isPressed()){
        nxshield.bank_b.motorStop(SH_Motor_2, SH_Next_Action_Brake);
        nxshield.bank_b.motorRunUnlimited(SH_Motor_1, SH_Direction_Reverse,30);
      } 
      else {
        nxshield.bank_b.motorStop(SH_Motor_2, SH_Next_Action_Brake);
        nxshield.bank_b.motorStop(SH_Motor_1, SH_Next_Action_Brake);
        analogWrite(2,0);
        analogWrite(3,0);
        analogWrite(4,0);
        analogWrite(5,0);
      }
      delay(20);
      break;
      
    // MODE 3 --------------------------------------------------------------------------//
    case 2:
      nxshield.ledSetRGB(0,0,8);
      if(touch1.isPressed() && nxshield.getButtonState(BTN_GO)){
        if(myservo.read()>0){
          
          myservo.write(myservo.read()-1);
        }
        delay(100);
      }
      else if(touch1.isPressed()){
        if(myservo.read()<180){
          
          myservo.write(myservo.read()+1);
        }
        delay(100);
      }
      else if(nxshield.getButtonState(BTN_LEFT)){
        mode=1;
        delay(900);
      }
      else if(nxshield.getButtonState(BTN_RIGHT)){
        mode=0;
        delay(900);
      }
      else {
        nxshield.bank_b.motorStop(SH_Motor_2, SH_Next_Action_Brake);
        nxshield.bank_b.motorStop(SH_Motor_1, SH_Next_Action_Brake);
        analogWrite(2,0);
        analogWrite(3,0);
        analogWrite(4,0);
        analogWrite(5,0);
      }
      delay(20);
      break;
  }
    
  /*
  if(nxshield.getButtonState(BTN_LEFT) && nxshield.getButtonState(BTN_GO)){
    nxshield.bank_b.motorStop(SH_Motor_1, SH_Next_Action_Brake);
    nxshield.bank_b.motorRunUnlimited(SH_Motor_2, SH_Direction_Forward,50);
  }
  
  else if(nxshield.getButtonState(BTN_RIGHT) && nxshield.getButtonState(BTN_GO)){
    nxshield.bank_b.motorStop(SH_Motor_2, SH_Next_Action_Brake);
    nxshield.bank_b.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward,30);
  }
  else if(nxshield.getButtonState(BTN_LEFT)){
    nxshield.bank_b.motorStop(SH_Motor_1, SH_Next_Action_Brake);
    nxshield.bank_b.motorRunUnlimited(SH_Motor_2, SH_Direction_Reverse,50);
  }
  else if(nxshield.getButtonState(BTN_RIGHT)){
    nxshield.bank_b.motorStop(SH_Motor_2, SH_Next_Action_Brake);
    nxshield.bank_b.motorRunUnlimited(SH_Motor_1, SH_Direction_Reverse,30);
  }
  
  else if(touch1.isPressed() && nxshield.getButtonState(BTN_GO)){
    analogWrite(2,0);
    analogWrite(3,255);
  }
  else if(touch1.isPressed()){
    analogWrite(2,255);
    analogWrite(3,0);
  } 
  else if(touch2.isPressed() && nxshield.getButtonState(BTN_GO)){
    analogWrite(4,0);
    analogWrite(5,255);
  }
  else if(touch2.isPressed()){
    analogWrite(4,255);
    analogWrite(5,0);
  } 
  else {
    nxshield.bank_b.motorStop(SH_Motor_2, SH_Next_Action_Brake);
    nxshield.bank_b.motorStop(SH_Motor_1, SH_Next_Action_Brake);
    analogWrite(2,0);
    analogWrite(3,0);
    analogWrite(4,0);
    analogWrite(5,0);
  }
  delay(20);*/
  }
}
