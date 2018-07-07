#include <Wire.h>
#include <Servo.h>
#include <NXShield.h>


NXShield nxshield;
Servo servoVentil;
Servo servoArm;

int taster1_A_a = 27;
int taster2_A_e = 28;
int taster3_B_a = 23;
int taster4_B_e = 26;
int taster5_C_a = 24;
int taster6_C_e = 29;
int taster7_D_a = 25;
int taster8_D_e = 22;

int motorB_a = 7;
int motorB_b = 6;
int motorC_a = 5;
int motorC_b = 4;
int motorD_a = 8;
int motorD_b = 9;
SH_Motor motorA = SH_Motor_2;

void setup() 
{ 
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(taster1_A_a,INPUT_PULLUP);
  pinMode(taster2_A_e,INPUT_PULLUP);
  pinMode(taster3_B_a,INPUT_PULLUP);
  pinMode(taster4_B_e,INPUT_PULLUP);
  pinMode(taster5_C_a,INPUT_PULLUP);
  pinMode(taster6_C_e,INPUT_PULLUP);
  pinMode(taster7_D_a,INPUT_PULLUP);
  pinMode(taster8_D_e,INPUT_PULLUP);
  
  Serial.begin(9600);
  nxshield.init(SH_SoftwareI2C);
  
  Serial.println ("Press GO button to continue");
  nxshield.waitForButtonPress(BTN_GO);
  servoVentil.attach(3);
  servoArm.attach(2);  
  // reset motors
  nxshield.bank_a.motorReset(); 
  
} 
 
 
void loop() 
{
  int valT_A_a = digitalRead(taster1_A_a);
  int valT_A_e = digitalRead(taster2_A_e);
  int valT_B_a = digitalRead(taster3_B_a);
  int valT_B_e = digitalRead(taster4_B_e);
  int valT_C_a = digitalRead(taster5_C_a);
  int valT_C_e = digitalRead(taster6_C_e);
  int valT_D_a = digitalRead(taster7_D_a);
  int valT_D_e = digitalRead(taster8_D_e);
  
  if(valT_A_a == LOW){
    Serial.println("A_a");
    nxshield.bank_a.motorRunUnlimited(motorA,SH_Direction_Reverse,50);
  }
  else if(valT_A_e == LOW){
    Serial.println("A_e");
    nxshield.bank_a.motorRunUnlimited(motorA,SH_Direction_Forward,50);
  }
  else{
    nxshield.bank_a.motorStop(motorA, SH_Next_Action_Brake);
  }
  if(valT_B_a == LOW){
    Serial.println("B_a");
    analogWrite(motorB_a,255);
    analogWrite(motorB_b,0);
  }
  else if(valT_B_e == LOW){
    Serial.println("B_e");
    analogWrite(motorB_a,0);
    analogWrite(motorB_b,255);
  }
  else{
    analogWrite(motorB_a,0);
    analogWrite(motorB_b,0);
  }
  if(valT_C_a == LOW){
    Serial.println("C_a");
    analogWrite(motorC_a,255);
    analogWrite(motorC_b,0);
  }
  else if(valT_C_e == LOW){
    Serial.println("C_e");
    analogWrite(motorC_a,0);
    analogWrite(motorC_b,255);
  }
  else{
    analogWrite(motorC_a,0);
    analogWrite(motorC_b,0);
  }
  if(valT_D_a == LOW){
    Serial.println("D_a");
    analogWrite(motorD_a,255);
    analogWrite(motorD_b,0);
  }
  else if(valT_D_e == LOW){
    Serial.println("D_e");
    analogWrite(motorD_a,0);
    analogWrite(motorD_b,255);
  }
  else{
    analogWrite(motorD_a,0);
    analogWrite(motorD_b,0);
  }
  
  Serial.println("Schleife");  
  delay(200);
}
