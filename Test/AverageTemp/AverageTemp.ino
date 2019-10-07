// define all Pins
int temperaturePin= A5;
int temperatureC= 25;
int lightPin= ;

void setup() {
// put your setup code here, to run once:

// OUTPUTS
pinMode(lightPin, OUTPUT);

// INPUTS
// Set the temperature sensor pin as an INPUT:
pinMode(temperaturePin, INPUT);

Serial.begin(9600);

}

float take_averaged_reading(int temp)
{
  float sum = 0.0 ;
  int counts = 8;
  for (byte i = 0 ; i < counts ; i++)
    sum += temp ; // whatever code reads the sensor
  return sum / counts ;
}

void loop() {
  //getting the voltage reading from the temperature sensor
 int reading = analogRead(temperaturePin);  
 
 // converting that reading to voltage, for 3.3v arduino use 3.3
 float voltage = reading * 5.0;
 voltage /= 1024.0; 
 
 // Print temperature
 float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 //Serial.print(temperatureC); Serial.println(" celcius");

 int average;

 average = take_averaged_reading(temperatureC);
 Serial.println(average);
 
 delay(1000);               
  
  // check if temperature is below the specified degrees
  if(average <= 20){
    Serial.println("Its christmas! ");
     //turn on and off lights
     digitalWrite(lightPin, HIGH);
     delay(400);
     digitalWrite(lightPin, LOW);
     delay(400);
  }
  else{
  Serial.println("Too warm... ");
  // turn off sound and lights
   digitalWrite(lightPin, LOW);
   digitalWrite(soundPin, LOW);
}

}
