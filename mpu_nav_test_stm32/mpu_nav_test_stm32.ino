//this is for stm32f103c8 bp
#include <SPI.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps612.h"

#define LED_BUILTIN PC13
MPU6050 mpu;

const uint8_t INTERRUPT_PIN=PB12; 
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer
volatile bool mpuInterrupt = false;   

int16_t quaternion[4];  // [w, x, y, z]         quaternion container


int16_t packet[4];  

void dmpDataReady() {
  mpuInterrupt = true;
}
void setup_mpu(){
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
  #endif
  Wire.setClock(4000000);
  
  mpu.initialize();
  Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
    /*
    mpu.setXGyroOffset(-59);
    mpu.setYGyroOffset(-114);
    mpu.setZGyroOffset(63);
    mpu.setXAccelOffset(-1898);
    mpu.setYAccelOffset(984);
    mpu.setZAccelOffset(1794);
    */
  devStatus = mpu.dmpInitialize();
  if (devStatus == 0) {
    mpu.CalibrateAccel(6);
    mpu.CalibrateGyro(6);
      
    Serial.println();
    mpu.PrintActiveOffsets();
    Serial.println(F("Enabling DMP..."));
    mpu.setDMPEnabled(true);
    Serial.print(F("Enabling interrupt detection (Arduino external interrupt "));
    Serial.print(digitalPinToInterrupt(INTERRUPT_PIN));
    Serial.println(F(")..."));
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();
    Serial.println(F("DMP ready! Waiting for first interrupt..."));
    dmpReady = true;
    packetSize = mpu.dmpGetFIFOPacketSize();
  } else {
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(devStatus);
    Serial.println(F(")"));
  }
}


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(1000000);
  setup_mpu();
}

// the loop function runs over and over again forever
void loop() {
  //digitalWrite(LED_BUILTIN, 1);  
  //delay(1);                    
  long t=millis();
  for(int id=0; id<1; id++){
  mpu.dmpGetCurrentFIFOPacket(fifoBuffer);
  mpu.dmpGetQuaternion(&packet[0], fifoBuffer); 
  }
  long p=millis();
  Serial.println(p-t);
  
  //for(int i=0; i<4; i++)
    //Serial.printf("%d, ", packet[i]);
  //delay(1);
  digitalWrite(LED_BUILTIN, 0);  
  
  
}
