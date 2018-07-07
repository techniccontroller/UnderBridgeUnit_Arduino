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
  nxshield.bank_b.motorRunUnlimited(SH_Motor_2,SH_Direction_Reverse,50);
  while(!touch1.isPressed());
  nxshield.bank_b.motorStop(SH_Motor_2, SH_Next_Action_Brake);
  delay(2000);
  nxshield.bank_b.motorRunUnlimited(SH_Motor_2,SH_Direction_Forward,50);
  while(!touch2.isPressed());
  nxshield.bank_b.motorStop(SH_Motor_2, SH_Next_Action_Brake);
  while(true);
}
