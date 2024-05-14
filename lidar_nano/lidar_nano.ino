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
  if (!lox.startRangeContinuous()) 
    while(1){
      Serial.println(F("Lidar_Failed"));
      delay(200);
    }  
  for(int i=0; i<5; i++){
    digitalWrite(13,1);
    Serial.println(F("Lidar_Ready")); 
    delay(100);
    digitalWrite(13,0);
    delay(100);
  }
}

long t_x=0;
  
void loop() {
  if(!sleep_flag){
    long t_1=millis();
    if(t_1-t_x>range_interval) {
      VL53L0X_RangingMeasurementData_t measure;
      lox.rangingTest(&measure, false);
      if (measure.RangeStatus != 4  && measure.RangeMilliMeter<8180)
        Serial.print(measure.RangeMilliMeter);
      else
        Serial.print("nan");
      Serial.print("\n");
      t_x=millis();    
    }
      
    long t_2=millis();
    //Serial.print(" ");
    //Serial.println(t_2-t_1);
  }
  if(Serial.available()>0){
      char c=Serial.read();
      switch(c){
        case 'h':Serial.print("Lidar_Sensor\n");break;
        case 's':sleep_flag=1; Serial.print("ok\n"); break;
        case 'w':sleep_flag=0; Serial.print("ok\n"); break;
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
