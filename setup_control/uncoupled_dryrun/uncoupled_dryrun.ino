/*

*/ 

int motorPinA = A0; // pin that turns on the pump 1
int motorPinB = A1; // pin that turns on the pump 2
int motorPinC = A2; // pin that turns on the pump 3
int foodPin = 9; // pin for feeder
int ledPin = 13; //LED blink pin 

long odortime = 1 ; // pump ON, in seconds
int feedTime = 1; //how long the feeding will happen, in seconds

long currentMillis = 0;    // stores the value of millis() in each iteration of loop()
long previousMotorPinAMillis = 0; // will store last time the motor was updated
long previousMotorPinBMillis = 3000;
long previousMotorPinCMillis = 1500;
unsigned long previousFoodPinMillis = 0;
long previousDaylightMillis = -5000;
long previousOvernightMillis = 0;
unsigned int foodindex = 0; // keeps track of which food delivery
const long MotorPinAInterval = 6; // (40' * 4 trial (repeats every 4 trials) * 60 sec/min) - 30 s (odortime) [s]
const long MotorPinBInterval = 6; // (40' * 4 trial (repeats every 4 trials) * 60 sec/min) - 30 s (odortime) [s]
const long MotorPinCInterval = 3; // (40' * 2 trial (repeats every 2 trials) * 60 sec/min) - 30 s (odortime) [s]
const long FoodPinInterval[] = {8,11,3,16,7,16,5,6,9,5,7,8,8,6,6}; // inter-food intervals in sec
long DaylightInterval = 17;//50400; // = 14h, how long is a day cycle in sec
long OvernightInterval = 5;//36000; // = 10h, how long is a night cycle in sec


void setup() {
  pinMode(motorPinA, OUTPUT);  // mock CS+ #1
  pinMode(motorPinB, OUTPUT); // mock CS+ #2
  pinMode(motorPinC, OUTPUT); // mock CS-
  pinMode(foodPin, OUTPUT);// set pin9 to an output for feeding
  pinMode(ledPin, OUTPUT); // set pin 13 to an output to use it to turn on the LED
  Serial.begin(9600);
}

void loop() {

  currentMillis = millis();   // capture the latest value of millis()
                              //   this is equivalent to noting the time from a clock
                              //   use the same time for all LED flashes to keep them synchronized

  updateCSplus1channel();
  updateCSplus2channel();
  updateCSminuschannel();
  
  updateFOODchannel();

  // overnight pause
  if (currentMillis - previousDaylightMillis - previousOvernightMillis >= DaylightInterval*1000) {
    digitalWrite(motorPinA,LOW);
    digitalWrite(motorPinB,LOW);
    digitalWrite(motorPinC,LOW);
    digitalWrite(foodPin,LOW);
    digitalWrite(ledPin,LOW);
    
//    digitalWrite(ledPin, HIGH);
    Serial.println(OvernightInterval*1000);
    delay(OvernightInterval*1000);
    Serial.println("done");
//    digitalWrite(ledPin, LOW);

    previousDaylightMillis += DaylightInterval*1000;
    previousOvernightMillis += OvernightInterval*1000;
  }

}

void updateCSplus1channel() {
 
  if (digitalRead(motorPinA) == LOW) {
          // if the Motor is off, we must wait for the interval to expire before turning it on
    if (currentMillis - previousMotorPinAMillis - previousOvernightMillis >= MotorPinAInterval*1000) {
          // time is up, so change the state to HIGH
       digitalWrite(motorPinA,HIGH);
       digitalWrite(ledPin, HIGH);   // turn the LED on 
          // and save the time when we made the change
       previousMotorPinAMillis += MotorPinAInterval*1000;
    }
  }
  else {  // i.e. if motor state is HIGH
  
          // if the motor is on, we must wait for the duration to expire before turning it off
    if (currentMillis - previousMotorPinAMillis - previousOvernightMillis >= odortime*1000) {
          // time is up, so change the state to LOW
       digitalWrite(motorPinA,LOW);
       digitalWrite(ledPin, LOW);   // turn the LED off
          // and save the time when we made the change
       previousMotorPinAMillis += odortime*1000;
    } 
  }
}

void updateCSplus2channel() {

  if (digitalRead(motorPinB) == LOW) {
          // if the Motor is off, we must wait for the interval to expire before turning it on
    if (currentMillis - previousMotorPinBMillis - previousOvernightMillis >= MotorPinBInterval*1000) {
          // time is up, so change the state to HIGH
       digitalWrite(motorPinB,HIGH);
       digitalWrite(ledPin, HIGH);   // turn the LED on 
          // and save the time when we made the change
       previousMotorPinBMillis += MotorPinBInterval*1000;
    }
  }
  else {  // i.e. if motor state is HIGH
  
          // if the motor is on, we must wait for the duration to expire before turning it off
    if (currentMillis - previousMotorPinBMillis - previousOvernightMillis >= odortime*1000) {
          // time is up, so change the state to LOW
       digitalWrite(motorPinB,LOW);
       digitalWrite(ledPin, LOW);   // turn the LED off
          // and save the time when we made the change
       previousMotorPinBMillis += odortime*1000;
    } 
  }
}

void updateCSminuschannel() {

  if (digitalRead(motorPinC) == LOW) {
          // if the Motor is off, we must wait for the interval to expire before turning it on
    if (currentMillis - previousMotorPinCMillis - previousOvernightMillis >= MotorPinCInterval*1000) {
          // time is up, so change the state to HIGH
       digitalWrite(motorPinC,HIGH);
       digitalWrite(ledPin, HIGH);   // turn the LED on 
          // and save the time when we made the change
       previousMotorPinCMillis += MotorPinCInterval*1000;
    }
  }
  else {  // i.e. if motor state is HIGH
  
          // if the motor is on, we must wait for the duration to expire before turning it off
    if (currentMillis - previousMotorPinCMillis - previousOvernightMillis >= odortime*1000) {
          // time is up, so change the state to LOW
       digitalWrite(motorPinC,LOW);
       digitalWrite(ledPin, LOW);   // turn the LED off
          // and save the time when we made the change
       previousMotorPinCMillis += odortime*1000;
    } 
  }
}

void updateFOODchannel() {
  if (digitalRead(foodPin) == LOW) {
    if (currentMillis - previousFoodPinMillis - previousOvernightMillis >= FoodPinInterval[foodindex]*1000) {
      // time is up, so change the state to HIGH
       digitalWrite(foodPin,HIGH);
       digitalWrite(ledPin, HIGH);   // turn the LED on 
          // and save the time when we made the change
       previousFoodPinMillis += FoodPinInterval[foodindex]*1000;
    }
  }
  else {
    if (currentMillis - previousFoodPinMillis - previousOvernightMillis >= feedTime*1000) {
          // time is up, so change the state to LOW
       digitalWrite(foodPin,LOW);
       digitalWrite(ledPin, LOW);   // turn the LED off
          // and save the time when we made the change
       previousFoodPinMillis += feedTime*1000;
       // update food index
       foodindex += 1;
    }
  }
}
