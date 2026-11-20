// IoT-Based Weather Monitoring System
// Microcontroller: NodeMCU (ESP8266)
// Sensors: DHT11, BMP180, Raindrop Sensor, LDR Module
// Display & Cloud: 16x2 I2C LCD + Blynk IoT

#define BLYNK_TEMPLATE_ID   "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Weather Monitoring System"
#define BLYNK_AUTH_TOKEN    "YOUR_BLYNK_AUTH_TOKEN"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>

// Wi-Fi Credentials
char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";

// Pin Definitions
#define DHTPIN      D4        // DHT11 Data Pin connected to GPIO2 (D4)
#define DHTTYPE     DHT11
#define RAIN_PIN    D5        // Raindrop Sensor Digital Out (D0)
#define LDR_PIN     A0        // LDR Analog Out (A0)

// Object Initializations
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C Address 0x27, 16 Columns, 2 Rows
BlynkTimer timer;

void sendSensorData() {
  // 1. Read Temperature & Humidity from DHT11
  float humidity = dht.readHumidity();
  float tempDHT = dht.readTemperature();

  // 2. Read Barometric Pressure (in hPa/mbar) from BMP180
  float pressure = bmp.readPressure() / 100.0F;

  // 3. Read Rainfall Status (LOW = Rain Detected, HIGH = Clear)
  int rainState = digitalRead(RAIN_PIN);
  String rainStatus = (rainState == LOW) ? "Rain" : "Clear";

  // 4. Read Ambient Light Intensity from LDR (0 - 1023)
  int ldrRaw = analogRead(LDR_PIN);
  int lightPercent = map(ldrRaw, 1023, 0, 0, 100);

  if (isnan(humidity) || isnan(tempDHT)) {
    Serial.println("Failed to read from DHT11 sensor!");
    return;
  }

  // Send Live Telemetry to Blynk IoT Virtual Pins
  Blynk.virtualWrite(V0, tempDHT);
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, pressure);
  Blynk.virtualWrite(V3, rainStatus);
  Blynk.virtualWrite(V4, lightPercent);

  // Display Live Readings on 16x2 I2C LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(tempDHT, 1);
  lcd.print("C H:");
  lcd.print((int)humidity);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("P:");
  lcd.print((int)pressure);
  lcd.print("hPa ");
  lcd.print(rainStatus);
}

void setup() {
  Serial.begin(115200);
  pinMode(RAIN_PIN, INPUT);

  // Initialize I2C Bus (SDA = D2, SCL = D1)
  Wire.begin(D2, D1);
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Weather Station");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");

  dht.begin();
  if (!bmp.begin()) {
    Serial.println("BMP180 sensor not detected!");
  }

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(2000L, sendSensorData); // Update every 2 seconds
  delay(1500);
  lcd.clear();
}

void loop() {
  Blynk.run();
  timer.run();
}
