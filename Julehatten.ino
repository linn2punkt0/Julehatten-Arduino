// define all Pins
// int colorPin = ;
int temperaturePin = 10;
// int firePin= ;
int soundPin = 9;
// int lightPin = 12;
int temperatureVal = 4;
int temperatureC = 25;

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN 12
#define NUMPIXELS 1
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  // put your setup code here, to run once:

  // OUTPUTS
  pinMode(soundPin, OUTPUT);
  // pinMode(lightPin, OUTPUT);

  byte neoBright = 100;
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.show();   // Send the updated pixel colors to the hardware.
  pixels.setBrightness(neoBright);

  // INPUTS
  // pinMode(colorPin, INPUT);
  pinMode(temperaturePin, INPUT);
  // pinMode(firePin, INPUT);

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

void loop() {
  // put your main code here, to run repeatedly:
  int temperature;
  temperature = measure_temperature();

  // check if temperature is below the specified degrees
  if (temperature <= 20) {
    Serial.println("Its christmas! ");

    // turn on the jingle bells!
    digitalWrite(soundPin, HIGH);

    //turn on and off lights
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...
      // Set green color:
      pixels.setPixelColor(i, pixels.Color(0, 150, 0));
      pixels.show();
      delay(300);
    }
    for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...
      // Setting white color:
      pixels.setPixelColor(i, pixels.Color(255, 255, 153));
      pixels.show();
      delay(300);
    }
    for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...
      // Setting red color:
      pixels.setPixelColor(i, pixels.Color(204, 0, 0));
      pixels.show();
      delay(300);
    }
  }
  else {
    Serial.println("too warm");
    // turn off sound and lights
    pixels.clear();
      for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...
      // Setting red color:
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels.show();
    }
    digitalWrite(soundPin, LOW);
    delay(900);
  }
}
