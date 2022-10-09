#include <WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include<ThingSpeak.h>
const char* ssid = "kapankoghar0";   // your network SSID 
const char* password = "kgfrrr2022";  

  const int relay = 4;
 
const int sensor = 12;

int sensor_value = 0;
 

unsigned long myChannelNumber = 1864319;
const char* myWriteAPIKey = "A30GAB5R6JP5LKVA";
WiFiClient  client;

void setup(){
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  wifiConnect();
  
     pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  delay(5000);
  
}

void loop() {
  sensor_value = analogRead(sensor);
  Serial.println(sensor_value);
  sensor_value = map(sensor_value, 4095, 1920, 0, 100);
  Serial.println(sensor_value);
  if(sensor_value < 30){
    digitalWrite(relay, LOW);
    Serial.println(digitalRead(relay));
  } else {
    digitalWrite(relay, HIGH);
    Serial.println(digitalRead(relay));
  }

 ThingSpeak.setField(1, sensor_value);
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
  