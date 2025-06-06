#include <WiFi.h>
#include <ThingSpeak.h>
#include <DHT.h>

#define DHTPIN 15
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

const char* SSID = "Wokwi-GUEST";
const char* PSWD = "";

WiFiClient client;
unsigned long channelID = 2981469;
const char* writeAPIKey = "54BV82DI9T8HHRPE";

float temperature;
float humidity;
float airQuality;
float fireLevel;

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
      Serial.print(SSID);

      Serial.print("\nIP: ");
      Serial.print(WiFi.localIP());
    } else {
      Serial.print("\nError while trying to connect");
    }
  }
}

void setup() {
  Serial.begin(115200);

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
  airQuality = analogRead(32);
  fireLevel = digitalRead(33);

  Serial.println("----- Simulated Data -----");
  Serial.printf("Temperature: %.2f°C\n", temperature);
  Serial.printf("Humidity: %.2f%%\n", humidity);
  Serial.printf("Air Quality (ppm): %.2f\n", airQuality);
  Serial.printf("Fire Level: %.2f\n", fireLevel);
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
