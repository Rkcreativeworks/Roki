//#define BLYNK_PRINT Serial
// Virtual V7 collect readings from water tank
//Virtual V5 send data to Horizontal Level in app
//Virtual V1 connected to light
//Virtual V2 connected to motor

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include "SSD1306.h"
BlynkTimer timer;
SSD1306  display(0x3C, D1, D2);//SDA,SCK

char auth[] = "Mt1Ydd29A4hq79VrnDCFjKqA1MO8A7xE";

char ssid[] = "H@CKER";
char pass[] = "kittu143";
#define DEBUG_SW 0


#define S1 D6
#define R1 D0

#define S2 D7
#define R2 D5

#define Buzzer D8

int count=0;
int count1=0;

boolean buz_mode_on=false;
boolean buz_mode_off=false;
int MODE = 0;





int switch_ON_Flag1_previous_I = 0;
int switch_ON_Flag2_previous_I = 0;

WidgetTerminal terminal(V9);

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  digitalWrite(R1, pinValue);
  // process received value
}

BLYNK_WRITE(V2)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V2 to a variable
  digitalWrite(R2, pinValue);
  // process received value
}

BLYNK_WRITE(V3)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V2 to a variable
 Serial.println(pinValue);
 if(pinValue<=30){
  buz_mode_on=false;
  count=0;
  Serial.print("count");
  Serial.println(count);
 }
    if(pinValue==80){
      if(count==0&&buz_mode_on==false){
        for(count;count<=19;count++){
          Serial.print("Buzzer on");
          digitalWrite(Buzzer,HIGH);
          delay(200);
          digitalWrite(Buzzer,LOW);
          delay(200);
          Serial.println(count);
        if(count==18){
          buz_mode_on=true;
        }
       }
      }
     }

     if(pinValue>=75){
  buz_mode_on=false;
  count1=0;
  Serial.print("count");
  Serial.println(count1);
 }
    if(pinValue==19){
      if(count1==0&&buz_mode_off==false){
        for(count1;count1<=19;count1++){
          Serial.print("Buzzer on");
          digitalWrite(Buzzer,HIGH);
          delay(1000);
          digitalWrite(Buzzer,LOW);
          delay(500);
          Serial.println(count);
        if(count1==18){
          buz_mode_on=true;
        }
       }
      }
     }
  // process received value
}


BLYNK_WRITE(V7)
{
  display.clear();
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  if(pinValue){
  Serial.println(pinValue);
  int y=map(pinValue, 100, 18, 0, 100);
  String h=String(y);
  
  
  display.setFont(Calligraffitti_Regular_16);
  display.drawString(20,0, "Water Level");  
 
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(Roboto_Black_36);
  
  display.drawString(20,20,h);
  display.drawString(88,20,"%");
  display.display();

  // process received value
}else{
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_16);
   display.drawString(0,10, "Water Tank");  
  display.drawString(0,30, "Disconnected..");  
  display.display();
}
}

void with_internet()
{
  if (digitalRead(S1) == LOW)
  {
    if (switch_ON_Flag1_previous_I == 0 )
    {
      digitalWrite(R1, LOW);
      if (DEBUG_SW) Serial.println("Relay1- ON");
      Blynk.virtualWrite(V1, 0);
      switch_ON_Flag1_previous_I = 1;
    }
    if (DEBUG_SW) Serial.println("Switch1 -ON");

  }
  if (digitalRead(S1) == HIGH )
  {
    if (switch_ON_Flag1_previous_I == 1)
    {
      digitalWrite(R1, HIGH);
      if (DEBUG_SW) Serial.println("Relay1 OFF");
      Blynk.virtualWrite(V1, 1);
      switch_ON_Flag1_previous_I = 0;
    }
    if (DEBUG_SW)Serial.println("Switch1 OFF");
  }


  if (digitalRead(S2) == LOW)
  {
    if (switch_ON_Flag2_previous_I == 0 )
    {
      digitalWrite(R2, LOW);
      if (DEBUG_SW)  Serial.println("Relay2- ON");
      Blynk.virtualWrite(V2, 0);
      switch_ON_Flag2_previous_I = 1;
    }
    if (DEBUG_SW) Serial.println("Switch2 -ON");

  }
  if (digitalRead(S2) == HIGH )
  {
    if (switch_ON_Flag2_previous_I == 1)
    {
      digitalWrite(R2, HIGH);
      if (DEBUG_SW) Serial.println("Relay2 OFF");
      Blynk.virtualWrite(V2, 1);
      switch_ON_Flag2_previous_I = 0;
    }
    if (DEBUG_SW)Serial.println("Switch2 OFF");
    //delay(200);
  }

 

}

void without_internet()
{

  digitalWrite(R1, digitalRead(S1));
  digitalWrite(R2, digitalRead(S2));


}


void checkBlynk() { // called every 3 seconds by SimpleTimer

  bool isconnected = Blynk.connected();
  if (isconnected == false) {
    MODE = 1;
   
  }
  if (isconnected == true) {
    MODE = 0;
    
  }
}


void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  
  if (DEBUG_SW) Serial.begin(9600);
  pinMode(S1, INPUT);
  pinMode(R1, OUTPUT);

  pinMode(S2, INPUT);
  pinMode(R2, OUTPUT);
  pinMode(Buzzer, OUTPUT); 
  digitalWrite(R1,HIGH);
  digitalWrite(R2,HIGH);
  digitalWrite(Buzzer,LOW);
  Blynk.notify("Hey your Device {DEVICE_NAME} was online");


Blynk.begin(auth, ssid, pass);
  timer.setInterval(3000L, checkBlynk); // check if connected to Blynk server every 3 seconds
 
display.init();
display.clear();
 display.setFont(Calligraffitti_Regular_16);
  display.drawString(20,0, "Water Level");
  display.display();
}

void loop()
{
 if (WiFi.status() != WL_CONNECTED)
  {
    if (DEBUG_SW) Serial.println("Not Connected");
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_16);
  display.drawString(0,30, "Disconnected..");  
  display.display();
  }
  else
  {
    if (DEBUG_SW) Serial.println(" Connected");
    Blynk.run();
  }

  timer.run(); // Initiates SimpleTimer
  if (MODE == 0)
    with_internet();
  else
    without_internet();
}
