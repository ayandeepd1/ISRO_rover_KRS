#include <IBusBM.h>

#define ly 0
#define lx 2

#define ry 1
#define rx 3

//#define LED_BUILTIN PC13
//HardwareSerial& ibusRcSerial = Serial2;
IBusBM IBus; // IBus object
//HardwareSerial Serial3 (PA10, PB9);
volatile int val[10];
int dx=0 , dy=0;  
void setup() {
  //Serial.begin(1000000);
  IBus.begin(Serial);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
}
void update_vals(){
  for(int i=0; i<10; i++){
    //Serial.print(IBus.readChannel(i));
    //Serial.print(", ");
    //if(abs(IBus.readChannel(i)-val[i]) >30)
     val[i] = IBus.readChannel(i);   
  }
}
void loop() {
  update_vals();
  //if(val[rx]>1800)
    //dx=1;
    //else if(val[rx]<1300)
    //dx=-1;
    //else
    //dx=0;
  int ndx=map(val[rx], 800, 1800, -1, 1);  
  int ndy=map(val[ry], 800, 1800, -1, 1);
  if(ndx!=dx){
    dx=ndx;  
    if(dx==-1)
      Serial.println('l');
    else if(dx==1)
      Serial.println('r');
    else if(dx==0)
      Serial.println('s');
    else 
      Serial.println('s');
    //Serial.print(dx);
    //Serial.print(" ");
    
  }
  if(ndy!=dy){
    dy=ndy;
    if(dx!=0)
      return;
    if(dy==-1)
      Serial.println('b');
    else if(dy==1)
      Serial.println('f');
    else if(dy==0)
      Serial.println('s');
    else 
      Serial.println('s');
    //Serial.print(dy);
    //Serial.print(" ");
  
  }  
  
    
  
  //digitalWrite(LED_BUILTIN, HIGH);
  //digitalWrite(LED_BUILTIN, LOW);
  
}
