#include <WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <string.h>
#include<ThingSpeak.h>
  
 
const char* ssid = "kapankoghar0";   // your network SSID 
const char* password = "kgfrrr2022";
const char* server = "api.thingspeak.com";
unsigned long myChannelNumber = 1864319;
const char* myWriteAPIKey = "A30GAB5R6JP5LKVA";
const int SensorPin = 12;
int soilMoistureValue = 0;
int relaypin = 4;
 
WiFiClient client;
 
 
  
void setup(){
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  wifiConnect();
    pinMode(relaypin, OUTPUT);

}

void loop() 
{

  soilMoistureValue = analogRead(SensorPin);  //put Sensor insert into soil
  Serial.println(soilMoistureValue);

  if(soilMoistureValue >= 3032)
  {
    digitalWrite(relaypin, HIGH);

    Serial.println("Motor is OFF");
  }
  else 
  {
    digitalWrite(relaypin, LOW);
   
    Serial.println("Motor is ON");
  }
  
   
    
    ThingSpeak.setField(1, soilMoistureValue);
   
    ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
 
    delay(5000);

}
// Function to connect WiFi
void wifiConnect(){
  Serial.println("Connecting to WiFi!");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println("WiFi connected.");
}