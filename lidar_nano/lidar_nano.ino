#include "Adafruit_VL53L0X.h"

#define range_interval 200
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

bool sleep_flag=0;
void setup() {
  Serial.begin(1000000);

  while (! Serial) {
    delay(1);
  }
  
  Serial.println("Lidar_Sensor");
  if (!lox.begin()) 
    while(1){
      Serial.println(F("Lidar_Failed"));
      delay(200);
    }
  lox.startRangeContinuous();
  for(int i=0; i<5; i++){
    digitalWrite(13,1);
    Serial.println(F("Lidar_Ready")); 
    delay(100);
    digitalWrite(13,0);
    delay(100);
  }
}

long tx=millis();
  
void loop() {
  if(!sleep_flag){
    long t1=millis();
    if(lox.isRangeComplete() && millis()-tx>range_interval) {
      Serial.print(lox.readRange());Serial.print("\n");
      tx=millis();    
    }
      
    long t2=millis();
    //Serial.print(" ");
    //Serial.println(t2-t1);
  }
  if(Serial.available()>0){
      char c=Serial.read();
      switch(c){
        case 'h':Serial.print("Lidar_Sensor\n");break;
        case 's':sleep_flag=1; break;
        case 'w':sleep_flag=0; break;
        case 'i':Serial.print("baud:1000000\n");
                 Serial.print("options: \n");
                 Serial.print("\th : show sensor name \n");
                 Serial.print("\ts : sleep \n");
                 Serial.print("\tw : wakeup \n");
                 Serial.print("\ti : show this message\n");break;
        case '\n':break;
        case '\r':break;
        default:Serial.print("error\n");
      }
    }
}
