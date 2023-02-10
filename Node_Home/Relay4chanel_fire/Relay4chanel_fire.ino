#include <ESP8266WiFi.h>
#include <PubSubClient.h>

/************ WIFI and MQTT INFORMATION ******************/
#define wifi_ssid "CongMinh"
#define wifi_password "minh0919"

const char *MQTT_HOST = "192.168.1.10";
const int MQTT_PORT = 1883;
const char *MQTT_CLIENT_ID = "ESP8266 NodeMCU";
const char *MQTT_USER = "farmstay";
const char *MQTT_PASSWORD = "farmstay";

/****************************** MQTT TOPICS  ***************************************/
#define RelayCommandSub1 "data/relay1/set"         //turn ON turn OFF
#define RelayStatusPub1  "data/relay1/setOK"       //and confirm
#define RelayCommandSub2 "data/relay2/set"         //turn ON turn OFF
#define RelayStatusPub2  "data/relay2/setOK"       //and confirm
#define RelayCommandSub3 "data/relay3/set"         //turn ON turn OFF
#define RelayStatusPub3  "data/relay3/setOK"       //and confirm
#define RelayCommandSub4 "data/relay4/set"         //turn ON turn OFF
#define RelayStatusPub4  "data/relay4/setOK"       //and confirm
#define RelayCommandSub5 "data/relayoffall/set"         //turn ON turn OFF
#define RelayStatusPub5  "data/relayoffall/setOK"       //and confirm
#define RelayCommandSub6 "data/relayonall/set"         //turn ON turn OFF
#define RelayStatusPub6  "data/relayonall/setOK"       //and confirm
#define MQTT_SENSOR_TOPIC "sensor/fire"
/****************************** INPUTS/OUTPUTS  ***************************************/
#define Relay1 D0 
#define Relay2 D1  
#define Relay3 D2
#define Relay4 D3  
#define Fire D5
#define Buzzer D6
WiFiClient espClient;              //initialise a wifi client
PubSubClient client(espClient);   //creates a partially initialised client instance

char msg[50];
int RelayState1 = 0;  //to store relay state
int RelayState2 = 0;
int RelayState3 = 0;
int RelayState4 = 0;
int RelayState5 = 0;
int RelayState6 = 0;


/****************************** SETUP WIFI  ***************************************/
void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    
  }

  randomSeed(micros());  

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD )) {
      Serial.println("connected");
      client.publish(RelayStatusPub1, "0");
      client.subscribe(RelayCommandSub1);
      client.publish(RelayStatusPub2, "0");
      client.subscribe(RelayCommandSub2);
      client.publish(RelayStatusPub3, "0");
      client.subscribe(RelayCommandSub3);
      client.publish(RelayStatusPub4, "0");
      client.subscribe(RelayCommandSub4);
      client.publish(RelayStatusPub5, "0");
      client.subscribe(RelayCommandSub5);
      client.publish(RelayStatusPub6, "0");
      client.subscribe(RelayCommandSub6);
    } 
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  if (strstr(topic, RelayCommandSub1))
  {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '0') {
      digitalWrite(Relay1, HIGH);   // Turn the LED on (Note that LOW is the voltage level
      RelayState1 = 0;
      client.publish(RelayStatusPub1,"0");
    } else {
      digitalWrite(Relay1, LOW);  // Turn the LED off by making the voltage HIGH
      RelayState1 = 1;
      client.publish(RelayStatusPub1,"1");
    }    
  }

  else if ( strstr(topic, RelayCommandSub2))
  {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '0') {
      digitalWrite(Relay2, HIGH);   // Turn the LED on (Note that LOW is the voltage level
      RelayState2 = 0;
      client.publish(RelayStatusPub2,"0");
    } else {
      digitalWrite(Relay2, LOW);  // Turn the LED off by making the voltage HIGH
      RelayState2 = 1;
      client.publish(RelayStatusPub2,"1");
    }
  }
  else if ( strstr(topic, RelayCommandSub3))
  {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '0') {
      digitalWrite(Relay3, HIGH);   // Turn the LED on (Note that LOW is the voltage level
      RelayState3 = 0;
      client.publish(RelayStatusPub3,"0");
    } else {
      digitalWrite(Relay3, LOW);  // Turn the LED off by making the voltage HIGH
      RelayState3 = 1;
      client.publish(RelayStatusPub3,"1");
    }
  }
  else if ( strstr(topic, RelayCommandSub4))
  {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '0') {
      digitalWrite(Relay4, HIGH);   // Turn the LED on (Note that LOW is the voltage level
      RelayState4 = 0;
      client.publish(RelayStatusPub4,"0");
    } else {
      digitalWrite(Relay4, LOW);  // Turn the LED off by making the voltage HIGH
      RelayState4 = 1;
      client.publish(RelayStatusPub4,"1");
    }
  }

   else if ( strstr(topic, RelayCommandSub5))
  {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '0') {
      RelayState5 = 0;
      client.publish(RelayStatusPub1,"0");
      client.publish(RelayCommandSub1,"0");
      client.publish(RelayStatusPub2,"0");
      client.publish(RelayCommandSub2,"0");
      client.publish(RelayStatusPub3,"0");
      client.publish(RelayCommandSub3,"0");
      client.publish(RelayStatusPub4,"0");
      client.publish(RelayCommandSub4,"0");
      client.publish(RelayStatusPub5,"0");
      client.publish(RelayStatusPub6,"0");
      client.publish(RelayCommandSub6,"0");
    } 
  }
     else if ( strstr(topic, RelayCommandSub6))
  {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '1') {
      RelayState6 = 1;
      client.publish(RelayStatusPub1,"1");
      client.publish(RelayCommandSub1,"1");
      client.publish(RelayStatusPub2,"1");
      client.publish(RelayCommandSub2,"1");
      client.publish(RelayStatusPub3,"1");
      client.publish(RelayCommandSub3,"1");
      client.publish(RelayStatusPub4,"1");
      client.publish(RelayCommandSub4,"1");
      client.publish(RelayStatusPub5,"1");
      client.publish(RelayCommandSub5,"1");
      client.publish(RelayStatusPub6,"1");
    } 
  }
  else
  {
    Serial.println("unsubscribed topic");
  }
}

void setup() {
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);
  Serial.begin(112500);
  digitalWrite(Relay1, HIGH);
  digitalWrite(Relay2, HIGH);
  digitalWrite(Relay3, HIGH);
  digitalWrite(Relay4, HIGH);
  pinMode(Fire, INPUT);
  pinMode(Buzzer, OUTPUT);
  setup_wifi(); 
  client.setServer(MQTT_HOST, MQTT_PORT);  //client is now ready for use
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); 
  int flameValue = digitalRead(Fire);
  if (flameValue == HIGH) {
    digitalWrite(Buzzer, HIGH);
    client.publish(MQTT_SENSOR_TOPIC, "1");
  } else {
    digitalWrite(Buzzer, LOW);
    client.publish(MQTT_SENSOR_TOPIC, "0");
  }
}
