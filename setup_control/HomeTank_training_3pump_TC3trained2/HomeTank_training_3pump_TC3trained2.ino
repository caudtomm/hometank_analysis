/*
This is an arduino code to control custom made home tank feeding/training chamber. It controls a servo for feeding and a peristaltic pump for odor delivery. NT- 23/11/2018
*/ 

int motorPinA = A1; // pin that turns on the pump 2
int motorPinB = A2; // pin that turns on the pump 3
int motorPinC = A0; // pin that turns on the pump 1
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
	pinMode(motorPinA, OUTPUT);  // CS+ #1
  pinMode(motorPinB, OUTPUT); // CS+ #2
  pinMode(motorPinC, OUTPUT); // CS-
  pinMode(foodPin, OUTPUT);// set pin9 to an output for feeding
	pinMode(ledPin, OUTPUT); // set pin 13 to an output to use it to turn on the LED

}

void loop() {
 
  delay(waittimeBegin*1000); // seconds to milliseconds

  // CS+ #1 Trial #1
  CSplus1trial();
  delay(waittimeShort*1000);
  // CS- Trial #1 
  CSminustrial();
  delay(waittimeShort*1000);
  // CS- Trial #2 
  CSminustrial();
  delay(waittimeShort*1000);     
  
  // CS+ #2 Trial #1
  CSplus2trial();
  delay(waittimeLong*1000);    // NIGHT BREAK
  // CS- Trial #3
  CSminustrial();
  delay(waittimeShort*1000);
  // CS- Trial #4 
  CSminustrial();
  delay(waittimeShort*1000);   

  // CS+ #1 Trial #2
  CSplus1trial();
  delay(waittimeShort*1000);  
  // CS- Trial #5
  CSminustrial();
  delay(waittimeShort*1000);   
  // CS- Trial #6
  CSminustrial();
  delay(waittimeShort*1000);  
  
  // CS+ #2 Trial #2
  CSplus2trial();
  delay(waittimeShort*1000);  
  // CS- Trial #7
  CSminustrial();
  delay(waittimeShort*1000);  
  // CS- Trial #8 
  CSminustrial();
  delay(waittimeShort*1000);
  

  // CS+ #1 Trial #3
  CSplus1trial();
  delay(waittimeShort*1000);    
  // CS- Trial #9 
  CSminustrial();
  delay(waittimeShort*1000);   
  // CS- Trial #10 
  CSminustrial();
  delay(waittimeShort*1000);  
  
  // CS+ #2 Trial #3
  CSplus2trial();
  delay(waittimeShort*1000);   
  // CS- Trial #11
  CSminustrial();
  delay(waittimeShort*1000);  
  // CS- Trial #12 
  CSminustrial();
  delay(waittimeShort*1000);     
  
  // CS+ #1 Trial #4
  CSplus1trial();
  delay(waittimeShort*1000);  
  // CS- Trial #13
  CSminustrial();
  delay(waittimeShort*1000);   
  // CS- Trial #14
  CSminustrial(); 
  delay(waittimeShort*1000);
  
  // CS+ #2 Trial #4
  CSplus2trial();
  delay(waittimeShort*1000);
  // CS- Trial #15
  CSminustrial();
  delay(waittimeShort*1000);
  // CS- Trial #16
  CSminustrial();
  delay(waittimeShort*1000);  
  
  // CS+ #1 Trial #5
  CSplus1trial();
  delay(waittimeLong*1000);    // NIGHT BREAK
  // CS- Trial #17
  CSminustrial();
  delay(waittimeShort*1000);
  // CS- Trial #18
  CSminustrial();
  delay(waittimeShort*1000);  
  
  // CS+ #2 Trial #5
  CSplus2trial();
  delay(waittimeShort*1000);  
  // CS- Trial #19
  CSminustrial();
  delay(waittimeShort*1000);    
  // CS- Trial #20 
  CSminustrial();
  delay(waittimeShort*1000);   

  // CS+ #1 Trial #6
  CSplus1trial();
  delay(waittimeShort*1000);    
  // CS- Trial #21
  CSminustrial();
  delay(waittimeShort*1000);  
  // CS- Trial #22
  CSminustrial();
  delay(waittimeShort*1000);
  
  // CS+ #2 Trial #6
  CSplus2trial();
  delay(waittimeShort*1000);  
  // CS- Trial #23
  CSminustrial();
  delay(waittimeShort*1000);  
  // CS- Trial #24 
  CSminustrial();
  delay(waittimeShort*1000);   
  

  // CS+ #1 Trial #7
  CSplus1trial();
  delay(waittimeShort*1000);    
  // CS- Trial #25
  CSminustrial();
  delay(waittimeShort*1000);    
  // CS- Trial #26
  CSminustrial();
  delay(waittimeShort*1000);
  
  // CS+ #2 Trial #7
  CSplus2trial();
  delay(waittimeShort*1000);
  // CS- Trial #27
  CSminustrial();
  delay(waittimeShort*1000);   
  // CS- Trial #28
  CSminustrial();
  
  delay(waittimeEnd*1000);  

}

void CSplus1trial() {
  // deliver odor (LED sustained ON)
  digitalWrite(ledPin, HIGH);   // turn the LED on 
  digitalWrite(motorPinA, HIGH); // turn on the pump 
  delay(odortime*1000);        // seconds to milliseconds
  digitalWrite(motorPinA, LOW);  // turn off the pump
  digitalWrite(ledPin, LOW);    // turn the LED off 
  // wait and deliver food (LED sustained ON)
  delay(interval*1000);
  digitalWrite(ledPin, HIGH);   // turn the LED on 
  digitalWrite(foodPin, HIGH);   // turn the LED on 
  delay(feedTime*1000);
  digitalWrite(foodPin, LOW);    // turn the LED off 
  digitalWrite(ledPin, LOW);    // turn the LED off 
}

void CSplus2trial() {
  // deliver odor (LED sustained ON)
  digitalWrite(ledPin, HIGH);   // turn the LED on 
  digitalWrite(motorPinB, HIGH); // turn on the pump 
  delay(odortime*1000);        // seconds to milliseconds
  digitalWrite(motorPinB, LOW);  // turn off the pump
  digitalWrite(ledPin, LOW);    // turn the LED off 
  // wait and deliver food (LED sustained ON)
  delay(interval*1000);
  digitalWrite(ledPin, HIGH);   // turn the LED on 
  digitalWrite(foodPin, HIGH);   // turn the LED on 
  delay(feedTime*1000);
  digitalWrite(foodPin, LOW);    // turn the LED off 
  digitalWrite(ledPin, LOW);    // turn the LED off 
}

void CSminustrial() {
  digitalWrite(ledPin, HIGH);   // turn the LED on 
  digitalWrite(motorPinC, HIGH); // turn on the pump 
  delay(odortime*1000);        // seconds to milliseconds
  digitalWrite(motorPinC, LOW);  // turn off the pump
  digitalWrite(ledPin, LOW);    // turn the LED off
  delay(interval*1000);
  delay(feedTime*1000);
}
