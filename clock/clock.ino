/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

volatile unsigned long previousTime = 0;
volatile unsigned long revolutionTime = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), hallInterrupt, RISING);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  /*
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  */

  digitalWrite(8, HIGH); //draws circle of the smiley face
}

// the loop function runs over and over again forever

// smiley face eyes and mouth
void loop() {
  for (int i = 0; i < 60; i++){
    if (i == 8 || i == 52){
      digitalWrite(7, HIGH);
      }
    else {
      digitalWrite(7,LOW);
      }
    if (i > 20 && i < 40) {
      digitalWrite(4, HIGH);
    }
    else {
      digitalWrite(4, LOW);
    }
  unsigned long endOfSlice = previousTime + (revolutionTime*(i+1));

    while (endOfSlice > micros()) {};
//    delayMicroseconds(revolutionTime);
  }

  while (digitalRead(2) == 0) {}
}

/*
void loop() {
  int led4 = 0;
  for (int i = 0; i < 16; i++) {
    led4 = 1 - led4;
    digitalWrite(4, led4);
    unsigned long endOfSlice = previousTime + (revolutionTime*(i+1));
    while (endOfSlice > micros()) {};
//    delayMicroseconds(revolutionTime);
  }

  while (digitalRead(2) == 0) {} //waits for the halleffect sensor is read as 1
}
*/

void hallInterrupt() {
  unsigned long t = micros();
  revolutionTime = t - previousTime;
  previousTime = t;
  revolutionTime = revolutionTime / 60; //changed to 60 increments within a revolution
}

