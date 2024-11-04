

 /*
This is an arduino code to control custom made home tank feeding/training chamber. It controls a servo for feeding and a peristaltic pump for odor delivery. NT- 23/11/2018
*/ 

int motorPinA = 4; // pin that turns on the pump 1
int motorPinB = A3; // pin that turns on the pump 2
int motorPinC = A1; // pin that turns on the pump 3
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

int valvePinA = 7;
int valvePinB = 6;
int valvePinC = 5;



void setup() {
  pinMode(motorPinA, OUTPUT);  // CS+ #1 (R)
  pinMode(motorPinB, OUTPUT); // CS+ #2 (A)
  pinMode(motorPinC, OUTPUT); // CS- (H)
  pinMode(foodPin, OUTPUT);// set pin9 to an output for feeding
  pinMode(ledPin, OUTPUT); // set pin 13 to an output to use it to turn on the LED
  pinMode(valvePinA, OUTPUT);
  pinMode(valvePinB, OUTPUT);
  pinMode(valvePinC, OUTPUT);
}

void loop() {
  digitalWrite(motorPinA,HIGH);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(5000);
  digitalWrite(motorPinA,LOW);
  digitalWrite(LED_BUILTIN,LOW);
  delay(1000);
  
  digitalWrite(motorPinB,HIGH);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(5000);
  digitalWrite(motorPinB,LOW);
  digitalWrite(LED_BUILTIN,LOW);
  delay(1000);
  
  digitalWrite(motorPinC,HIGH);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(5000);
  digitalWrite(motorPinC,LOW);
  digitalWrite(LED_BUILTIN,LOW);
  delay(1000);
  
  digitalWrite(valvePinA,HIGH);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(1000);
  digitalWrite(valvePinA,LOW);
  digitalWrite(LED_BUILTIN,LOW);
  delay(1000);
  
  digitalWrite(valvePinB,HIGH);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(1000);
  digitalWrite(valvePinB,LOW);
  digitalWrite(LED_BUILTIN,LOW);
  delay(1000);
  
  digitalWrite(valvePinC,HIGH);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(1000);
  digitalWrite(valvePinC,LOW);
  digitalWrite(LED_BUILTIN,LOW);
  delay(1000);
}
