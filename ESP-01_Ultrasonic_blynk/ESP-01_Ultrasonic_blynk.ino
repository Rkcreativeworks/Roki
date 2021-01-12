#include <SPI.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "biihHphUJbmxXSjc3oAHMzX76s-AXmIB";
char ssid[] = "Xiaomi_899C";
char pass[] = "9052879993";
WidgetBridge bridge1(V2);


BlynkTimer timer;
const int trigPin = 0;  
const int echoPin = 2;  

// defines variables
long duration;
int distance;

#define DEBUG_SW 0

WidgetTerminal terminal(V1);


int MODE = 0;



void with_internet()
{
  

}

void without_internet()
{


}


void checkBlynk() { 
  bool isconnected = Blynk.connected();
  if (isconnected == false) {
    MODE = 1;
   
  }
  if (isconnected == true) {
    MODE = 0;
    
  }
}
BLYNK_CONNECTED() {
  bridge1.setAuthToken("5hMALkoynlMI6Q4Em9UxDKtj88sAcx8X"); // Place the AuthToken of the second hardware here
}


void setup()
{
  // Debug console
  if (DEBUG_SW) Serial.begin(9600);
 
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT);

Blynk.begin(auth, ssid, pass);
  timer.setInterval(3000L, checkBlynk); // check if connected to Blynk server every 3 seconds
 
  terminal.clear();

 terminal.println(F("Blynk v" BLYNK_VERSION ": Device started"));
  terminal.println(F("-------------"));
   terminal.println(F("Water Level Indicator"));
  terminal.flush();

}

void loop()
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
Serial.print("Distance: ");
Serial.println(distance);

  if (WiFi.status() != WL_CONNECTED)
  {
    if (DEBUG_SW) Serial.println("Not Connected");
  }
  else
  {
    if (DEBUG_SW) Serial.println(" Connected");
    Blynk.virtualWrite(V5,distance);
    bridge1.virtualWrite(V7,distance);
    terminal.print("Distance: ");
    terminal.print(distance);
    terminal.println(" CM");
    terminal.flush();
    delay(1000);
    Blynk.run();
  }

  timer.run(); // Initiates SimpleTimer
  if (MODE == 0)
    with_internet();
  else
    without_internet();
}
