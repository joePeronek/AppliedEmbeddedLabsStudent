#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <Wire.h>

// User Settings
const int DHT_PIN = 2; // DHT11 data pin
const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;

// DHT11 Setup
#define DHTTYPE DHT11
DHT dht(DHT_PIN, DHTTYPE);

// OLED Setup
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);

  dht.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED initialization failed!");
    while (true)
      ;
  }

  display.clearDisplay();
  display.display();
}

void loop() {
  // Read the sensor
  float temperatureC = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Convert Celsius to Fahrenheit
  float temperatureF = temperatureC * 9.0 / 5.0 + 32.0;

  // Print to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperatureF, 1);
  Serial.print(" F\tHumidity: ");
  Serial.print(humidity, 1);
  Serial.println("%");

  // Update OLED
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);

  display.setCursor(0, 0);
  display.print("T: ");
  display.print(temperatureF, 1);
  display.write(247);
  display.print("F");

  display.setCursor(0, 32);
  display.print("H: ");
  display.print(humidity, 1);
  display.print("%");

  display.display();

  delay(1000);
}
