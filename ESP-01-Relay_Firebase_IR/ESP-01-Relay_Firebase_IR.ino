#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <IRremoteESP8266.h>

// Set these to run example.
#define FIREBASE_HOST "test-web-b3c7b.firebaseio.com"
#define FIREBASE_AUTH "7hycX1uQAIQEgfe2m2IXvBTStYOS8qgAYCZMR6Z7"
#define WIFI_SSID "hahaha"
#define WIFI_PASSWORD "sasasasa"

int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

int lampu = 0;

bool On = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  irrecv.enableIRIn();

  pinMode(lampu, OUTPUT);

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
  if (WiFi.status() == WL_CONNECTED) {
    On = Firebase.getBool("D0");
    if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());
    }

  }

  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    switch (results.value) {
      case 0x1000809:
        if (On == false) {
          On = true;
        }
        else {
          On = false;
        }

        if (WiFi.status() == WL_CONNECTED) {
          if (On == true) {
            Firebase.setBool("D0", true);
          }
          else {
            Firebase.setBool("D0", false);
          }
          if (Firebase.failed()) {
            Serial.print("setting /number failed:");
            Serial.println(Firebase.error());
          }
          delay(150);
          break;
        }
        irrecv.resume();
    }

    if (On == true) {
      Serial.println("On");
      digitalWrite(lampu, HIGH);
      return;
    }
    else {
      Serial.println("Off");
      digitalWrite(lampu, LOW);
    }



  }
}
