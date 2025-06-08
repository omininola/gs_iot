#include <WiFi.h>
#include <ThingSpeak.h>
#include <DHT.h>

#define AIR_PIN 35
#define LIGHT_PIN 34

#define DHT_PIN 17
#define DHT_TYPE DHT22

DHT dht(DHT_PIN, DHT_TYPE);

const char* SSID = "Wokwi-GUEST";
const char* PSWD = "";

WiFiClient client;
unsigned long channelID = 2981469;
const char* writeAPIKey = "54BV82DI9T8HHRPE";

float temperature;
float humidity;
float airQuality;
int fireLevel;

void connectWifi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to Wi-Fi: ");
    Serial.print("(");
    Serial.print(SSID);
    Serial.print(")");

    WiFi.begin(SSID, PSWD);

    int tries = 0;
    while (WiFi.status() != WL_CONNECTED && tries < 20) {
      delay(500);
      Serial.print(".");
      tries++;
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.print("\nConnected to ");
      Serial.println(SSID);

      Serial.print("IP: ");
      Serial.println(WiFi.localIP());
    } else {
      Serial.println("\nError while trying to connect");
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(LIGHT_PIN, INPUT);
  
  WiFi.mode(WIFI_STA);
  connectWifi();

  ThingSpeak.begin(client);
  dht.begin();

  Serial.println("Initializing client...");
  delay(2000);
  Serial.println("Client connected");
}

void loop() {
  connectWifi();

  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  airQuality = analogRead(AIR_PIN);
  fireLevel = !digitalRead(LIGHT_PIN);

  Serial.println("----- Simulated Data -----");
  Serial.printf("Temperature: %.2f°C\n", temperature);
  Serial.printf("Humidity: %.2f%%\n", humidity);
  Serial.printf("Air Quality (ppm): %.2f\n", airQuality);
  Serial.printf("Fire Level: ");
  Serial.println(fireLevel ? "Detected" : "Not Detected");
  Serial.println("--------------------------");

  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);
  ThingSpeak.setField(3, airQuality);
  ThingSpeak.setField(4, fireLevel);

  int status = ThingSpeak.writeFields(channelID, writeAPIKey);

  if (status == 200) {
    Serial.println("Data successfully sent to channel on ThingSpeak!");
  } else {
    Serial.print("Error sending data: ");
    Serial.println(status);
  }

  delay(20000);
}