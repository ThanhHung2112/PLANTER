#include <string.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Firebase.h>
#include <FirebaseArduino.h>

#include <NTPClient.h>
#include <WiFiUdp.h>

#define WIFI_SSID "stc"
#define WIFI_PASSWORD "suthanhcon"

#define FIREBASE_HOST "new1-b591a-default-rtdb.firebaseio.com" 
#define FIREBASE_AUTH "1SToaOUtt1dJTTbW0R0sBD4KWOmQaNH8ZasdBAPk"

#define Rx 14             //Định nghĩa chân D5 là Rx
#define Tx 2             //Định nghĩa chân D4 là Tx

const long utcOffsetInSeconds = 25200; //UTC+7 =7*60*60=25200
int x,y,z,d,p,l,k,t,e,s;
int h,m,n;
SoftwareSerial mySerial(Rx, Tx); //Khởi tạo cổng serial mềm
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,"3.th.pool.ntp.org", utcOffsetInSeconds);

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

String dataTX;

void setup() 
{
  Serial.begin(115200);
  mySerial.begin(115200);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
    {
      Serial.print(".");
      delay(500);
    }
  Serial.println();
  Serial.print("connected: ");
  timeClient.begin();
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setString("begin/start","0");
  while ( int b = Firebase.getString("begin/start")!= "1")
    {
      delay(500);
    }
  Firebase.setString("begin/start","0");
  send_data();
}
void loop() 
{
  timeClient.update(); 
  send_data();
}
//-----------------------------------------------------//
void send_data()
{    
  x = Firebase.getString("begin/size/x").toInt()-1;
  y = ((Firebase.getString("begin/size/y").toInt()-1))/2;
  z = Firebase.getInt("begin/size/z");
  d = Firebase.getInt("begin/afterday");
  t = Firebase.getInt("begin/timecheck");
  e = Firebase.getInt("begin/percent_soil");

  h = timeClient.getHours();
  m = timeClient.getMinutes();
//  h = Firebase.getInt("test/hour");        // FOR TESTING
//  m = Firebase.getInt("test/minute");      // FOR TESTING
//  n = Firebase.getInt("test/check");       // FOR TESTING
  
  if ( m == 0 )
    {
      if (h == 5 || h == 17) {p=1;} else { p=0;}
      if (h == t) { k=1;} else {k=0;}
    }
  if (Firebase.getInt("leaf")== 0)
    { l = 1;} else { l = 0 ;}
  if (Firebase.getInt("sensor/soil")<= e)
    { s = 1;} else { s = 0 ;}   
  dataTX = "?" + String(x) + "a" + String(y) + "b" + String(z) + "c" + String(d) + "d" + String(p) + "e" + String(k) + "f" + String(l) + "g" + String(s) + "h";

  mySerial.println(dataTX);
  Serial.println(dataTX);                    // FOR TESTING

}
