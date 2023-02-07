#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "SPI.h"
#include "MFRC522.h"
#include <Servo.h>
#include <ArduinoJson.h>


#define MQTT_VERSION MQTT_VERSION_3_1_1
#define SS_PIN 4
#define RST_PIN 5

// Wifi: SSID and password
const PROGMEM char* WIFI_SSID = "CongMinh";
const PROGMEM char* WIFI_PASSWORD = "minh0919";

// MQTT: ID, server IP, port, username and password
const PROGMEM char* MQTT_CLIENT_ID = "sensor_farm";
const PROGMEM char* MQTT_SERVER_IP = "192.168.1.45";
const PROGMEM uint16_t MQTT_SERVER_PORT = 1883;
const PROGMEM char* MQTT_USER = "farmstay";
const PROGMEM char* MQTT_PASSWORD = "farmstay";
const PROGMEM char* MQTT_RFID_TOPIC = "sensor/rfid";

String strID="";
uint8_t qos = 1;
Servo myServo;
String UID1= "D3:75:75:08";
String UID2= "F3:EA:3A:08";
String UID3 ="63:26:9B:08";
String UID4 ="F3:08:86:A3";
MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

WiFiClient wifiClient;
PubSubClient client(wifiClient);


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
String rfidCard(){
  strID="";
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
  return "";
  for (byte i = 0; i < 4; i++) {
    strID += (rfid.uid.uidByte[i] < 0x10 ? "0" : "") + String(rfid.uid.uidByte[i], HEX) + (i!=3 ? ":" : "");
  }
  strID.toUpperCase();
return strID;
}
void check(){
  String rfidCardValue = rfidCard();   
  if (rfidCardValue != ""){
      StaticJsonBuffer<300> JSONbuffer;
      JsonObject& JSONencoder = JSONbuffer.createObject();
      char JSONmessageBuffer[100];
      Serial.println(rfidCardValue);
        if (rfidCardValue == UID1){
          JSONencoder["UID"] = (char*) rfidCardValue.c_str();
          JSONencoder["UserName"] = "Trần Nam Anh";
          JSONencoder["Status"] = "Open Door";
          JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
          client.publish(MQTT_RFID_TOPIC,JSONmessageBuffer,false);
          myServo.write(90);
          delay(60000);
          myServo.write(0);

        }
       else if (rfidCardValue == UID2){
          JSONencoder["UID"] = (char*) rfidCardValue.c_str();
          JSONencoder["UserName"] = "Tăng Hồ Trung Nam";
          JSONencoder["Status"] = "Open Door";
          JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
          client.publish(MQTT_RFID_TOPIC,JSONmessageBuffer,false);
          myServo.write(90);
          delay(60000);
          myServo.write(0);
        }
       else if (rfidCardValue == UID3){
          JSONencoder["UID"] = (char*) rfidCardValue.c_str();
          JSONencoder["UserName"] = "Đoàn Hoàng Ca";
          JSONencoder["Status"] = "Open Door";
          JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
          client.publish(MQTT_RFID_TOPIC,JSONmessageBuffer,false);
          myServo.write(90);
          delay(60000);
          myServo.write(0);
        }
       else if (rfidCardValue == UID4){
          JSONencoder["UID"] = (char*) rfidCardValue.c_str();
          JSONencoder["UserName"] = "Customer";
          JSONencoder["Status"] = "Open Door";
          JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
          client.publish(MQTT_RFID_TOPIC,JSONmessageBuffer,false);
          myServo.write(90);
          delay(60000);
          myServo.write(0);

        }
       else{
          JSONencoder["No information"] = (char*) rfidCardValue.c_str();
          JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
          client.publish(MQTT_RFID_TOPIC,JSONmessageBuffer,false);
        }
      }       
     }
void setup() {
  // init the serial
  Serial.begin(115200);
  SPI.begin();
  myServo.attach(16); 
  myServo.write(0);
  rfid.PCD_Init();
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
  if (client.connected()){
    check();
    } 
}
