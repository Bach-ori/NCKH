/*-------------------------------------------MQTT---------------------------------------------------*/
#ifndef MQTT_H
#define MQTT_H

#include <WiFi.h>
#include <ArduinoJson.h>

#include <PubSubClient.h>
#include <WiFiClientSecure.h>

const char* mqtt_server = "1cbe44e0762541ce800bd4fb8b250296.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_username = "IOT_BL"; //User
const char* mqtt_password = "123456789"; //Password

//--------------------------------------------------
WiFiClientSecure espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];

//------------Connect to MQTT Broker-----------------------------
void reconnect() 
{
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    String clientID =  "ESPClient-";
    clientID += String(random(0xffff),HEX);
    if (client.connect(clientID.c_str(), mqtt_username, mqtt_password)) 
    {
      Serial.println("connected");
      client.subscribe("0000503380_esp32_receive");
    } 
    else 
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void publishMessage(const char* topic, String payload, boolean retained)
{
  if(client.publish(topic,payload.c_str(),true))
    Serial.println("Message published ["+String(topic)+"]: "+payload);
}

//-----Call back Method for Receiving MQTT massage---------
void callback(char* topic, byte* payload, unsigned int length) 
{
  String incommingMessage = "";
  Serial.println("-------new message from broker-----");
  for(int i=0; i<length;i++) incommingMessage += (char)payload[i];
  Serial.println("Message arived ["+String(topic)+"]"+incommingMessage);
  
  if(incommingMessage == "#")
  {
    message = false;
    data = false;
  }
  else// if(incommingMessage != "#")
  {
    message = true;
    data = true;
  }
  Split(incommingMessage);
}

void setMQTT() 
{
  espClient.setInsecure();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback); // Thiết lập hàm callback
}

void setloopMQTT()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    if (!client.connected()) 
    {
      reconnect();
      //for(;;);
    }
    client.loop(); 
  }
}

void sendMQTT(float heart, int Spo2) 
{ 
  setloopMQTT();
  if (WiFi.status() == WL_CONNECTED)
  {
    char mqtt_message[128];
    sprintf(mqtt_message, "%.2f %d 21.0276703 105.8016783", heart, Spo2);
    publishMessage("0000503380_csdl_receive", mqtt_message, true);  
  }
}

#endif