#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <Wire.h>

//Setup WiFI
#define WIFI_SSID "Zem!"
#define WIFI_PASS "bismillah"

//Setup Firebase
#define HOST "https://projekiot-8b4d3-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define AUTH "dvXloOD7EATHijvOze2vSwyR99bYPtzYmsCLxlOZ"

FirebaseData firebase;
FirebaseJson json;

String bpm;

String heartRate(){
  String c;
  Wire.requestFrom(0xA0 >> 1, 1);    
    while(Wire.available()) {          
        c = Wire.read();   
    }
  return c;
}

void transmitData(){
  Firebase.setString(firebase, "RikoSemarang/sensor/denyut nadi", bpm);
  digitalWrite(2, LOW);
    delay(100);
    digitalWrite(2, HIGH);
    delay(100);
}

void setup(){
  Serial.begin(115200);
  
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to WiFi");
  while(WiFi.status() != WL_CONNECTED){
    Serial.println("......");
    delay(100);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(HOST, AUTH);
  Firebase.reconnectWiFi(true);
  
  Wire.begin();
  
  pinMode(2, OUTPUT);
}

void loop(){
  bpm = heartRate();
  Serial.println(bpm);
  transmitData();
  delay(5000);
}
