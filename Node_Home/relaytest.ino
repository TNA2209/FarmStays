#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define channel1_pin D0 
#define channel2_pin D1  
#define channel3_pin D2
#define channel4_pin D3  
#define FirePin D5
#define BuzzerPin D6
#define waterLevelPin  A0
// Replace with your wifi credentials

const char *ssid = "CaFe Minh Tam";
const char *password = "88888888";

// Replace with your MQTT broker IP address
const char *mqtt_server = "192.168.1.40";

// Replace with your MQTT broker username and password (if any)
const char *mqtt_user = "farmstay";
const char *mqtt_password = "farmstay";

// Replace with your MQTT topics
const char *channel1_topic = "relay1";
const char *channel2_topic = "relay2";
const char *channel3_topic = "relay3";
const char *channel4_topic = "relay4";
const char *sensor_topic1 = "sensor/fire";
const char *sensor_topic2 = "sensor/waterlevel";

const unsigned long sensorInterval = 5000; // Send sensor data every 5 seconds
const unsigned long relayInterval = 10000; // Control the relay every 10 seconds

// Define variables to keep track of the last time sensor data and relay control were sent
unsigned long lastSensorTime = 0;
unsigned long lastRelayTime = 0;
WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi()
{
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *payload, unsigned int length)
{
    // Handle messages on subscribed topics
    if (strcmp(topic, channel1_topic) == 0)
    {
        if (payload[0] == '1')
        {
            digitalWrite(channel1_pin, LOW);
        }
        else
        {
            digitalWrite(channel1_pin, HIGH);
        }
    }
    if (strcmp(topic, channel2_topic) == 0)
    {
        if (payload[0] == '1')
        {
            digitalWrite(channel2_pin, LOW);
        }
        else
        {
            digitalWrite(channel2_pin, HIGH);
        }
    }
    if (strcmp(topic, channel3_topic) == 0)
    {
        if (payload[0] == '1')
        {
            digitalWrite(channel3_pin, LOW);
        }
        else
        {
            digitalWrite(channel3_pin, HIGH);
        }
    }
    if (strcmp(topic, channel4_topic) == 0)
    {
        if (payload[0] == '1')
        {
            digitalWrite(channel4_pin, LOW);
        }
        else
        {
            digitalWrite(channel4_pin, HIGH);
        }
    }
}

void reconnect()
{
    // Loop until we're reconnected
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect("ESP8266Client", mqtt_user, mqtt_password))
        {
            Serial.println("connected");
            // Once connected, subscribe to the channels for each relay
            client.subscribe(channel1_topic);
            client.subscribe(channel2_topic);
            client.subscribe(channel3_topic);
            client.subscribe(channel4_topic);
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void setup()
{
    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
    pinMode(BuzzerPin, OUTPUT);
    // Set Relay pins as outputs
    pinMode(channel1_pin, OUTPUT);
    pinMode(channel2_pin, OUTPUT);
    pinMode(channel3_pin, OUTPUT);
    pinMode(channel4_pin, OUTPUT);
    digitalWrite(channel1_pin, HIGH);
    digitalWrite(channel2_pin, HIGH);
    digitalWrite(channel3_pin, HIGH);
    digitalWrite(channel4_pin, HIGH);
    pinMode(waterLevelPin, INPUT);
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Get the current time
  unsigned long currentTime = millis();

  // Check if it's time to send sensor data
  if (currentTime - lastSensorTime >= sensorInterval) {
    int flameValue = digitalRead(FirePin);
    if (flameValue == HIGH) {
      digitalWrite(BuzzerPin, HIGH);
      client.publish(sensor_topic1, "1");
    } else {
      digitalWrite(BuzzerPin, LOW);
      client.publish(sensor_topic1, "0");
    }
    int waterLevel = analogRead(waterLevelPin);
    client.publish(sensor_topic2, String(waterLevel).c_str());
    lastSensorTime = currentTime; // Update the last sensor time
  }

  // Check if it's time to control the relay
  if (currentTime - lastRelayTime >= relayInterval) {
    // Your code for controlling the relay here
    lastRelayTime = currentTime; // Update the last relay time
  }
}
