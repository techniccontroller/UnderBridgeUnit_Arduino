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
  
  Serial.println ("Press GO button to continue");
  nxshield.waitForButtonPress(BTN_GO);
  servoVentil.attach(3);
  servoArm.attach(2);
  // reset motors
  nxshield.bank_a.motorReset();
  nxshield.bank_b.motorReset();
} 
 
 
void loop() 
{
  durationNull = durationRCL = pulseIn(RCpinL, HIGH);
 
  durationRCA = pulseIn(RCpinA, HIGH);
  Serial.println("Naechste");
  Serial.print(durationRCA);
  Serial.print("    ");
  Serial.println(durationRCL);
  delay(200);
  /*while(true){
    
    
    Serial.println(durationRCA);
    /*if(durationRCA == 0){
      ausfahren();
    }
    if(durationRCA < 1400 && durationRCA > 1000 ){
          // Der LKW fährt rückwärts
          Serial.println("rueckwaerts");
          analogWrite(antrieb_b,0);
          
          analogWrite(antrieb_a,255);  
          
    }
    else if(durationRCA > 1600){
          // LKW fängt an vorwärts zu fahren
          Serial.println("vorwaerts");
          
          analogWrite(antrieb_a,0);
          
          analogWrite(antrieb_b,255);    
    }
    else{
      analogWrite(antrieb_a,0);
      analogWrite(antrieb_b,0);
    }
    for(int i = 0; i < 10; i++){
      durationRCL = durationRCL + pulseIn(RCpinL, HIGH);
      delay(1);
    } 
    durationRCL = (unsigned long) durationRCL/11;
    Serial.println(durationRCL);
    Serial.println("Lenken");
    position = nxshield.bank_b.motorGetEncoderPosition(SH_Motor_2);
    posK = ((durationRCL - 1500)/4)*2;
    if((posK - position) >= 0){
       nxshield.bank_b.motorRunDegrees(SH_Motor_2, SH_Direction_Forward, 20, posK - position, SH_Completion_Wait_For, SH_Next_Action_Brake);
          
    }
    if((posK - position) < 0){
    nxshield.bank_b.motorRunDegrees(SH_Motor_2, SH_Direction_Reverse, 20, posK - position, SH_Completion_Wait_For, SH_Next_Action_Brake);
          
    }
    durationRCA = pulseIn(RCpinA, HIGH);
  }
  
}

void ausfahren(){
  Serial.println("Ausfahren");
  
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
  
  while(true);*/
}
