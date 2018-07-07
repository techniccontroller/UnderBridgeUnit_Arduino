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
  servoVentil.attach(3);
  servoArm.attach(2);
  servoPumpe.attach(12);
  Serial.println ("Press GO button to continue");
  while(!(touchR.isPressed() == true && touchL.isPressed() == true));

  
  // reset motors
  nxshield.bank_a.motorReset();
  nxshield.bank_b.motorReset();
  ausgefahren = false;
} 
 
 
void loop() 
{
  delay(1000);
  servoVentil.write(90);
  servoPumpe.write(90);
  Serial.println("Stufe1");
  while(!(touchR.isPressed() == true && touchL.isPressed() == true));
  Serial.println("Stufe2");
  for(int l = 90; l>52;l--){
      servoVentil.write(l);
      delay(100);
  }
  servoPumpe.write(120);
  delay(1000);
  while(!(touchR.isPressed() == true && touchL.isPressed() == true));
}
