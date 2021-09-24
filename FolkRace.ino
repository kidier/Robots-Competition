//#include "funkcje.h"
#include <SoftWire.h>
#include <vl53l0x_class.h>

//SILNIKI
#define L1 PB8
#define L2 PB9
#define R1 PB7
#define R2 PB6
#define L 0
#define R 1
int prevmili=millis();
//RGB
#define R PA3
#define G PA2
#define B PA1

//VL53L0X
#define SCL PB10
#define SDA PB11
#define XSHUTL PB12
#define XSHUTM PB14
#define XSHUTR PA8
#define GPIOL PB13
#define GPIOM PB15
#define GPIOR PA9

//IR
#define IRL PB0
#define IRR PB1

//BATERIA
#define BAT PA7

//START
#define START PB4

//PROGI
#define batThreshold 2137
#define irThreshold 1500
#define vlThreshold 600
#define halfPeriod 500

//FLAGI
bool rBlinking = false;
int rState = LOW;
int STATE = 0;
bool DIR = 1;
bool TIMEOUT = 0;
int ind=0;
int lLine;
int rLine;
int v= 50;
int timing=0;
bool strona=true;
//CZASY
uint32_t rPrevMillis = 0;
uint32_t prevMillis = 0;
int timeLeft = 0;
#define TURN 500;
#define SCAN 1000;
#define RETREAT 300;

SoftWire WIRE1(PB10, PB11, SOFT_FAST);
VL53L0X sensorL(&WIRE1, XSHUTL, GPIOL); //WIRE, XSHUT, INT
VL53L0X sensorM(&WIRE1, XSHUTM, GPIOM);
VL53L0X sensorR(&WIRE1, XSHUTR, GPIOR);

uint32_t distanceL;
uint32_t distanceM;
uint32_t distanceR;
bool kontra=false;
void setup()
{
  //PWM
  
  pinMode(L1, PWM);
  pinMode(L2, PWM);
  pinMode(R1, PWM);
  pinMode(R2, PWM);
  //DIGITAL
  pinMode(PC13, OUTPUT);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  //ANALOG

  //VL53L0X
  int status;
  Serial.begin(9600);
  WIRE1.begin();
  
  sensorL.VL53L0X_Off();
  sensorM.VL53L0X_Off();
  sensorR.VL53L0X_Off();

  status = sensorL.InitSensor(0x10);
  //sensorL.VL53L0X_Off();
  
  while(status)
  {
     digitalWrite(R,HIGH);
    digitalWrite(G,HIGH);
    digitalWrite(B,HIGH);
     delay(500);
     digitalWrite(R,LOW);
    delay(500);   
    Serial.println("L Init sensor_vl53l0x failed...");
  }
delay(150);
  status = sensorR.InitSensor(0x18);
  //sensorR.VL53L0X_Off();  
  
    while(status)
  {
    digitalWrite(R,HIGH);
    digitalWrite(G,HIGH);
    digitalWrite(B,HIGH);
    delay(500);
     digitalWrite(R,LOW);
    delay(500);  
    Serial.println("R Init sensor_vl53l0x failed...");
  }
  delay(150);
 status = sensorM.InitSensor(0x26);
  
    while(status)
  {
    digitalWrite(R,HIGH);
    digitalWrite(G,HIGH);
    digitalWrite(B,HIGH);
   delay(500);
     digitalWrite(R,LOW);
    delay(500);   
    Serial.println("M Init sensor_vl53l0x failed...");
  }

  digitalWrite(R, LOW);
  digitalWrite(G, LOW);
  digitalWrite(B, LOW);
  

  DIR = analogRead(IRL) % 2;
  digitalWrite(R, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(B, HIGH);
  while(millis()<5000){}
  power(L,0,70);
power(R,0,70);
delay(100);

}


/////////////////////////////////////////////////////////////////////////////////////////LOOP

void loop()
{
  int rng=350;
sensorL.GetDistance(&distanceL);
sensorM.GetDistance(&distanceM);
sensorR.GetDistance(&distanceR);
//lLine = analogRead(IRL);
//rLine = analogRead(IRL);

Serial.print(distanceL);

Serial.print("  ");

Serial.print(distanceM);

Serial.print("  ");

Serial.println(distanceR);

if(distanceL==0){
  distanceL=2600;
}
if(distanceM==0){
  distanceM=2600;
}
if(distanceR==0){
  distanceR=2600;
}

}
