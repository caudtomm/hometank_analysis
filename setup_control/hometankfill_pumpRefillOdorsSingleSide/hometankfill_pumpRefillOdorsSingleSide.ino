

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

long waittimeDay = 86400 ; //24h in seconds

long ML = 820 ; //delay to get 1 ML out of the pumps, in milliseconds
long HUNDRED_ML = 122 ; //delay to get 100 ML out of the system water, in seconds


void setup() {
  pinMode(motorPinA, OUTPUT);  // Ala
  pinMode(motorPinB, OUTPUT); // Arg
  pinMode(motorPinC, OUTPUT); // His
  pinMode(foodPin, OUTPUT);// set pin9 to an output for feeding
  pinMode(ledPin, OUTPUT); // set pin 13 to an output to use it to turn on the LED
  pinMode(valvePinA, OUTPUT);  // water to Ala
  pinMode(valvePinB, OUTPUT);  // water to Arg
  pinMode(valvePinC, OUTPUT);  // water to His

  
  //fill100ML(motorPinA,valvePinA);

  //fill100ML(motorPinB,valvePinB);
  
  //fill100ML(motorPinC,valvePinC);
}


void loop() {
  delay((waittimeDay-HUNDRED_ML*10)*1000);
  fill100ML(motorPinA,valvePinA);

  fill200ML(motorPinB,valvePinB);
  fill200ML(motorPinB,valvePinB);
  
  fill100ML(motorPinC,valvePinC);

  //delay((waittimeDay-HUNDRED_ML*10)*1000);
}

void fill100ML(int motorID, int valveID) {
  delay(3000);
  
  digitalWrite(motorID,HIGH);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(ML);
  digitalWrite(motorID,LOW);
  digitalWrite(LED_BUILTIN,LOW);
  
  delay(1000);

  digitalWrite(valveID,HIGH);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(HUNDRED_ML*1000);
  digitalWrite(valveID,LOW);
  digitalWrite(LED_BUILTIN,LOW);
  
  delay(1000);
}

void fill200ML(int motorID,int valveID) {
  delay(3000);
  
  digitalWrite(motorID,HIGH);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(2*ML);
  digitalWrite(motorID,LOW);
  digitalWrite(LED_BUILTIN,LOW);
  
  delay(1000);

  digitalWrite(valveID,HIGH);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(2*HUNDRED_ML*1000);
  digitalWrite(valveID,LOW);
  digitalWrite(LED_BUILTIN,LOW);
  
  delay(1000);
}
