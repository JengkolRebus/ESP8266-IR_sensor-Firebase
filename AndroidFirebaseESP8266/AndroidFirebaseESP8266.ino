#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>

// Set these to run example.
#define FIREBASE_HOST "lightcontrol-95c7b.firebaseio.com"
#define FIREBASE_AUTH "14TJAOaqoV5uzQd7YLGj5YfbxT2LuBzFANszoAcX"
#define WIFI_SSID "1601"
#define WIFI_PASSWORD "gagagaga"

int state = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BUILTIN_LED, OUTPUT);

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

void loop() {
  // put your main code here, to run repeatedly:
  state = Firebase.getInt("/state");
  
  if(state == 1){
    Serial.println("Light On");
    digitalWrite(BUILTIN_LED, HIGH);
  }
  else{
    Serial.println("Light Off");
    digitalWrite(BUILTIN_LED, LOW);
  }

}
