int soundPin = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(soundPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(soundPin, HIGH);


  delay(600);
  digitalWrite(soundPin, LOW);
  delay(600);
  digitalWrite(soundPin, HIGH);
  delay(600);
  digitalWrite(soundPin, LOW);

}
