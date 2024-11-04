/*
  experiment run

  runs as many times as there are entries in boolean array ch1
  1 cycle / h --> total runtime 12 h

  assumes prep already run and setup ready.
*/


// output>pin, 1>7, 2,3>6, 4>5

static int pinVALVE = 5; // #4
static int pinPUMP1 = 7;
static int pinLX1 = 9; // outward
static int pinRX1 = 8; // inward
static int pinPUMP23 = 6;
static int pinLX2 = 11; // outward
static int pinRX2 = 10; // inward
static int pinLX3 = 12; // outward
static int pinRX3 = 13; // inward


int iter = 0;


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

  Serial.begin(9600);
  delay(500);

  digitalWrite(pinVALVE, LOW);

  Serial.println("starting program");
  Serial.println(" ");
  Serial.println("starting 15 min pause"); 
  delay(900000); //15 min
  Serial.println("starting stimulation: 1x channel #1");

  digitalWrite(pinLX1, HIGH);
  digitalWrite(pinPUMP1, HIGH);
  delay(1900);
  digitalWrite(pinPUMP1, LOW);
  digitalWrite(pinLX1, LOW);
}

// the loop function runs over and over again forever
void loop() {
  
}
