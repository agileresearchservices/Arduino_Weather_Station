#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "DHT.h"

// DHT Settings
#define DHTPIN 10     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

// LCD Settings
Adafruit_PCD8544 display = Adafruit_PCD8544(15, 16, 5, 4, 6);

void setup()   {
  Serial.begin(9600);
  display.begin();
  display.setContrast(40);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  // Begin DHT acquisition
  dht.begin();
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
  display.println(f);
  display.print("H:");
  display.println(h);
  display.display();
}
