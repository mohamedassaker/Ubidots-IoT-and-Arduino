/****************************************
* Include Libraries
****************************************/

#include "Ubidots.h"

/****************************************
* Define Instances and Constants
****************************************/   
 
const char* UBIDOTS_TOKEN = "BBFF-ynsTc4Da6WTr7gxKiRqtq8t6edYrHq";  // Put here your Ubidots TOKEN
const char* WIFI_SSID = "Test";      // Put here your Wi-Fi SSID
const char* WIFI_PASS = "12345678";      // Put here your Wi-Fi password 

Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);

/****************************************
* Auxiliar Functions
****************************************/

// Put here your auxiliar functions

/****************************************
* Main Functions
****************************************/  

void setup() {                       

  Serial.begin(115200);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  // ubidots.setDebug(true);  // Uncomment this line for printing debug  messages                     
}

void loop() {
    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    
    // This will send the request to the server
    int analogValue = analogRead(A0);
    float millivolts = (analogValue/1024.0) * 3300; //3300 is the voltage provided by NodeMCU
    float celsius = millivolts/100;
    Serial.print("temperature: ");
    Serial.println(celsius);

    client.print("temperature: ");
    client.println(celsius);
  
    Serial.println("wait 5 sec...");
    delay(5000);

  ubidots.add("temperature", celsius);// Change for your variable name  
  
  bool bufferSent = false;
  bufferSent = ubidots.send(); // Will send data to a device label that matches the device Id

  if (bufferSent) {
   Serial.println("Values sent by the device");
  }
  delay(5000);
}

