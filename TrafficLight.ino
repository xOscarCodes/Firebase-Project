#include <Arduino.h>
#include <WiFiNINA.h>
#include <ArduinoJson.h>
#include <Firebase_Arduino_WiFiNINA.h>

#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""

char ssid[] = SSID;
char pass[] = PASSWORD;

FirebaseData object;
String path = "/status";

#define REDLed 4
#define YELLOWLed 5
#define GREENLed 6

void setup()
{
  Serial.begin(9600);
  pinMode(REDLed, OUTPUT);
  pinMode(YELLOWLed, OUTPUT);
  pinMode(GREENLed, OUTPUT);

  while (WiFi.begin(ssid, pass) != WL_CONNECTED)
  {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.print("You're connected to the ");
  Serial.println(ssid);
  Serial.print("WiFi localIP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, ssid, pass);
  Firebase.reconnectWiFi(true);

  if (Firebase.setString(object, path, "OFF"))
  {
    Serial.println("OK");
  }
  else
  {
    Serial.println("Error: " + object.errorReason());
  }
}

void loop()
{
  if (Firebase.getString(object, path))
  {
    turnOnLED(object.stringData());
  }
  else
  {
    Serial.println("Error");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, ssid, pass);
    Firebase.reconnectWiFi(true);

    if (Firebase.setString(object, path, "OFF"))
    {
      Serial.println("Reconnected: OK");
    }
    else
    {
      Serial.println("Error: " + object.errorReason());
    }
  }
}

void turnOnLED(String status)
{
  if (status == "RED")
  {
    digitalWrite(REDLed, HIGH);
    digitalWrite(YELLOWLed, LOW);
    digitalWrite(GREENLed, LOW);
  }
  else if (status == "YELLOW")
  {
    digitalWrite(REDLed, LOW);
    digitalWrite(YELLOWLed, HIGH);
    digitalWrite(GREENLed, LOW);
  }
  else if (status == "GREEN")
  {
    digitalWrite(REDLed, LOW);
    digitalWrite(YELLOWLed, LOW);
    digitalWrite(GREENLed, HIGH);
  }
  else if (status == "OFF")
  {
    digitalWrite(REDLed, LOW);
    digitalWrite(YELLOWLed, LOW);
    digitalWrite(GREENLed, LOW);
  }
}
