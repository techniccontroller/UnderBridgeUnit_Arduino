#include <Wire.h>
#include <Servo.h>
#include <NXShield.h>
#include <NXTTouch.h>


NXShield nxshield;
Servo servoVentil;
Servo servoArm;
Servo servoPumpe;
NXTTouch touchR;
NXTTouch touchL;


int taster1_A_a = 27;
int taster2_A_e = 28;
int taster3_B_a = 23;
int taster4_B_e = 26;
int taster5_C_a = 24;
int taster6_C_e = 29;
int taster7_D_a = 25;
int taster8_D_e = 22;

int motorB_a = 10;
int motorB_b = 11;
int motorC_a = 5;
int motorC_b = 4;
int motorD_a = 8;
int motorD_b = 9;
int antrieb_a = 6;
int antrieb_b = 7;
SH_Motor motorA = SH_Motor_2;
SH_Motor motorE = SH_Motor_1;

int RCpinA = 30;
int RCpinL = 31;
unsigned long durationRCA;
unsigned long durationRCL;
unsigned long durationNull;
int position;
int posK;
bool ausgefahren = false;
bool servoArmEin = false;
unsigned long time;
unsigned long timediff;

char startbyte = 0;
char input = 0;
int arbeitpos = 70;

void setup() 
{ 
  pinMode(RCpinA, INPUT);
  pinMode(RCpinL, INPUT);
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(taster1_A_a,INPUT_PULLUP);
  pinMode(taster2_A_e,INPUT_PULLUP);
  pinMode(taster3_B_a,INPUT_PULLUP);
  pinMode(taster4_B_e,INPUT_PULLUP);
  pinMode(taster5_C_a,INPUT_PULLUP);
  pinMode(taster6_C_e,INPUT_PULLUP);
  pinMode(taster7_D_a,INPUT_PULLUP);
  pinMode(taster8_D_e,INPUT_PULLUP);

  Serial.begin(9600);
  nxshield.init(SH_HardwareI2C);
  touchR.init( &nxshield, SH_BBS1 );
  touchL.init( &nxshield, SH_BBS2 );

  Serial.println ("Press GO button to continue");
  while(!(touchR.isPressed() == true && touchL.isPressed() == true));

  servoVentil.attach(3);
  servoArm.attach(2);
  servoPumpe.attach(12);
  // reset motors
  nxshield.bank_a.motorReset();
  nxshield.bank_b.motorReset();
  ausgefahren = false;
} 


