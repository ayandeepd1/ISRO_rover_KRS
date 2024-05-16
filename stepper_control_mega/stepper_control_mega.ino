
#include <AccelStepper.h>

#define gripper_max_limit 12000 //+ve goes inside, -ve goes outside
#define base_max_limit 3600   //+ve goes cw, -ve goes ccw
// The Y Stepper pins
#define STEPPERY_DIR_PIN A9 //ydir
#define STEPPERY_STEP_PIN A8//ystep
// The Z stepper pins
#define STEPPERZ_DIR_PIN A1//zdir
#define STEPPERZ_STEP_PIN A0//zstep

// Define some steppers and the pins the will use
AccelStepper stepper_z(AccelStepper::DRIVER, STEPPERZ_STEP_PIN, STEPPERZ_DIR_PIN);
AccelStepper stepper_y(AccelStepper::DRIVER, STEPPERY_STEP_PIN, STEPPERY_DIR_PIN);
int stepper_status[]={0, gripper_max_limit};

void move_stepper(int dvra, int dvrb, int dvrc){
  if(dvra==-1){
    stepper_y.moveTo(-100);
  }      
  else if(dvra==1){
    stepper_y.moveTo(100);
  }
  else if(dvra==0)
    stepper_y.moveTo(0);
  
  if(dvrb==1 && stepper_status[1]+100<gripper_max_limit){
    stepper_status[1]+=100;
    stepper_z.moveTo(stepper_status[1]);
  }
  else if(dvrc==1 && stepper_status[1]-100>-gripper_max_limit){
    stepper_status[1]-=100;
    stepper_z.moveTo(stepper_status[1]);
  }
  
    
  while(stepper_y.distanceToGo()!=0)
      stepper_y.run();
  while(stepper_z.distanceToGo()!=0)
      stepper_z.run();
  
}

void setup(){  
  Serial.begin(115200);
  
  stepper_z.setMaxSpeed(2000.0);
  stepper_z.setSpeed(2000.0);
  stepper_z.setAcceleration(1600.0);
  //stepper_z.moveTo(-gripper_max_limit);
  
  stepper_y.setMaxSpeed(2000.0);
  stepper_y.setSpeed(2000.0);
  stepper_y.setAcceleration(1600.0);
  //stepper_y.moveTo(base_max_limit);
  
  //while (stepper1.distanceToGo() != 0)
      
}

void loop()
{   /*
    
    stepper1.moveTo(800);
    stepper1.run();
    
    stepper2.moveTo(800);
    stepper2.run();
    delay(2000);
    
    stepper1.moveTo(0);
    stepper1.run();
    
    stepper2.moveTo(0);
    stepper2.run();
    delay(2000);
    
     Serial.print("1: d_to_go:"); Serial.print(stepper1.distanceToGo());
     Serial.print(", curr_pos:"); Serial.println(stepper1.currentPosition());
     
     if (stepper1.distanceToGo() == 0)
	    stepper1.moveTo(-stepper1.currentPosition());
     
     Serial.print("2: d_to_go:"); Serial.print(stepper2.distanceToGo());
     Serial.print(", curr_pos:"); Serial.println(stepper2.currentPosition());
     if (stepper2.distanceToGo() == 0)
	    stepper2.moveTo(-stepper2.currentPosition());
    */
    move_stepper(0, -1, 1);
    Serial.print(stepper_status[1]);
    Serial.println();
    delay(200);
  
}
