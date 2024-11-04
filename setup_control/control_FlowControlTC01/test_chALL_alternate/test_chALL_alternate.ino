/*
  test setup for ALL CHANNELS in series
*/


// output>pin, pump1>7, pump2,pump3>6, valve4>5

static int pinVALVE = 5; // #4
static int pinPUMP1 = 7;
static int pinLX1 = 9; // outward
static int pinRX1 = 8; // inward
static int pinPUMP23 = 6;
static int pinLX2 = 11; // outward
static int pinRX2 = 10; // inward
static int pinLX3 = 12; // outward
static int pinRX3 = 13; // inward

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(pinVALVE, OUTPUT);
  pinMode(pinPUMP1, OUTPUT);
  pinMode(pinLX1, OUTPUT);
  pinMode(pinRX1, OUTPUT);
  pinMode(pinPUMP23, OUTPUT);
  pinMode(pinLX2, OUTPUT);
  pinMode(pinRX2, OUTPUT);
  pinMode(pinLX3, OUTPUT);
  pinMode(pinRX3, OUTPUT);

  delay(500);

  digitalWrite(pinVALVE, LOW);
}

// the loop function runs over and over again forever
void loop() {
  
  digitalWrite(pinLX1, HIGH);
  digitalWrite(pinRX1, LOW);
  
  digitalWrite(pinPUMP1, HIGH);
  delay(1000);
  digitalWrite(pinPUMP1, LOW);
  delay(1000);

  digitalWrite(pinLX1, LOW);
  digitalWrite(pinRX1, LOW);
  
  digitalWrite(pinLX2, HIGH);
  digitalWrite(pinRX2, LOW);
  
  digitalWrite(pinPUMP23, HIGH);
  delay(1000);
  digitalWrite(pinPUMP23, LOW);
  delay(1000);

  digitalWrite(pinLX2, LOW);
  digitalWrite(pinRX2, LOW);
  
  digitalWrite(pinLX3, HIGH);
  digitalWrite(pinRX3, LOW);
  
  digitalWrite(pinPUMP23, HIGH);
  delay(1000);
  digitalWrite(pinPUMP23, LOW);
  delay(1000);

  digitalWrite(pinLX3, LOW);
  digitalWrite(pinRX3, LOW);

  digitalWrite(pinVALVE, HIGH);
  delay(1000);
  digitalWrite(pinVALVE, LOW);
  delay(1000);
}
