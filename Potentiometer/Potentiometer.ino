/*
3 PIN POTENTIOMETER

Pin A0 - Input
Pin 13 - Output
Pin 12 - Output
Pin 11 - Output

HOW TO BUILD:
1. Connect GND with resitor on negative of led lights
2. Connect pins 13, 12 and 11 to positive of led lights
3. Connect left pin of potentiometer to 5V pin
4. Connect middle pin of potentiometer to A0 pin
5. Connect right pin of potentiometer to GND
*/

int i = 0;
int prev_i = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  i = analogRead(A0);

  if (i < 400) {
    digitalWrite(13, 1);
    digitalWrite(12, 0);
    digitalWrite(11, 0);

  } else if (i < 900) {
    digitalWrite(13, 0);
    digitalWrite(12, 1);
    digitalWrite(11, 0);
  } else {
    digitalWrite(13, 0);
    digitalWrite(12, 0);
    digitalWrite(11, 1);
  }
}
