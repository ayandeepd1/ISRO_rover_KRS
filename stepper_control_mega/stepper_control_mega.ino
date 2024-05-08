// DualMotorShield.pde
// -*- mode: C++ -*-
//
// Shows how to run 2 simultaneous steppers
// using the Itead Studio Arduino Dual Stepper Motor Driver Shield
// model IM120417015
// This shield is capable of driving 2 steppers at 
// currents of up to 750mA
// and voltages up to 30V
// Runs both steppers forwards and backwards, accelerating and decelerating
// at the limits.
//
// Copyright (C) 2014 Mike McCauley
// $Id:  $

#include <AccelStepper.h>

// The X Stepper pins
#define STEPPER1_DIR_PIN A9 //ydir
#define STEPPER1_STEP_PIN A8//ystep
// The Y stepper pins
#define STEPPER2_DIR_PIN A1//zdir
#define STEPPER2_STEP_PIN A0//zstep

// Define some steppers and the pins the will use
AccelStepper stepper1(AccelStepper::DRIVER, STEPPER1_STEP_PIN, STEPPER1_DIR_PIN);
AccelStepper stepper2(AccelStepper::DRIVER, STEPPER2_STEP_PIN, STEPPER2_DIR_PIN);

void setup()
{  
    Serial.begin(115200);
    stepper1.setMaxSpeed(1000.0);
    stepper1.setSpeed(1000.0);
    stepper1.setAcceleration(800.0);
    stepper1.moveTo(800);
    stepper1.run();
    
    stepper2.setMaxSpeed(1000.0);
    stepper2.setSpeed(1000.0);
    stepper2.setAcceleration(800.0);
    stepper2.moveTo(800);
    stepper2.run();
    
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
    */
     Serial.print("1: d_to_go:"); Serial.print(stepper1.distanceToGo());
     Serial.print(", curr_pos:"); Serial.println(stepper1.currentPosition());
     
     if (stepper1.distanceToGo() == 0)
	    stepper1.moveTo(-stepper1.currentPosition());
     
     Serial.print("2: d_to_go:"); Serial.print(stepper2.distanceToGo());
     Serial.print(", curr_pos:"); Serial.println(stepper2.currentPosition());
     if (stepper2.distanceToGo() == 0)
	    stepper2.moveTo(-stepper2.currentPosition());
    
    stepper1.run();
    stepper2.run();
    
}
