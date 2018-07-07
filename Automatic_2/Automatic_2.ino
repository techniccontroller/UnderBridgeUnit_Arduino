#include <Wire.h>
#include <Servo.h>
#include <NXShield.h>
#include <NXTUS.h>


NXShield nxshield;
Servo servoVentil;
Servo servoArm;
NXTUS sonar1;

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


void setup() 
{ 
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
  nxshield.init(SH_SoftwareI2C);
  
  Serial.println ("Press GO button to continue");
  nxshield.waitForButtonPress(BTN_GO);
  servoVentil.attach(3);
  servoArm.attach(2);  
  // reset motors
  nxshield.bank_a.motorReset(); 
  sonar1.init( &nxshield, SH_BBS2 ); 
  
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
  
  /*for(int l = 90; l>52;l--){
      servoVentil.write(l);
      delay(100);
  }
  while(digitalRead(taster1_A_a) == HIGH);
  
  for(int k = 52; k<90;k++){
      servoVentil.write(k);
      delay(100);
  }
  while(digitalRead(taster1_A_a) == HIGH);
  */
  
  servoArm.write(90);
  
  
  analogWrite(motorD_a,0);
  analogWrite(motorD_b,255);
  while(digitalRead(taster8_D_e) == HIGH);
  analogWrite(motorD_a,0);
  analogWrite(motorD_b,0);
  
  digitalWrite(motorB_a,HIGH);
  digitalWrite(motorB_b,LOW);
  while(digitalRead(taster4_B_e) == HIGH);
  digitalWrite(motorB_a,LOW);
  digitalWrite(motorB_b,LOW);
  
   analogWrite(motorC_a,255);
  analogWrite(motorC_b,0);
  while(digitalRead(taster6_C_e) == HIGH);
  analogWrite(motorC_a,0);
  analogWrite(motorC_b,0);
  
  nxshield.bank_a.motorRunUnlimited(motorA,SH_Direction_Forward,50);
  while(digitalRead(taster2_A_e) == HIGH);
  nxshield.bank_a.motorStop(motorA, SH_Next_Action_Brake);
  
 
  
  delay(1000);
  
  nxshield.bank_a.motorRunUnlimited(motorA,SH_Direction_Reverse,50);
  while(digitalRead(taster1_A_a) == HIGH);
  nxshield.bank_a.motorStop(motorA, SH_Next_Action_Brake);
  
  analogWrite(motorC_a,0);
  analogWrite(motorC_b,255);
  while(digitalRead(taster5_C_a) == HIGH);
  analogWrite(motorC_a,0);
  analogWrite(motorC_b,0);
  
  digitalWrite(motorB_a,LOW);
  digitalWrite(motorB_b,HIGH);
  while(digitalRead(taster3_B_a) == HIGH);
  digitalWrite(motorB_a,LOW);
  digitalWrite(motorB_b,LOW);
  
  analogWrite(motorD_a,100);
  analogWrite(motorD_b,0);
  while(digitalRead(taster7_D_a) == HIGH);
  analogWrite(motorD_a,0);
  analogWrite(motorD_b,0);
  
  int  wert;
  
  while(sonar1.getDist() > 10){
    /*for(int i = 0; i < 10; i++){
      wert = wert + sonar1.getDist();
      delay(5);
    }
    wert = wert/10;*/
    delay(10);
    wert = sonar1.getDist();
    Serial.println(wert);
    if(wert < 30){
          Serial.println("ab");
          nxshield.bank_a.motorRunUnlimited(motorE,SH_Direction_Forward,20);
          
    }
    else if(wert < 70 && wert > 35){
          Serial.println("auf");
          nxshield.bank_a.motorRunUnlimited(motorE,SH_Direction_Reverse,20);
          
    }
    else{
      nxshield.bank_a.motorStop(motorE, SH_Next_Action_Brake);
    }
  }
  
  nxshield.bank_a.motorStop(motorE, SH_Next_Action_Brake);
  
  for(int k = 90; k<180;k++){
      servoArm.write(k);
      delay(100);
  }
  
  while(true){
    /*for(int i = 0; i < 20; i++){
      wert = wert + sonar1.getDist();
      delay(5);
    }
    wert = wert/20;*/
    delay(10);
    wert = sonar1.getDist();
    Serial.println(wert);
    if(wert < 30 ){
          // Der LKW fährt rückwärts
          Serial.println("rueckwaerts");
          analogWrite(antrieb_b,0);
          analogWrite(antrieb_a,200);
    }
    else if(wert < 70 && wert > 35){
          // LKW fängt an vorwärts zu fahren
          Serial.println("vorwaerts");
          analogWrite(antrieb_a,0);
          analogWrite(antrieb_b,200);
    }
    else{
      analogWrite(antrieb_a,0);
      analogWrite(antrieb_b,0);
    }
  }
  while(true);
  
}
