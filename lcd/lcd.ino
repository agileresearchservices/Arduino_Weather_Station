#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "DHT.h"
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <Arduino.h>
#include <Wire.h>         // this #include still required because the RTClib depends on it
#include "RTClib.h"

// RTC Settings
RTC_Millis rtc;

// BMP180 Settings
Adafruit_BMP085 bmp;

// DHT Settings
#define DHTPIN 10     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

// LCD Settings
Adafruit_PCD8544 display = Adafruit_PCD8544(15, 16, 5, 4, 6);

void setup()   {
  Serial.begin(9600);
  // Begin LCD Display
  display.begin();
  display.setContrast(40);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  // Begin DHT acquisition
  dht.begin();
  // Begin BMP180
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) {}
  }
  //Begin Clock
      rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
    // Wait a few seconds between measurements.
  delay(2000);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  display.clearDisplay();
  display.print("T:");
  display.println(dht.convertCtoF(bmp.readTemperature()));
  display.print("H:");
  display.println(h);

  // BMP180 Read and report
  //Serial.print("Temperature = ");
  //Serial.print(dht.convertCtoF(bmp.readTemperature()));
  //Serial.println(" *F");
  
  display.print("P: ");
  display.print(bmp.readPressure());
  display.println(" Pa");
  
  // Calculate altitude assuming 'standard' barometric
  // pressure of 1013.25 millibar = 101325 Pascal
  display.print("Alt: ");
  display.println(bmp.readAltitude());
  
  //display.print("Sea: ");
  //display.print(bmp.readSealevelPressure());
  //display.println(" Pa");
  
  // you can get a more precise measurement of altitude
  // if you know the current sea level pressure which will
  // vary with weather and such. If it is 1015 millibars
  // that is equal to 101500 Pascals.
  //display.print("RealAlt: ");
  //display.print(bmp.readAltitude(101862));
  //display.println(" meters");

  // Read and display Date and Time
  DateTime now = rtc.now();
  
  display.print(now.year(), DEC);
  display.print('/');
  display.print(now.month(), DEC);
  display.print('/');
  display.print(now.day(), DEC);
  display.println(' ');
  display.print(now.hour(), DEC);
  display.print(':');
  display.print(now.minute(), DEC);
  //display.print(':');
  //display.print(now.second(), DEC);
  //display.println();
  display.display();
  //Serial.println();
  delay(500);
  
}
