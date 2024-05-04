#include <Servo.h>
#define servo1_chan 46
#define servo2_chan 47
#define servo3_chan 48
#define servo4_chan 49

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;


bool led_status=0; 
void setup() {
  servo1.attach(servo1_chan);  ///
  servo2.attach(servo2_chan);  ///
  servo3.attach(servo3_chan);  ///
  servo4.attach(servo4_chan);  ///

  pinMode(LED_BUILTIN, OUTPUT);  
}

void loop() {
  digitalWrite(LED_BUILTIN, led_status);
  led_status ^=1;
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    servo1.write(pos);
    servo2.write(pos);              
    servo3.write(pos);              
    servo4.write(pos);              
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  delay(1000);
}
