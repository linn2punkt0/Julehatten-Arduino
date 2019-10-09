// define all Pins
int temperaturePin = A11;
int soundPin = 10;
int temperatureVal = 4;
int temperatureC = 25;

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define lightPin 9
#define numPixel 12
Adafruit_NeoPixel pixels(numPixel, lightPin, NEO_GRB + NEO_KHZ800);


void setup() {
  // put your setup code here, to run once:

  // OUTPUTS
  pinMode(soundPin, OUTPUT);

  byte neoBright = 100;
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.show();   // Send the updated pixel colors to the hardware.
  // pixels.setBrightness(neoBright);

  // INPUTS
  pinMode(temperaturePin, INPUT);
  Serial.begin(9600);
}

float take_averaged_reading(int temp)
{
  float sum = 0.0 ;
  int counts = 20;
  for (byte i = 0 ; i < counts ; i++)
    sum += temp ; // whatever code reads the sensor
  return sum / counts ;
}

float measure_temperature()
{
  //getting the voltage reading from the temperature sensor
  int reading = analogRead(temperaturePin);

  // converting that reading to voltage, for 3.3v arduino use 3.3
  float voltage = reading * 3.3;
  voltage /= 1024.0;

  //converting from 10 mv per degree wit 500 mV offset
  //to degrees ((voltage - 500mV) times 100)
  float temperatureC = (voltage - 0.5) * 100 ;

  int average;
  average = take_averaged_reading(temperatureC);
  Serial.println(average);
  return average;
  delay(1000);

}

/*
  char setRandomColor()
  {
  char red = "204, 0, 0";
  char green = "0, 150, 0";
  char white = "255, 255, 153";
  char color [3] = {"red", "green", "white"};
  int itemNumber = rand() % 3;
  if (itemNumber == "red"){
  return "204, 0, 0"
  }
  if (itemNumber == "green"){
  return "0, 150, 0"
  }
  if (itemNumber == "white"){
  return "255, 255, 153"
  }
  // return color[itemNumber];
  }
*/

void loop() {
  int temperature;
  temperature = measure_temperature();

  // check if temperature is below the specified degrees
  if (temperature <= 20) {
    Serial.println("Its christmas! ");

    // turn on the jingle bells!
    digitalWrite(soundPin, HIGH);

    //turn on and off lights
    for (int i = 0; i < numPixel; i++) { // For each pixel...
      // Set green color:
      pixels.setPixelColor(i, pixels.Color(0, 150, 0));
      pixels.show();
      delay(25);
    }
   /* for (int i = 0; i < numPixel; i++) { // For each pixel...
      // Setting white color:
      pixels.setPixelColor(i, pixels.Color(255, 255, 255));
      pixels.show();
      delay(30);
    }
    */
    for (int i = 0; i < numPixel; i++) { // For each pixel...
      // Setting red color:
      pixels.setPixelColor(i, pixels.Color(204, 0, 0));
      pixels.show();
      delay(25);
    }

    /*
      // TEST
      for (int i = 0; i < numPixel; i++) { // For each pixel...
       char color = setRandomColor();
       pixels.setPixelColor(i, pixels.Color(color));
      pixels.show();
      delay(20);
      }

    */
  }
  else {
    Serial.println("too warm");
    // turn off sound and lights
    pixels.clear();
    for (int i = 0; i < numPixel; i++) { // For each pixel...
      // Setting red color:
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels.show();
    }
    digitalWrite(soundPin, LOW);
    delay(300);
  }
}
