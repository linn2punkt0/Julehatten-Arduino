// define all Pins
// int colorPin = ;
int temperaturePin= 6;
// int firePin= ;
// int soundPin= ;
// int lightPin= ;
int temperatureVal= 4;


void setup() {
// put your setup code here, to run once:

// OUTPUTS
// pinMode(soundPin, OUTPUT);
// pinMode(lightPin, OUTPUT);

// INPUTS
// pinMode(colorPin, INPUT);
pinMode(temperaturePin, INPUT);
// pinMode(firePin, INPUT);
}

void loop() {
// put your main code here, to run repeatedly:

// Read all input values
// colorVal = digitalRead(colorPin);
temperatureVal = analogRead(temperaturePin);
delay(400);
// fireVal = digitalRead(firePin);

// check if temperature is below 0 degrees
if(temperatureVal <= 0,5){
  Serial.print(temperatureVal);
// turn on and off lights
// digitalWrite(lightPin, HIGH);
// delay(400);
// digitalWrite(lightPin, LOW);
// delay(400);

// turn on the jingle bells!
// digitalWrite(soundPin, HIGH);
}
else{
Serial.print("too warm");
// turn off sound and lights
// digitalWrite(lightPin, LOW);
// digitalWrite(soundPin, LOW);
}
}
