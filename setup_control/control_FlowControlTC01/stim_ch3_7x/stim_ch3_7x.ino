/*
 stimulate 7x with ch1 (US)

 habituation: 1.5 h
 ISI: 60 min
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


// ch1: US
// ch2: CS+
// ch3: CS-


const boolean ch1[] = {true, true, true, true, true, true, true}; //US


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
  Serial.println("starting 1.5 h pause (habituation)"); 
  delay(5400000); //1.5 h
  Serial.println("starting sequence");
}

// the loop function runs over and over again forever
void loop() {

  if (iter < sizeof(ch1)) {

    Serial.println(iter + 1);
    delay(2000);

    digitalWrite(pinRX1, LOW);
    digitalWrite(pinRX2, LOW);
    digitalWrite(pinRX3, LOW);

    digitalWrite(pinLX3, HIGH);
    if (ch1[iter]) {
      Serial.println("ok ch3");
      digitalWrite(pinPUMP23, HIGH);
      delay(1900);
      digitalWrite(pinPUMP23, LOW);
    }
    digitalWrite(pinLX3, LOW);

    delay(3596100); // top off at 60 min
    iter++;

  } else if (iter == sizeof(ch1)) {
    Serial.println(" ");
    Serial.println("sequence terminated");
    iter++;
  }
}
