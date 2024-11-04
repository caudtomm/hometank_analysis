/*
This is an arduino code to control custom made home tank feeding/training chamber. It controls a servo for feeding and a peristaltic pump for odor delivery. NT- 23/11/2018
*/ 

int motorPinA = A0; // pin that turns on the pump 1
int motorPinB = A1; // pin that turns on the pump 2
int motorPinC = A2; // pin that turns on the pump 3
int foodPin = 9; // pin for feeder
//long watertime = 60 ; // pump ON, in seconds
long odortime = 30 ; // pump ON, in seconds
long waittimeShort =2364 ;//2300; // 40min (normal ITI) - a trial length (watertime is added in)
long waittimeLong = 38304 ; //10h40 (length of lights off period)-trial time, in seconds
long waittimeBegin = 900; //in seconds, 15min (how long after you start to run the arduino, the first training happens, optional)
long waittimeEnd = 1464; //in seconds, 25min -trial, if you do have a waittimeBegin, to make sure when the code loops, ITI ends up waittimeShort (watertime is added in)
int interval =4; // interval between odor delivery and food delivery, in seconds (depends on tubing length and flow rate)
int feedTime = 2; //how long the feeding will happen, in seconds
int ledPin = 13;//LED blink pin 



void setup() {
  pinMode(motorPinA, OUTPUT);  // CS+ #1 (R)
  pinMode(motorPinB, OUTPUT); // CS+ #2 (A)
  pinMode(motorPinC, OUTPUT); // CS- (H)
  pinMode(foodPin, OUTPUT);// set pin9 to an output for feeding
  pinMode(ledPin, OUTPUT); // set pin 13 to an output to use it to turn on the LED

}

void loop() {
  digitalWrite(motorPinA,HIGH);
  delay(5000);
  digitalWrite(motorPinA,LOW);

  digitalWrite(motorPinB,HIGH);
  delay(5000);
  digitalWrite(motorPinB,LOW);
  
  digitalWrite(motorPinC,HIGH);
  delay(5000);
  digitalWrite(motorPinC,LOW);

  delay(20000);
}
