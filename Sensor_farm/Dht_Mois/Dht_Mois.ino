#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "DHT.h"

#define MQTT_VERSION MQTT_VERSION_3_1_1
#define DHTPIN D5  
#define DHTTYPE DHT11 
// Wifi: SSID and password
const PROGMEM char* WIFI_SSID = "CongMinh";
const PROGMEM char* WIFI_PASSWORD = "minh0919";

// MQTT: ID, server IP, port, username and password
const PROGMEM char* MQTT_CLIENT_ID = "sensor_farm";
const PROGMEM char* MQTT_SERVER_IP = "134.122.6.117";
const PROGMEM uint16_t MQTT_SERVER_PORT = 1883;
const PROGMEM char* MQTT_USER = "farmstay";
const PROGMEM char* MQTT_PASSWORD = "farmstay";

// MQTT: topic
const PROGMEM char* MQTT_SENSOR_TOPIC = "sensor/moisture";
const PROGMEM char* MQTT_SENSOR_TOPIC2 = "sensor/fire";
const PROGMEM char* MQTT_SENSOR_TOPIC3= "sensor/humitemp";

const int sensor_pin = A0;
const int sensor_pin2 = D1;

WiFiClient wifiClient;
PubSubClient client(wifiClient);
DHT dht(DHTPIN, DHTTYPE);

// function called to publish the temperature and the humidity
void publishData(int p_moisture) {
  
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["moisture"] = (String)p_moisture;
  root.prettyPrintTo(Serial);
  Serial.println("");
  /*
  {
    "moisture":  "0"
  }
  */
  char data[200];
  root.printTo(data, root.measureLength() + 1);
  client.publish(MQTT_SENSOR_TOPIC, data);
}
void publishData2(int p_fire) {
  
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["Fire"] = (String)p_fire;
  root.prettyPrintTo(Serial);
  Serial.println("");
  /*
  {
    "Fire":  "75"
  }
  */
  char data[200];
  root.printTo(data, root.measureLength() + 1);
  client.publish(MQTT_SENSOR_TOPIC2, data);
}
void publishData3(float p_temperature, float p_humidity) {

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  // INFO: the data must be converted into a string; a problem occurs when using floats...
  root["temperature"] = (String)p_temperature;
  root["humidity"] = (String)p_humidity;
  root.prettyPrintTo(Serial);
  Serial.println("");
  /*
     {
        "temperature": "0.0" ,
        "humidity": "0.0"
     }
  */
  char data[200];
  root.printTo(data, root.measureLength() + 1);
  client.publish(MQTT_SENSOR_TOPIC3, data, true);
  yield();
}
// function called when a MQTT message arrived
void callback(char* p_topic, byte* p_payload, unsigned int p_length) {
}

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
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  // read the value of the moisture
  float moisture_percentage;
  uint16_t mois = analogRead(sensor_pin);
  moisture_percentage = ( 100.00 - ( (mois/1024.00) * 100.00 ) ); 
  publishData(moisture_percentage);

  // read the value of the fire
  uint8_t fires = digitalRead(sensor_pin2);
  publishData2(fires);
//  if (sensor == 1) {
//      digitalWrite(Buzzer, HIGH);
//    } else{
//      digitalWrite(Buzzer, LOW);
//    }

// read the value of the humi&temp
  float h = 44.00;
  float t = 5.00;
//  float h = dht.readHumidity();
//  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("ERROR: Failed to read from DHT sensor!");
    return;
  } else {
    publishData3(t, h);
  }
    delay(10000);
}
