#include <Wire.h>
#include "MPU6050.h"
#include <NewPing.h>

MPU6050 mpu;

// Timers
unsigned long timer = 0;
float timeStep = 0.01;
// Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;
float yaw = 0;


//Serial communication
String ToSendStr = "";


//Encoder
static int pinA = 2; // Our first hardware interrupt pin is digital pin 2
static int pinB = 3; // Our second hardware interrupt pin is digital pin 3
volatile byte aFlag = 0; // let's us know when we're expecting a rising edge on pinA to signal that the encoder has arrived at a detent
volatile byte bFlag = 0; // let's us know when we're expecting a rising edge on pinB to signal that the encoder has arrived at a detent (opposite direction to when aFlag is set)
int encoderPos = 0; //this variable stores our current value of encoder position. Change to int or uin16_t instead of byte if you want to record a larger range than 0-255
int oldEncPos = 0; //stores the last encoder position value so we can compare to the current reading and see if it has changed (so we know when to print to the serial monitor)
volatile byte reading = 0;
int deltaEncPos =0;

//Ultrasonic sensor
#define TRIGGER1_PIN  4  // Arduino pin tied to trigger pin on ping sensor.
#define ECHO1_PIN     5  // Arduino pin tied to echo pin on ping sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar1(TRIGGER1_PIN, ECHO1_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
unsigned int ping1Speed = 50; // How frequently are we going to send out a ping (in milliseconds). 50ms would be 20 times a second.
unsigned long ping1Timer;     // Holds the next ping time.
int distanceR = 0, distanceL = 0;

#define TRIGGER2_PIN  10  // Arduino pin tied to trigger pin on ping sensor.
#define ECHO2_PIN     11  // Arduino pin tied to echo pin on ping sensor.
NewPing sonar2(TRIGGER2_PIN, ECHO2_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
unsigned int ping2Speed = 50; // How frequently are we going to send out a ping (in milliseconds). 50ms would be 20 times a second.
unsigned long ping2Timer;     // Holds the next ping time.


//MetalDetector 
#define MMRelay_pin 12
#define Sound_pin 13

#define MetalDecetor_pin 6
int MineR = 0, MineL = 0;
int RelayTimer = 0, LastTimer =0;


//Temprature
float tempC;
int Tempreading;
#define tempPin A0



void setup() 
{
  
  Serial.begin(115200);
  // Initialize MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
    // Calibrate gyroscope. The calibration must be at rest.
  // If you don't want calibrate, comment this line.
  mpu.calibrateGyro();
  // Set threshold sensivty. Default 3.
  // If you don't want use threshold, comment this line or set 0.
  mpu.setThreshold(0);

  //ENCODER
  pinMode(pinA, INPUT_PULLUP); // set pinA as an input, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
  pinMode(pinB, INPUT_PULLUP); // set pinB as an input, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
  attachInterrupt(0,PinA,RISING); // set an interrupt on PinA, looking for a rising edge signal and executing the "PinA" Interrupt Service Routine (below)
  attachInterrupt(1,PinB,RISING); // set an interrupt on PinB, looking for a rising edge signal and executing the "PinB" Interrupt Service Routine (below)


  pinMode(MMRelay_pin, OUTPUT);
  pinMode(Sound_pin, OUTPUT);
 
  pinMode(tempPin, INPUT);
  pinMode(TRIGGER1_PIN, OUTPUT);  //Arduino pin tied to trigger pin on ping sensor.
  pinMode(ECHO1_PIN,INPUT);        // Arduino pin tied to echo pin on ping sensor.
  pinMode(TRIGGER2_PIN, OUTPUT);  //Arduino pin tied to trigger pin on ping sensor.
  pinMode(ECHO2_PIN,INPUT);        // Arduino pin tied to echo pin on ping sensor.
  pinMode(MetalDecetor_pin, INPUT);

   /*ULTRASONIC PULSE IN
   pinMode(trig1Pin, OUTPUT); // Sets the trigPin as an Output
   pinMode(echo1Pin, INPUT); // Sets the echoPin as an Input*/
    ping1Timer = millis(); // Start now.
    ping2Timer = millis(); // Start now.


    //TEMPRATURE
    analogReference(INTERNAL);
   
}
int LastIMUTimer = 0;
void loop()
{
  /*IMU*/
  timer = millis();
  // Read normalized values
  Vector norm = mpu.readNormalizeGyro();
  // Calculate Pitch, Roll and Yaw
  pitch = pitch + norm.YAxis * timeStep;
  roll = roll + norm.XAxis * timeStep;
  yaw = yaw + norm.ZAxis * timeStep;
  if(roll>360) roll = roll-360; //care for the change from 0-->360 or 360-->0 near to north
  if(roll<0)roll = roll+360;
   /*END OF IMU*/


//ENCODER
   deltaEncPos = encoderPos-oldEncPos;
  if(oldEncPos != encoderPos)
  {
    oldEncPos = encoderPos;    
  }

  
 //METAL DETECTOR
      MetalDetector();

//Temprature sensor
  Tempreading = analogRead(tempPin);
  tempC = Tempreading / 9.31;

   
 //ULTRASONIC SENSOR
 if(MineR)
   UltrasonicSensorR();

 if(MineL)
   UltrasonicSensorL();

 
 //SERIAL DATA to send to the other arduino (Ethernet-sheilded arduino for sending it wirelessly to the control station)
  ToSendStr = String(roll) +"," + String(deltaEncPos) + "," + String(encoderPos) + "," + String(MineL) + "," + String(MineR) + "," + String(distanceL) + "," + String(distanceR) + ","+ String(tempC);
  Serial.println(ToSendStr);
  
  // Wait to full timeStep period
 
   delay((timeStep*1000) - (millis() - timer));


}
