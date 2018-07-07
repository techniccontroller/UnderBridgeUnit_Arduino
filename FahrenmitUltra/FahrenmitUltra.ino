#include <Wire.h>
#include <Servo.h>
#include <NXShield.h>


NXShield nxshield; 

Servo myservo;   
int pos = 0;    

int motorB_a = 11;
int motorB_b = 10;
int motorC_a = 5;
int motorC_b = 4;
int motorD_a = 8;
int motorD_b = 9;
int antrieb_a = 6;
int antrieb_b = 7;
SH_Motor motorE = SH_Motor_2;

 
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
  Serial.begin(9600);
  nxshield.init(SH_HardwareI2C);
    
  // Warten auf das Drücken des GO-Buttons
  Serial.println ("Press GO button to continue");
  nxshield.waitForButtonPress(BTN_GO);
  // Motoren reseten
  nxshield.bank_b.motorReset();
  
} 
 
 
void loop() 
{
  // LED blickt einmal für eine Sekunde ROT auf
  
  int  wert;
  digitalWrite(motorB_a,LOW);
  digitalWrite(motorB_b,LOW);
  analogWrite(motorC_a,0);
  analogWrite(motorC_b,0);
  analogWrite(motorD_a,0);
  analogWrite(motorD_b,0);
  while(true){
    for(int i = 0; i < 20; i++){
      wert = wert + sonar1.getDist();
      delay(5);
    }
    wert = wert/20;
    
    Serial.println(wert);
    if(wert < 15 ){
          // Der LKW fährt rückwärts
          Serial.println("rueckwaerts");
          analogWrite(antrieb_b,0);
          
          analogWrite(antrieb_a,200);
            
          
    }
    else if(wert < 35 && wert > 20){
          // LKW fängt an vorwärts zu fahren
          Serial.println("vorwaerts");
          
          analogWrite(antrieb_a,0);
          
          analogWrite(antrieb_b,200);
          
    }
    else if(wert < 50 && wert > 35){
          // LKW fängt an vorwärts zu fahren
          Serial.println("ab");
          nxshield.bank_b.motorRunUnlimited(motorE,SH_Direction_Forward,20);
          //digitalWrite(motorB_b,LOW);
          
          //digitalWrite(motorB_a,HIGH);
          
    }
    else if(wert < 75 && wert > 55){
          // LKW fängt an vorwärts zu fahren
          Serial.println("auf");
          
          //digitalWrite(motorB_a,LOW);
           nxshield.bank_b.motorRunUnlimited(motorE,SH_Direction_Reverse,20);
          //digitalWrite(motorB_b,HIGH);
          
    }
    else{
      analogWrite(antrieb_a,0);
      analogWrite(antrieb_b,0);
      digitalWrite(motorB_a,LOW);    
      digitalWrite(motorB_b,LOW);
      nxshield.bank_b.motorStop(motorE, SH_Next_Action_Brake);
    }
    
  }
 
  
  // Das Programm stoppt
  while(true);
}
