
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


char auth[] = "OcOD87g6qltuP5q1LipJJUNFV13V8NMr";

char ssid[] = "H@CKER";
char pass[] = "kittu143";
const int trigPin = 14;  //D5
const int echoPin = 12;  //D6

// defines variables
long duration;
int distance;
BlynkTimer timer;
void setup()
{
  // Debug console
  Serial.begin(9600);
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Blynk.begin(auth, ssid, pass);

}

void loop()
{
  // Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
Blynk.virtualWrite(V5,distance);
  Blynk.run();
   timer.run(); // Initiates BlynkTimer
}
