/* 
Although I intended for this software to be run on an ESP32, this is configured to run on an ESP8266.  The only code you should have
to change have comments next to them.  Nothing below the setup function needs modification for proper functionality.

This software is configured to interface with 2 motion sensors on pins 16 and 5 with a relay output on pin 2.
*/

#include <PubSubClient.h>
#include <SPI.h>
#include <ESP8266WiFi.h>

//********************General vars********************
int zonePin[] = {16, 5};                                            //Define pins for where motion sensors are connected
int numZones = sizeof(zonePin)/sizeof(int);
int currentZoneStatus[] = {0, 0};                                   //Match this to have the same number of places as there are zones
int lastZoneStatus[] = {0, 0,};                                     //Match this to have the same number of places as there are zones

int outputPin[] = {2};                                              //Define pins for relay outputs (siren trigger)
int numOutputs = sizeof(outputPin)/sizeof(int);

String mode = "";
//********************General vars********************


//********************MQTT********************
const char* ssid = "****";                                          //WiFi SSID
const char* password = "****";                                      //WiFi password

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

const char* mqtt_server = "192.168.1.199";                          //MQTT client address (this device should be assigned a static IP)

const char* commandTopic = "/home/alarm/controller/command";        //MQTT topic for command (this should match the alarmControllerCommand item)
const char* stateTopic = "/home/alarm/controller/state";            //MQTT topic for state (this should match the alarmStatus item)

const char* zoneTopic[] = {
  "/home/alarm/zone1/state",                                        //Topics for each motion sensor zone (these should be included in the .rules file)
  "/home/alarm/zone2/state",
};
//********************MQTT********************

void setup() {
  
  Serial.begin(115200);
  Serial.println("Power detected");
  
  networkInitialization();
  sensorInitialization();

}

void loop() {
  if (!wifiClient.connected()) {
    reconnect();
  }
  
  mqttClient.loop();
  checkSensors();
  delay(100);
}

void callback(char* topic, byte* payload, unsigned int length) {
  mode = "";
  for (int i = 0; i < length; i++) {
    mode+=(char)payload[i];
  }
  Serial.print("Alarm mode: ");
  Serial.println(mode);

  if(mode == "Arm") {
    Serial.println("System is armed");
    publishCommand(stateTopic, 2);
  }
  if(mode == "Triggered") {
    Serial.println("Alarm triggered and sirens on");
    digitalWrite(outputPin[0], LOW);
  }
  else if(mode == "Disarmed") {
    Serial.println("System disarmed and sirens off");
    digitalWrite(outputPin[0], HIGH);
  }
  
}

void networkInitialization() {
  delay(250);
  Serial.print("Network initialization started.  Connecting to: ");
  Serial.print(ssid);

  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  randomSeed(micros());
  
  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  mqttClient.setServer(mqtt_server, 1883);
  mqttClient.setCallback(callback);
  mqttClient.subscribe(commandTopic);
  mqttClient.subscribe(stateTopic);
  
  Serial.println("Network initialization complete");
}

void sensorInitialization() {
  Serial.println("Sensor initialization started");
  for(int i = 0; i < numZones; i++) {
    pinMode(zonePin[i], INPUT_PULLUP);
  }

  for(int i = 0; i < numOutputs; i++) {
    pinMode(outputPin[i], OUTPUT);
    digitalWrite(outputPin[i], HIGH);
  } 

  Serial.print("Waiting for sensor warmup on ");
  for(int i = 0; i < numZones; i++) {
    Serial.print(i+1);
    while(digitalRead(zonePin[i]) == HIGH) {
    Serial.print(".");
    delay(250);
    }
  }
  Serial.println("");
  Serial.println("Sensor initialization complete");
}

void checkSensors() {
  for(int i = 0; i < numZones; i++) {
    currentZoneStatus[i] = digitalRead(zonePin[i]);
    if(currentZoneStatus[i] != lastZoneStatus[i]) {
      publishCommand(zoneTopic[i], currentZoneStatus[i]);
    }
    lastZoneStatus[i] = currentZoneStatus[i];
  }
}

void publishCommand(String topic,int topic_val){
    Serial.print("Publishing: " + topic + " value:");
    Serial.println(String(topic_val).c_str());
    if(topic_val == 0) {
      mqttClient.publish(topic.c_str(), "Idle", true);
    }
    else if(topic_val == 1) {
      mqttClient.publish(topic.c_str(), "Motion", true);
    }
    else if(topic_val == 2) {
      mqttClient.publish(topic.c_str(), "Armed", true);
    }
    
}

void reconnect() {
  // Loop until we're reconnected
  while (!wifiClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (mqttClient.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      // ... and resubscribe
      mqttClient.subscribe(commandTopic);
      mqttClient.subscribe(stateTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 1 second before retrying
      delay(1000);
    }
  }
}
