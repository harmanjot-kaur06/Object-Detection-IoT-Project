#include <WiFi.h>
#include "ThingSpeak.h"  

#define IR_SENSOR_PIN 4  // IR sensor is connected to GPIO 4
#define BUZZER_PIN 5     // Buzzer is connected to GPIO 5

const char* ssid = "your_SSID";         // Replace with your WiFi SSID
const char* password = "your_PASSWORD"; // Replace with your WiFi Password

WiFiClient client;

unsigned long myChannelNumber = YOUR_CHANNEL_NUMBER;  // Replace with your ThingSpeak Channel Number
const char* myWriteAPIKey = "YOUR_API_KEY";           // Replace with your ThingSpeak Write API Key

int sensorValue = 0;

void setup() {
  Serial.begin(115200);
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
  ThingSpeak.begin(client); // Initialize ThingSpeak
}

void loop() {
  sensorValue = digitalRead(IR_SENSOR_PIN);

  if (sensorValue == LOW) {
    Serial.println("Object Detected!");
    digitalWrite(BUZZER_PIN, HIGH);
    ThingSpeak.writeField(myChannelNumber, 1, 1, myWriteAPIKey); // Send 1 to channel
  } else {
    Serial.println("No Object Detected");
    digitalWrite(BUZZER_PIN, LOW);
    ThingSpeak.writeField(myChannelNumber, 1, 0, myWriteAPIKey); // Send 0 to channel
  }

  delay(2000); // Delay before next reading
}
