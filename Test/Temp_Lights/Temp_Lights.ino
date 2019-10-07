#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// define all Pins
int temperaturePin= A5;
int temperatureC= 25;
#define PIN 6 // Pin on the Arduino connected to the NeoPixels

// Number of NeoPixels attached to the Arduino
#define NUMPIXELS 2

void setup() {

byte neoBright = 100;
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.show();   // Send the updated pixel colors to the hardware.
  pixels.setBrightness(neoBright);

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
     // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));
    pixels.show();
    delay(200);
  }
  for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Setting red color:
    pixels.setPixelColor(i, pixels.Color(204, 0, 0));
    pixels.show();
    delay(200);
  }
  }
  else{
  Serial.println("Too warm... ");
  // turn off sound and lights
  pixels.clear();
}

}