void loop() 
{
  while(true){
    /*for(int i = 0; i < 10; i++){
      durationRCA = durationRCA + pulseIn(RCpinA, HIGH);
      durationRCL = durationRCL + pulseIn(RCpinL, HIGH);
      delay(1);
    } 
    durationRCL = (unsigned long) durationRCL/11; 
    durationRCA = (unsigned long) durationRCA/11;
    if(durationRCA < 1400 && durationRCA > 1000 ){
      // Der LKW fährt rückwärts
      Serial.println("rueckwaerts");
      analogWrite(antrieb_b,0);
      analogWrite(antrieb_a,150);  
    }
    else if(durationRCA > 1600){
      // LKW fängt an vorwärts zu fahren
      Serial.println("vorwaerts");
      analogWrite(antrieb_a,0);
      analogWrite(antrieb_b,150);    
    }
    else{
      analogWrite(antrieb_a,0);
      analogWrite(antrieb_b,0);
    }

   
    Serial.println("Lenken");
    position = nxshield.bank_b.motorGetEncoderPosition(SH_Motor_2);
    posK = ((durationRCL - 1500)/4)*2;
    if((posK - position) >= 0){
      nxshield.bank_b.motorRunDegrees(SH_Motor_2, SH_Direction_Forward, 60, posK - position, SH_Completion_Wait_For, SH_Next_Action_Brake);

    }
    if((posK - position) < 0){
      nxshield.bank_b.motorRunDegrees(SH_Motor_2, SH_Direction_Reverse, 60, posK - position, SH_Completion_Wait_For, SH_Next_Action_Brake);

    }*/
    
    
    // Sprachsteuerung-------------------------------------------------------------------------------------------------------------------------
    if (Serial.available() > 0) {
      // read the incoming byte:
      input = Serial.read();
    }
    switch(input)
    {
    case 10:
      if(digitalRead(taster7_D_a) == LOW){
        analogWrite(motorD_b,0);
        analogWrite(motorD_a,0);
      }
      else{
        analogWrite(motorD_a,150);
        analogWrite(motorD_b,0);
      }
      break;

    case 20:
      if(digitalRead(taster8_D_e) == LOW){
        analogWrite(motorD_b,0);
        analogWrite(motorD_a,0);
      }
      else{
        analogWrite(motorD_a,0);
        analogWrite(motorD_b,255);
      }
      break;

    case 30:
      if(digitalRead(taster5_C_a) == LOW){
        analogWrite(motorC_a,0);
        analogWrite(motorC_b,0);
      }
      else{
        analogWrite(motorC_a,0);
        analogWrite(motorC_b,200);
      }
      break;

    case 40:
      if(digitalRead(taster6_C_e) == LOW){
        analogWrite(motorC_a,0);
        analogWrite(motorC_b,0);
      }
      else{
        analogWrite(motorC_a,150);
        analogWrite(motorC_b,0);
      }
      break;

    case 50:
      if(digitalRead(taster4_B_e) == LOW){
        digitalWrite(motorB_a, LOW);
        digitalWrite(motorB_b, LOW);
      }
      else{
        digitalWrite(motorB_a,HIGH);
        digitalWrite(motorB_b,LOW);
      }
      break;

    case 60:
      if(digitalRead(taster3_B_a) == LOW){
        digitalWrite(motorB_a, LOW);
        digitalWrite(motorB_b, LOW);
      }
      else{
        digitalWrite(motorB_a,LOW);
        digitalWrite(motorB_b,HIGH);
      }
      break;

    case 70:
      analogWrite(antrieb_a,150);
      analogWrite(antrieb_b,0);
      break;

    case 80:
      analogWrite(antrieb_a,0);
      analogWrite(antrieb_b,150);
      break;

    case 90:
      if(digitalRead(taster2_A_e) == LOW){
        nxshield.bank_a.motorStop(motorA, SH_Next_Action_Float);
      }
      else{
        nxshield.bank_a.motorRunUnlimited(motorA,SH_Direction_Forward,100);
      }
      break;

    case 100:
      if(digitalRead(taster1_A_a) == LOW){
        nxshield.bank_a.motorStop(motorA, SH_Next_Action_Float);
      }
      else{
        nxshield.bank_a.motorRunUnlimited(motorA,SH_Direction_Reverse,100);
      }
      break;

    case 110:
      nxshield.bank_a.motorRunUnlimited(motorE,SH_Direction_Reverse,20);
      break;

    case 120:
      nxshield.bank_a.motorRunUnlimited(motorE,SH_Direction_Forward,20);
      break;
     
    case 5:
    if(arbeitpos > 70){
      servoArm.write(arbeitpos);
      arbeitpos--;
      delay(100);
    }
    break;
    
    case 7:
    if(arbeitpos < 180){
      servoArm.write(arbeitpos);
      arbeitpos++;
      delay(100);
    }
    break;
    
    default:
      analogWrite(motorD_a,0);
      analogWrite(motorD_b,0);
      analogWrite(motorC_a,0);
      analogWrite(motorC_b,0);
      digitalWrite(motorB_a,LOW);
      digitalWrite(motorB_b,LOW);
      analogWrite(antrieb_a,0);
      analogWrite(antrieb_b,0);
      nxshield.bank_a.motorStop(motorE, SH_Next_Action_BrakeHold);
      nxshield.bank_a.motorStop(motorA, SH_Next_Action_Float);        
      break;
    }
  }
}



