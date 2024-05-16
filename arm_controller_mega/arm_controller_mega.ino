#include <Servo.h>
#include <AccelStepper.h>
#include <IBusBM.h>

#define ly 0
#define lx 2
#define ry 1
#define rx 3
#define vra 4
#define vrb 6

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

IBusBM IBus; // IBus object
volatile int val[10];
int servo_status[4]={servo1_centre, servo2_centre, servo3_centre, servo4_centre};
int stepper_status[]={0, 0};
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

AccelStepper stepper_z(AccelStepper::DRIVER, STEPPERZ_STEP_PIN, STEPPERZ_DIR_PIN);
AccelStepper stepper_y(AccelStepper::DRIVER, STEPPERY_STEP_PIN, STEPPERY_DIR_PIN);

bool led_status=0; 

void update_vals(){
  for(int i=0; i<10; i++){
    val[i] = IBus.readChannel(i);   
  } 
}

void move_stepper(int dvra, int dvrb, int dvrc){
  if(dvra==-1 && stepper_status[1]-200>-base_max_limit){
    stepper_status[0]-=200;
    stepper_y.moveTo(stepper_status[0]);
  }      
  else if(dvra==1 && stepper_status[0]+200<base_max_limit){
    stepper_status[0]+=200;
    stepper_y.moveTo(stepper_status[0]);
  }
  else if(dvra==0)
    stepper_y.moveTo(stepper_status[0]);
  
  if(dvrb==1 && stepper_status[1]+200<gripper_max_limit){
    stepper_status[1]+=200;
    stepper_z.moveTo(stepper_status[1]);
  }
  else if(dvrc==1 && stepper_status[1]-200>0){
    stepper_status[1]-=200;
    stepper_z.moveTo(stepper_status[1]);
  }
  //else{
    //do nothing
  //}
  
  
    
  while(stepper_y.distanceToGo()!=0)
      stepper_y.run();
  while(stepper_z.distanceToGo()!=0)
      stepper_z.run();
  
}

void move_servo(int drx, int dry, int dlx, int dly){
  if(drx==1 && servo_status[0]+5<servo1_external)
    servo_status[0]+=5;
  else if(drx==-1 && servo_status[0]-5>servo1_internal)
    servo_status[0]-=5;

  if(dry==1 && servo_status[1]+5<servo2_external)
    servo_status[1]+=5;
  else if(dry==-1 && servo_status[1]-5>servo2_internal)
    servo_status[1]-=5;

  if(dlx==1 && servo_status[2]+5<servo3_external)
    servo_status[2]+=5;
  else if(dlx==-1 && servo_status[2]-5>servo3_internal)
    servo_status[2]-=5;

  if(dly==1 && servo_status[3]+5<servo4_external)
    servo_status[3]+=5;
  else if(dly==-1 && servo_status[3]-5>servo4_internal)
    servo_status[3]-=5;  

  servo1.write(servo_status[0]);
  servo2.write(servo_status[1]);              
  servo3.write(servo_status[2]);              
  servo4.write(servo_status[3]);              
  
}

void setup_servo(){
  servo1.attach(servo1_chan);  
  servo2.attach(servo2_chan);  
  servo3.attach(servo3_chan);  
  servo4.attach(servo4_chan);  
}
void setup_stepper(){
  stepper_z.setMaxSpeed(2500.0);
  stepper_z.setSpeed(2500.0);
  stepper_z.setAcceleration(2500.0);
  
  stepper_y.setMaxSpeed(2000.0);
  stepper_y.setSpeed(2000.0);
  stepper_y.setAcceleration(1600.0);
  
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  
  Serial.begin(115200);
  IBus.begin(Serial2);
  setup_servo();
  setup_stepper();
  /*
  servo1.write(servo1_centre);
  servo2.write(servo2_centre);              
  servo3.write(servo3_internal);              
  servo4.write(servo4_internal);              
  
   */
 
  
}

void loop() {
  digitalWrite(LED_BUILTIN, led_status);
  update_vals();
  int nrx=map(val[rx], 800, 1800, -1, 1);  
  int nry=map(val[ry], 800, 1800, -1, 1);
  int nlx=map(val[lx], 800, 1800, -1, 1);  
  int nly=map(val[ly], 800, 1800, -1, 1);
  int nvra=map(val[vra], 800, 1800, -1, 1);  
  int nvrb=map(val[vrb], 1000, 1800, -1, 1);
  int nvrc=map(val[vrb+1], 1000, 1800, -1, 1);
  
  move_stepper(nvra, nvrb, nvrc);
  move_servo(nrx, nry, nlx, nly);
  Serial.print(nrx);
  Serial.print(" ");
  Serial.print(nry);
  Serial.print(" ");
  Serial.print(nlx);
  Serial.print(" ");
  Serial.print(nly);
  Serial.print(" ");
  Serial.print(nvra);
  Serial.print(" ");
  Serial.print(nvrb);
  Serial.print(" ");
  Serial.print(nvrc);
  Serial.print(" ");
  //Serial.print();
  for(int i=0; i<4; i++){
    Serial.print(servo_status[i]);
    Serial.print(" ");
  }
  Serial.print(stepper_status[1]);
  Serial.println();
  
  led_status ^=1;
  delay(1);
  //stepper_y.run();
  //stepper_z.run();
    
}
