/*
  Based on the ReadAnalogVoltage public domain example code.

*/

static float bias = 2.5; // [V] , voltage bias of the Valvelink 8.3 AO
static double threshold = 0.15; // [V] , detection threshold for valve-switch events

const byte analogIn = A0; // input channel for the Valvelink 8.3 AO
const int LEDout = 2; // output to LED ("D2" on Nano)
const int inbuiltLEDout = 13; // output
.0to inbuilt LED ("D13" on Nano)

void setup() {
  pinMode(analogIn, INPUT);
  pinMode(LEDout, OUTPUT);
  pinMode(inbuiltLEDout, OUTPUT);
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  Serial.println(voltage);
  if(voltage-bias>threshold){
    digitalWrite(LEDout, HIGH);
    digitalWrite(inbuiltLEDout, HIGH);
  } else {
    digitalWrite(LEDout, LOW);  
    digitalWrite(inbuiltLEDout, LOW);  
  }
}
