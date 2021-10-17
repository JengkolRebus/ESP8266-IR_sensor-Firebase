#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "lightcontrol-95c7b.firebaseio.com"
#define FIREBASE_AUTH "14TJAOaqoV5uzQd7YLGj5YfbxT2LuBzFANszoAcX"
#define WIFI_SSID "1601"
#define WIFI_PASSWORD "gagagaga"

void setup() {
  // put your setup code here, to run once:
  pinMode(D3, OUTPUT);
  Serial.begin(9600);
}

int state = 0;

void loop() {
  // put your main code here, to run repeatedly:
  while(WiFi.status() == WL_CONNECTED){
    state = Firebase.getInt("state");
    if(Firebase.failed()){
      Serial.println(Firebase.error());
      return;
    }
    if(state == 1){
      digitalWrite(D3, HIGH);
    }
    else{
      digitalWrite(D3, LOW);
    }
  }
  
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}
