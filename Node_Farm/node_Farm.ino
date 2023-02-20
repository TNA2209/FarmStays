#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

#define MQTT_VERSION MQTT_VERSION_3_1_1
#define DHTPIN D1  
#define DHTTYPE DHT11 
// Wifi: SSID and password
const PROGMEM char* WIFI_SSID = "CaFe Minh Tam";
const PROGMEM char* WIFI_PASSWORD = "88888888";

// MQTT: ID, server IP, port, username and password
const PROGMEM char* MQTT_CLIENT_ID = "sensor_farm";
const PROGMEM char* MQTT_SERVER_IP = "192.168.1.40";
const PROGMEM uint16_t MQTT_SERVER_PORT = 1883;
const PROGMEM char* MQTT_USER = "farmstay";
const PROGMEM char* MQTT_PASSWORD = "farmstay";

// MQTT: topic
const PROGMEM char* MQTT_SENSOR_TOPIC = "sensor/moisture";
const PROGMEM char* MQTT_SENSOR_TOPIC2= "sensor/humi";
const PROGMEM char* MQTT_SENSOR_TOPIC3= "sensor/temp";

const int sensor_pin = A0;
unsigned long lastSensorTime = 0;
const unsigned long sensorInterval = 5000; // Send sensor data every 5 seconds
WiFiClient wifiClient;
PubSubClient client(wifiClient);
DHT dht(DHTPIN, DHTTYPE);

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("INFO: Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("INFO: connected");
      
    } else {
      Serial.print("ERROR: failed, rc=");
      Serial.print(client.state());
      Serial.println("DEBUG: try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  // init the serial
  Serial.begin(115200);

  // init the WiFi connection
  Serial.println();
  Serial.println();
  Serial.print("INFO: Connecting to ");
  WiFi.mode(WIFI_STA);
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("INFO: WiFi connected");
  Serial.println("INFO: IP address: ");
  Serial.println(WiFi.localIP());

  // init the MQTT connection
  client.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
}

void loop()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();
    unsigned long currentTime = millis();

    // Check if it's time to send sensor data
    if (currentTime - lastSensorTime >= sensorInterval)
    {
//        float temperature = dht.readTemperature();
//        float humidity = dht.readHumidity();
        float temperature = 30;
        float humidity = 50;
        String temp_payload = String(temperature);
        String hum_payload = String(humidity);
        if (isnan(humidity) || isnan(temperature))
        {
            Serial.println("ERROR: Failed to read from DHT sensor!");
            return;
        }
        else
        {
            client.publish(MQTT_SENSOR_TOPIC2, hum_payload.c_str(), true);
            client.publish(MQTT_SENSOR_TOPIC3, temp_payload.c_str(), true);
        }
        int mois = analogRead(sensor_pin);
        float moisture_percentage = (100.00 - ((mois / 1024.00) * 100.00));
        String moisture_payload = String(moisture_percentage);
        client.publish(MQTT_SENSOR_TOPIC, moisture_payload.c_str(), true);
        lastSensorTime = currentTime; // Update the last sensor time
    }
}
