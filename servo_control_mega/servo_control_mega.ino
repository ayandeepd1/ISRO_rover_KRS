#include <Servo.h>
#define servo1_chan 46
#define servo2_chan 47
#define servo3_chan 48
#define servo4_chan 49

#define servo1_centre 95 //calibrated
#define servo2_centre 80  //calibrated
#define servo3_centre 94  //calibrated
#define servo4_centre 75  //calibrated

#define servo1_internal 0  //calibrated
#define servo2_internal 0   //calibrated
#define servo3_internal 10   //calibrated
#define servo4_internal 0   //calibrated

#define servo1_external 180 
#define servo2_external 180 //calibrated
#define servo3_external 173 //calibrated
#define servo4_external 180 //calibrated

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;


bool led_status=0; 
void setup() {
  servo1.attach(servo1_chan);  
  servo2.attach(servo2_chan);  
  servo3.attach(servo3_chan);  
  servo4.attach(servo4_chan);  

  pinMode(LED_BUILTIN, OUTPUT);  
  
  servo1.write(servo1_centre);
  servo2.write(servo2_centre);              
  servo3.write(servo3_internal);              
  servo4.write(servo4_internal);              
  ///servo3.write(servo3_centre);              
  //servo4.write(servo4_centre);              
  
}

void loop() {
  digitalWrite(LED_BUILTIN, led_status);
  led_status ^=1;
  //for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    //delay(15);                       // waits 15 ms for the servo to reach the position
  //}
  //delay(1000);
}
