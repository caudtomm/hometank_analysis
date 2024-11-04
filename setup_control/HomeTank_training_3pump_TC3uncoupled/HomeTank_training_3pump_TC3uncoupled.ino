
/*
This is an arduino code to control custom made home tank feeding/training chamber. It controls a servo for feeding and a peristaltic pump for odor delivery. NT- 23/11/2018
*/ 

int motorPinA = A0; // pin that turns on the pump 1
int motorPinB = A1; // pin that turns on the pump 2
int motorPinC = A2; // pin that turns on the pump 3
int foodPin = 9; // pin for feeder
int ledPin = 13; //LED blink pin 

long odortime = 30 ; // pump ON, in seconds
int feedTime = 2; //how long the feeding will happen, in seconds

long currentMillis = 0;    // stores the value of millis() in each iteration of loop()
long previousMotorPinAMillis = 0; // will store last time the motor was updated
long previousMotorPinBMillis = 4800000; // 80'
long previousMotorPinCMillis = 2400000; // 40'
unsigned long previousFoodPinMillis = 0;
long previousDaylightMillis = -36000000; // neg. millis already elapsed since 7:30 AM at the time of starting the protocol
long previousOvernightMillis = 0;
unsigned int foodindex = 0; // keeps track of which food delivery
const long MotorPinAInterval = 9570; // (40' * 4 trial (repeats every 4 trials) * 60 sec/min) - 30 s (odortime) [s]
const long MotorPinBInterval = 9570; // (40' * 4 trial (repeats every 4 trials) * 60 sec/min) - 30 s (odortime) [s]
const long MotorPinCInterval = 4770; // (40' * 2 trial (repeats every 2 trials) * 60 sec/min) - 30 s (odortime) [s]
const long FoodPinInterval[] = {5025, 7192, 3621, 15880, 2778, 1500, 7234, 3285, 3603, 4373, 5828, 15544, 407, 2394, 3098, 2856, 883, 11697, 943, 687, 8941, 4615, 7692, 4398, 3778, 3069, 2260, 4183, 2724, 3393, 3210, 854, 3861, 3225, 5264, 4633, 707, 3180, 3469, 2383, 10409, 1878, 676, 3112, 2275, 7545, 26109, 5198, 5803, 5171, 334, 1949, 2039, 7468, 3333, 1071, 2589, 2540, 3240, 1089, 11890, 1152, 1793, 7262, 10240, 9810, 4914, 5880, 19288, 866, 2828, 9402, 1219, 970, 1722, 14833, 1023, 10920, 1355, 8058, 2659, 7465, 2221, 2295, 12965, 4562, 9453, 4515, 3037, 4030, 3058, 1436, 3863, 662, 17813, 3996, 11762, 1643, 2634, 785, 1343, 7412, 7501, 2719, 2446, 2650, 14793, 2448, 7455, 8397, 421, 496, 2678, 430, 17333, 1250, 6355, 4563, 5572, 304, 16150, 13636, 5999, 3680, 6692, 13532, 1659, 1599, 5007, 1266, 660, 549, 22106, 1218, 7007, 2613, 5623, 4329, 6909, 3447, 21502, 11120, 1780, 3580, 3254, 2635, 1208, 2683, 812, 7675, 9208, 1061, 3576, 1305, 324, 11637, 2270, 818, 650, 4916, 501, 13581, 716, 2746, 608, 3682, 2447, 2537, 5052, 9678, 8277, 4000, 15154, 866, 20794, 8978, 2824, 3217, 4905, 2850, 337, 2537, 1683, 11746, 416, 4669, 317, 7924, 2895, 5454, 5907, 1279, 622, 1993, 490, 539, 2342, 3136, 5710, 24521}; // inter-food intervals in sec
long DaylightInterval = 50400; // = 14h, how long is a day cycle in sec
long OvernightInterval = 36000; // = 10h, how long is a night cycle in sec


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
