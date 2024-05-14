#include <Servo.h>
#include <AccelStepper.h>

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

#define gripper_max_limit 12000 //+ve goes inside, -ve goes outside
#define base_max_limit 3600   //+ve goes cw, -ve goes ccw

// The Y Stepper pins
#define STEPPERY_DIR_PIN A9 //ydir
#define STEPPERY_STEP_PIN A8//ystep
// The Z stepper pins
#define STEPPERZ_DIR_PIN A1//zdir
#define STEPPERZ_STEP_PIN A0//zstep

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

AccelStepper stepper_z(AccelStepper::DRIVER, STEPPERZ_STEP_PIN, STEPPERZ_DIR_PIN);
AccelStepper stepper_y(AccelStepper::DRIVER, STEPPERY_STEP_PIN, STEPPERY_DIR_PIN);

bool led_status=0; 
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  
  Serial.begin(115200);
    
  servo1.attach(servo1_chan);  
  servo2.attach(servo2_chan);  
  servo3.attach(servo3_chan);  
  servo4.attach(servo4_chan);  

  stepper_z.setMaxSpeed(2000.0);
  stepper_z.setSpeed(2000.0);
  stepper_z.setAcceleration(1600.0);
  
  stepper_y.setMaxSpeed(2000.0);
  stepper_y.setSpeed(2000.0);
  stepper_y.setAcceleration(1600.0);
    
  servo1.write(servo1_centre);
  servo2.write(servo2_centre);              
  servo3.write(servo3_internal);              
  servo4.write(servo4_internal);              
  
  //stepper_z.moveTo(-gripper_max_limit);
  //stepper_y.moveTo(base_max_limit);
  
}

void loop() {
  digitalWrite(LED_BUILTIN, led_status);
  led_status ^=1;
  //stepper_y.run();
  stepper_z.run();
    
}
