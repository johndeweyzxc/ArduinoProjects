int dTime = 1000;

int led = 5;
int curLed = led;
int seq = 0;

int lastLed = 11;
int midInc = 0;

int curTime = 0;

void setup() {
  // put your setup code here, to run once:
  for (int i = 5; i < 12; i++) {
    pinMode(i, OUTPUT);
  }
}

void sequence() {
  digitalWrite(curLed, HIGH);
  curLed++;
  delay(dTime);
  digitalWrite(curLed - 1, LOW);
  if (curLed == 12) {
    curLed = led;
    seq = 0;
  }
}

void middle() {
  digitalWrite(curLed, HIGH);
  digitalWrite(lastLed - midInc, HIGH);
  delay(dTime);
  digitalWrite(curLed, LOW);
  digitalWrite(lastLed - midInc, LOW);
  curLed++;
  midInc++;
  if (curLed == 8) {
    delay(dTime);
    digitalWrite(7, LOW);
    digitalWrite(9, LOW);
    digitalWrite(curLed, HIGH);
    delay(dTime);
    digitalWrite(curLed, LOW);
    curLed = led;
    midInc = 0;
    seq = 1;
  }
  delay(dTime);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (seq == 1) {
    sequence();
  } else {
    middle();
  }
}
