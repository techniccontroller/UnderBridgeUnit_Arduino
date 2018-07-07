// Programmaufgabe:
// LKW hebt sich an und fährt dann lenkend vorwärts und rückwärts, 
// anschließend senkt er sich wieder ab
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
  // Warten auf das Drücken des GO-Buttons
  Serial.println ("Press GO button to continue");
  nxshield.waitForButtonPress(BTN_GO);
  // Motoren reseten
  nxshield.bank_b.motorReset(); 
  
} 
 
 
void loop() 
{
  // LED blickt einmal für eine Sekunde ROT auf
  nxshield.ledSetRGB(8,0,0);
  delay(1000);
  nxshield.ledSetRGB(0,0,0);
  delay(1000);
  // Ventil wird geöffnet
  for(int l = 90; l<128;l++){
      myservo.write(l);
      delay(100);
  }
  // LED leuchtet blau während der Kompressor zu arbeiten anfängt und den LKW hebt
  nxshield.ledSetRGB(0,8,0);
  delay(100);
  analogWrite(2,0);
  for(int i = 155; i<255; i+=10){
    analogWrite(3,i);
    delay(200);
  }  
  // Kompressor läuft so lange bis der linke Button gedrückt wird
  while(!nxshield.getButtonState(BTN_LEFT));
  analogWrite(3,0);
  // LED geht aus
  nxshield.ledSetRGB(0,0,0);
  // Ventil geht auf Neutralposition
  for(int k = 128; k>90;k--){
      myservo.write(k);
      delay(100);
  }
  // LED leuchtet grün während der LKW fährt
  nxshield.ledSetRGB(0,0,8);
  delay(100);
  // LKW lenkt nach rechts ein
  nxshield.bank_b.motorRunDegrees(SH_Motor_1,SH_Direction_Reverse,70,130,SH_Completion_Wait_For, SH_Next_Action_Brake);
  delay(1000);  
  // LKW fängt an vorwärts zu fahren
  analogWrite(4,0);
  for(int i = 0; i<255; i+=10){
    analogWrite(5,i);
    delay(200);
  }  
  // Während er fährt lenkt er in Neutralpostion und dann nach links
  nxshield.bank_b.motorRunDegrees(SH_Motor_1,SH_Direction_Forward,70,130,SH_Completion_Wait_For, SH_Next_Action_Brake);
  nxshield.bank_b.motorRunDegrees(SH_Motor_1,SH_Direction_Forward,70,130,SH_Completion_Wait_For, SH_Next_Action_Brake);
  delay(1000);
  // Der LKW stoppt und fährt anschließend rückwärts
  analogWrite(5,0);
  for(int i = 0; i<255; i+=10){
    analogWrite(4,i);
    delay(200);
  }
  delay(5000);
  // Nach 5 Sekunde stopp der LKW
  analogWrite(4,0);
  // LKW lenkt in Neutralposition
  nxshield.bank_b.motorRunDegrees(SH_Motor_1,SH_Direction_Reverse,70,130,SH_Completion_Wait_For, SH_Next_Action_Brake);
  delay(2000);
  // Nach 2 Sekunden öffnet sich das Ventil und lässt somit die Luft aus den Zylindern
  // Der LKW senkt sich ab
  for(int i = 90; i>52;i--){
      myservo.write(i);
      delay(100);
  }
  // Das Programm stoppt
  while(true);
}
