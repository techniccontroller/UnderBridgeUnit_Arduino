#include <Wire.h>
#include <Servo.h>
#include <NXShield.h>
#include <NXTTouch.h>

NXShield nxshield;
NXTTouch touch1;
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
  myservo.attach(8);  
  // Warten auf das Drücken des GO-Buttons
  Serial.println ("Press GO button to continue");
  nxshield.waitForButtonPress(BTN_GO);
  // Motoren reseten
  touch1.init( &nxshield, SH_BBS1 );
  nxshield.bank_b.motorReset(); 
  
} 
 
 
void loop() 
{
  // LED blickt einmal für eine Sekunde ROT auf
  nxshield.ledSetRGB(8,0,0);
  delay(1000);
  nxshield.ledSetRGB(0,0,0);
  delay(1000);
  /*for(int l = 90; l<180;l++){
      myservo.write(l);
      if(nxshield.getButtonState(BTN_LEFT)){
        l=128;
      }
      delay(100);
  }
  delay(2000);
  for(int l = 180; l>90;l--){
      myservo.write(l);
      if(nxshield.getButtonState(BTN_LEFT)){
        l=90;
      }
      delay(100);
  }*/
  pos = 90;
  while(true){
    if(touch1.isPressed() && nxshield.getButtonState(BTN_GO)){
        if(pos>0){
          pos--;
          myservo.write(pos);
        }
        delay(100);
    }
    else if(touch1.isPressed()){
        if(pos<180){
          pos++;
          myservo.write(pos);
        }
        delay(100);
    }  
  }
}
