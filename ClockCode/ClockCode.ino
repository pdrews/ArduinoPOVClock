#define CYCLE 60
int all_pins[16] = {A3,A2,A1,A0,13,12,11,10,9,8,7,6,5,4,3,A6};
volatile unsigned long previousTime = 0;
volatile unsigned long revolutionTime = 0;
unsigned long second = 0;
unsigned long last_second_time = 0;

void setup() {
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), hallInterrupt, RISING);
  
  for (int i=0; i<16; i++){
    pinMode(all_pins[i],OUTPUT);
  }
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
}

void loop() {
  if (last_second_time+1000 < millis()) {
    second++;
    if (second > CYCLE-1) {
      second = 0;
    }
    last_second_time += 1000;
  }
//  int current_second = (millis()/1000)%32;
  for (int i = 0; i < CYCLE; i++) {
    int slice_number = CYCLE-1-i;
    if (second == slice_number) {
      for (int ii=0; ii<16; ii++){
        digitalWrite(all_pins[ii],HIGH);
      }
    }
    else {
      for (int ii=0; ii<16; ii++){
        digitalWrite(all_pins[ii],LOW);
      }
    }
    unsigned long endOfSlice = previousTime + (revolutionTime*(i+1));
    while (endOfSlice > micros()) {};
  }
  while (digitalRead(2) == 0) {}
}

void hallInterrupt() {
  unsigned long t = micros();
  revolutionTime = t - previousTime;
  previousTime = t;
  revolutionTime = revolutionTime / CYCLE;
}
