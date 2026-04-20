// Merged ESP32 Smart Plant Monitor with ThingSpeak + OLED + DHT + 4 Soil Sensors
#include <WiFi.h>
#include <ThingSpeak.h>
#include <Wire.h>
#include <HTTPClient.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// WiFi credentials
const char* ssid = "Nothing";
const char* password = "12345678";

// ThingSpeak details
unsigned long myChannelNumber = 2648467;
const char * myWriteAPIKey = "0YEBHYJDAOV51VK7";
WiFiClient client;

#define THINGSPEAK_API_KEY  "0YEBHYJDAOV51VK7"
#define THINGSPEAK_CHANNEL_ID  2648467
unsigned long lastTS = 0;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int SOIL1_PIN = 32;
const int SOIL2_PIN = 33;
const int SOIL3_PIN = 34;
const int SOIL4_PIN = 35;
const float ADC_MAX = 4095.0f;

float rawToPercent(int raw) {
  float pct = (1.0f - (raw / ADC_MAX)) * 100.0f;
  return constrain(pct, 0.0f, 100.0f);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  Serial.println("\nWiFi Connected");
  ThingSpeak.begin(client);

  Wire.begin(21, 22);
  dht.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) { Serial.println("OLED not found!"); while (1); }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();
}

void loop() {
  int s1 = rawToPercent(analogRead(SOIL1_PIN));
  int s2 = rawToPercent(analogRead(SOIL2_PIN));
  int s3 = rawToPercent(analogRead(SOIL3_PIN));
  int s4 = rawToPercent(analogRead(SOIL4_PIN));
  int avgSoil = (s1 + s2 + s3 + s4) / 4;
  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();

  Serial.printf("S1:%d%%  S2:%d%%  S3:%d%%  S4:%d%%  Avg:%d%%  Temp:%.1fC  Humi:%.1f%%\n", s1, s2, s3, s4, avgSoil, temp, hum);

  display.clearDisplay();
  display.setCursor(0, 0);   display.printf("S1:%d%%  S2:%d%%  S3:%d%%", s1, s2, s3);
  display.setCursor(0, 16);  display.printf("S4:%d%%  Temp:%.0fC", s4, temp);
  display.setCursor(0, 32);  display.printf("Avg Soil:%d%% H:%d%%", avgSoil, (int)hum);
  display.display();

  if (millis() - lastTS > 5000) {
    lastTS = millis();
    sendToThingSpeak(temp, hum, s1, s2, s3, s4, avgSoil);
    Serial.println("Data sent to ThingSpeak");
  }

  ThingSpeak.setField(1, temp);
  ThingSpeak.setField(2, hum);
  ThingSpeak.setField(3, s1);
  ThingSpeak.setField(4, s2);
  ThingSpeak.setField(5, s3);
  ThingSpeak.setField(6, s4);
  ThingSpeak.setField(7, avgSoil);
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  Serial.println(x == 200 ? "Data pushed to ThingSpeak" : String("ThingSpeak Error: ") + x);

  delay(15000);
}

void sendToThingSpeak(float temp, float hum, int s1, int s2, int s3, int s4, float avg) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "http://api.thingspeak.com/update?api_key=" + String(THINGSPEAK_API_KEY) +
                 "&field1=" + String(temp) +
                 "&field2=" + String(hum) +
                 "&field3=" + String(s1) +
                 "&field4=" + String(s2) +
                 "&field5=" + String(s3) +
                 "&field6=" + String(s4) +
                 "&field7=" + String(avg);
    http.begin(url);
    http.GET();
    http.end();
  }
}