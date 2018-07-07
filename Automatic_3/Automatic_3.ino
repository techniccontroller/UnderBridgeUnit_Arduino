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
  einfahren();
  for(int l = 90; l<128;l++){
    servoVentil.write(l);
    delay(100);
  } 
  delay(1000);
  servoVentil.write(90);
  servoPumpe.write(90);
  Serial.println("Stufe1");
  while(!(touchR.isPressed() == true && touchL.isPressed() == true));
  Serial.println("Stufe2");
  for(int l = 128; l>52;l--){
    servoVentil.write(l);
    delay(100);
  }
  servoPumpe.write(125);
  delay(1000);
  while(!(touchR.isPressed() == true && touchL.isPressed() == true));
  delay(1000);
  Serial.println("Betriebsbereit");
  durationRCA = pulseIn(RCpinA, HIGH);
  
  while(true){
    for(int i = 0; i < 10; i++){
      durationRCA = durationRCA + pulseIn(RCpinA, HIGH);
      durationRCL = durationRCL + pulseIn(RCpinL, HIGH);
      delay(1);
    } 
    durationRCL = (unsigned long) durationRCL/11; 
    durationRCA = (unsigned long) durationRCA/11;
    Serial.println(durationRCA);
    Serial.println(ausgefahren);
    if(ausgefahren == true){
      Serial.println("Ausgefahren!!");
      // Wenn Button rechts gedrückt, dann ab
      if(touchR.isPressed() == true && touchL.isPressed() == false){
        Serial.println("ab");
        nxshield.bank_a.motorRunUnlimited(motorE,SH_Direction_Forward,20);
      }
      // Wenn Button links gedrückt, dann auf
      else if(touchR.isPressed() == false && touchL.isPressed() == true){
        Serial.println("auf");
        nxshield.bank_a.motorRunUnlimited(motorE,SH_Direction_Reverse,20);
      }
      else{
        nxshield.bank_a.motorStop(motorE, SH_Next_Action_BrakeHold);
      }
      // Wenn beide Button gedrückt, dann ServoArm ein/aus
      if(touchR.isPressed() == true && touchL.isPressed() == true){
        time = millis();
        while(touchR.isPressed() == true && touchL.isPressed() == true);
        timediff = millis() - time;
        if(timediff < 2000){
          if(!servoArmEin){
            for(int k = 70; k<180;k++){
              servoArm.write(k);
              delay(100);
            }
            servoArmEin = true;
          }
          else{
            for(int k = 180; k>70;k--){
              servoArm.write(k);
              delay(100);
            }
            servoArmEin = false;
          }
        }
        else{
          if(servoArmEin){
            for(int k = 180; k>70;k--){
              servoArm.write(k);
              delay(100);
            }
            einfahren();
            ausgefahren = false;
          }
          else if(!servoArmEin){
            einfahren();
            ausgefahren = false;
          }
        }
      }
    }
    if(ausgefahren){
      servoPumpe.write(90);
    }
    else{
      servoPumpe.write(125);
    }
    if(ausgefahren == false && touchR.isPressed() == true && touchL.isPressed() == true){
      ausfahren();
      ausgefahren = true;
    }
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

    }
    
  }
}

void ausfahren(){
  Serial.println("Ausfahren");
  servoPumpe.write(90);
  for(int l = 90; l<128;l++){
    servoVentil.write(l);
    delay(100);
  }

  nxshield.bank_a.motorRunUnlimited(motorA,SH_Direction_Reverse,100);
  while(digitalRead(taster1_A_a) == HIGH);
  nxshield.bank_a.motorStop(motorA, SH_Next_Action_Float);
  delay(200);
  Serial.println("C");
  analogWrite(motorC_a,0);
  analogWrite(motorC_b,255);
  while(digitalRead(taster5_C_a) == HIGH);
  analogWrite(motorC_a,0);
  analogWrite(motorC_b,0);
  delay(200);
  Serial.println("B");
  digitalWrite(motorB_a,LOW);
  digitalWrite(motorB_b,HIGH);
  while(digitalRead(taster3_B_a) == HIGH);
  digitalWrite(motorB_a,LOW);
  digitalWrite(motorB_b,LOW);
  delay(200);
  Serial.println("D");
  analogWrite(motorD_a,100);
  analogWrite(motorD_b,0);
  while(digitalRead(taster7_D_a) == HIGH);
  analogWrite(motorD_a,0);
  analogWrite(motorD_b,0);
}

void einfahren(){
  Serial.println("Einfahren");
  servoPumpe.write(125);

  analogWrite(motorD_a,0);
  analogWrite(motorD_b,255);
  while(digitalRead(taster8_D_e) == HIGH);
  analogWrite(motorD_a,0);
  analogWrite(motorD_b,0);

  Serial.println("Bitte hochfahren");
  while(!(touchR.isPressed() == true && touchL.isPressed() == true)){
    if(touchR.isPressed() == true && touchL.isPressed() == false){
      Serial.println("ab");
      nxshield.bank_a.motorRunUnlimited(motorE,SH_Direction_Forward,20);
    }
    // Wenn Button links gedrückt, dann auf
    else if(touchR.isPressed() == false && touchL.isPressed() == true){
      Serial.println("auf");
      nxshield.bank_a.motorRunUnlimited(motorE,SH_Direction_Reverse,20);
    }
    else{
      nxshield.bank_a.motorStop(motorE, SH_Next_Action_BrakeHold);
    }
  }
  Serial.println("Danke");

  


  digitalWrite(motorB_a,HIGH);
  digitalWrite(motorB_b,LOW);
  while(digitalRead(taster4_B_e) == HIGH);
  digitalWrite(motorB_a,LOW);
  digitalWrite(motorB_b,LOW);
  
  for(int l = 90; l>52;l--){
    servoVentil.write(l);
    delay(100);
  }
  servoPumpe.write(125);
  
  analogWrite(motorC_a,255);
  analogWrite(motorC_b,0);
  while(digitalRead(taster6_C_e) == HIGH);
  analogWrite(motorC_a,0);
  analogWrite(motorC_b,0);
  
  nxshield.bank_a.motorRunUnlimited(motorA,SH_Direction_Forward,100);
  while(digitalRead(taster2_A_e) == HIGH);
  nxshield.bank_a.motorStop(motorA, SH_Next_Action_Float);
  while(!(touchR.isPressed() == true && touchL.isPressed() == true));
  servoPumpe.write(90);
  for(int l = 52; l<90;l++){
    servoVentil.write(l);
    delay(100);
  }
}


