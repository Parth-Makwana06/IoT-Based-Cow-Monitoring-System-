#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include "DHT.h"
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <HTTPClient.h>

// ====== WiFi & ThingSpeak ======
const char* ssid = "M64";     // Make sure exact case
const char* password = "";
String apiKey = "5ZH81U2R4Z2852TC";      // ThingSpeak Write API Key
const char* server = "http://api.thingspeak.com/update";

// ====== DHT11 Setup ======
#define DHTPIN 4       // DHT11 connected to GPIO4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ====== GPS Setup ======
TinyGPSPlus gps;
HardwareSerial SerialGPS(1);  // UART1 for GPS (RX=16, TX=17)

// ====== MPU6050 Setup ======
MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting ESP32 IoT Device...");

  // ===== WiFi Connect =====
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 20) {  // ~10 seconds max
    delay(500);
    Serial.print(".");
    retry++;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFailed to connect to WiFi!");
  }

  // ===== DHT11 Init =====
  dht.begin();

  // ===== GPS Init =====
  SerialGPS.begin(9600, SERIAL_8N1, 16, 17);

  // ===== MPU6050 Init =====
  Wire.begin(); 
  delay(200);  // Give MPU6050 time to power up
  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("MPU6050 Connected at default address 0x68!");
  } else {
    Serial.println("MPU6050 Connection Failed at 0x68, trying 0x69...");
    mpu.initialize();  // re-init if your library supports 0x69 change
    if (mpu.testConnection()) Serial.println("MPU6050 Connected at 0x69!");
    else Serial.println("MPU6050 still not connected. Check wiring & AD0!");
  }
}


// === loop ===
void loop() {
  // ===== DHT11 Data =====
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  if (isnan(temp) || isnan(hum)) {
    Serial.println("❌ Failed to read from DHT11!");
    temp = 0.0; hum = 0.0;
  }

  // ===== GPS Data =====
  float latitude = 0.0, longitude = 0.0;
  while (SerialGPS.available() > 0) {
    if (gps.encode(SerialGPS.read())) {
      if (gps.location.isValid()) {
        latitude = gps.location.lat();
        longitude = gps.location.lng();
      }
    }
  }

  // ===== MPU6050 Data =====
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // ===== Print to Serial Monitor =====
  Serial.println("======================================");
  Serial.println("📡 Sensor Readings:");
  Serial.print("🌡️ Temp: "); Serial.print(temp); Serial.println(" °C");
  Serial.print("💧 Humidity: "); Serial.print(hum); Serial.println(" %");
  if (gps.location.isValid()) {
    Serial.print("📍 GPS: Lat: "); Serial.print(latitude, 6);
    Serial.print(", Lng: "); Serial.println(longitude, 6);
  } else {
    Serial.println("📍 GPS: No Fix Yet");
  }
  Serial.print("🤖 Accel(g): X: "); Serial.print(ax);
  Serial.print(", Y: "); Serial.print(ay);
  Serial.print(", Z: "); Serial.println(az);
  Serial.print("🌀 Gyro(deg/s): X: "); Serial.print(gx);
  Serial.print(", Y: "); Serial.print(gy);
  Serial.print(", Z: "); Serial.println(gz);
  Serial.println("======================================");

  // ===== Send Data to ThingSpeak =====
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(server) + "?api_key=" + apiKey +
                 "&field1=" + String(temp) +
                 "&field2=" + String(hum) +
                 "&field3=" + String(latitude, 6) +
                 "&field4=" + String(longitude, 6) +
                 "&field5=" + String(ax) +
                 "&field6=" + String(ay) +
                 "&field7=" + String(az);

    http.begin(url);
    int httpCode = http.GET();
    if (httpCode > 0) Serial.println("✅ Data sent to ThingSpeak successfully!");
    else Serial.println("⚠️ Error sending data to ThingSpeak.");
    http.end();
  } else {
    Serial.println("⚠️ WiFi not connected. Skipping ThingSpeak upload.");
  }

  Serial.println("\n⏳ Waiting 10 seconds for next reading...\n");
  delay(10000); // 10 seconds, ThingSpeak allows every 15 sec
}
