#include <Servo.h>
#include <SoftwareSerial.h>

#define BUT 13
#define RELAY 12 
#define PULF 2    //define Pulse pin 
#define PULR 4    //define Pulse pin 
#define PULU 7    //define Pulse pin 
#define PULW 8    //define Pulse pin 

#define DIR 3     //define Direction pin 

#define Rx 5             
#define Tx 6

unsigned long time1 = 0;
int timedetect = 6000;
int microStep = 16; 
float angleStep = 1.8;
float stepsPerRound = microStep * 360.0 / angleStep; 

int s,a,b,c,x,y,z;
int dv, chuc, tram;
int x01,y01,z01,d01,l01,p01,k01,s01;
int g = 3;

long steps_fb;  //28 (-1)
long steps_rl; //48 (-1)
long steps_ud; //8 (-1)
long steps_w;
      
Servo myservo;
SoftwareSerial mySerial(Rx, Tx);

void setup() 
{
  Serial.begin(115200); 
  mySerial.begin(115200);
  myservo.attach(11);
  myservo.write(0);
  
  pinMode(PULF, OUTPUT);
  pinMode(PULR, OUTPUT);
  pinMode(PULU, OUTPUT);
  pinMode(PULW, OUTPUT);
  
  pinMode(DIR, OUTPUT);
  pinMode(BUT, INPUT_PULLUP);
    
  digitalWrite(PULF, LOW);
  digitalWrite(PULR, LOW);
  digitalWrite(PULU, LOW);
  digitalWrite(PULW, LOW);
  digitalWrite(BUT, HIGH);

  while (digitalRead(BUT)!= LOW)
    {
      receive_data_begin();
    }
  start();
  firstpoint();
}

void loop()
{
  control();
}
//--------------------------------------------------------//
void forward_back()
{
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULF, HIGH); 
      delayMicroseconds(200);
      digitalWrite(PULF, LOW);
      delayMicroseconds(200);
    }
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULF, HIGH); 
      delayMicroseconds(160);
      digitalWrite(PULF, LOW);
      delayMicroseconds(160);
    }
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULF, HIGH); 
      delayMicroseconds(120);
      digitalWrite(PULF, LOW);
      delayMicroseconds(120);
    }
  for (long i = 1; i <= steps_fb; i++) 
    {
      digitalWrite(PULF, HIGH); 
      delayMicroseconds(80);
      digitalWrite(PULF, LOW);
      delayMicroseconds(80);
    }
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULF, HIGH); 
      delayMicroseconds(120);
      digitalWrite(PULF, LOW);
      delayMicroseconds(120);
    }
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULF, HIGH); 
      delayMicroseconds(160);
      digitalWrite(PULF, LOW);
      delayMicroseconds(160);
    }
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULF, HIGH); 
      delayMicroseconds(200);
      digitalWrite(PULF, LOW);
      delayMicroseconds(200);
    }
}
//--------------------------------------------------------//
void right_left()
{
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULR, HIGH); 
      delayMicroseconds(300);
      digitalWrite(PULR, LOW);
      delayMicroseconds(300);
    }
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULR, HIGH); 
      delayMicroseconds(200);
      digitalWrite(PULR, LOW);
      delayMicroseconds(200);
    }
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULR, HIGH); 
      delayMicroseconds(100);
      digitalWrite(PULR, LOW);
      delayMicroseconds(100);
    }
  for (long i = 1; i <= steps_rl; i++)
    {
      digitalWrite(PULR, HIGH); 
      delayMicroseconds(40);
      digitalWrite(PULR, LOW);
      delayMicroseconds(40);
    }
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULR, HIGH); 
      delayMicroseconds(100);
      digitalWrite(PULR, LOW);
      delayMicroseconds(100);
    }
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULR, HIGH); 
      delayMicroseconds(200);
      digitalWrite(PULR, LOW);
      delayMicroseconds(200);
    }
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULR, HIGH); 
      delayMicroseconds(300);
      digitalWrite(PULR, LOW);
      delayMicroseconds(300);
    }
}
//--------------------------------------------------------//
void up_down()
{
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULU, HIGH); 
      delayMicroseconds(300);
      digitalWrite(PULU, LOW);
      delayMicroseconds(300);
    }
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULU, HIGH); 
      delayMicroseconds(200);
      digitalWrite(PULU, LOW);
      delayMicroseconds(200);
    }
  seed_u();
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULU, HIGH); 
      delayMicroseconds(100);
      digitalWrite(PULU, LOW);
      delayMicroseconds(100);
    }
  for (long i = 1; i <= steps_ud; i++)
    {
      digitalWrite(PULU, HIGH); 
      delayMicroseconds(40);
      digitalWrite(PULU, LOW);
      delayMicroseconds(40);
    }
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULU, HIGH); 
      delayMicroseconds(100);
      digitalWrite(PULU, LOW);
      delayMicroseconds(100);
    }
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULU, HIGH); 
      delayMicroseconds(200);
      digitalWrite(PULU, LOW);
      delayMicroseconds(200);
    }
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULU, HIGH); 
      delayMicroseconds(300);
      digitalWrite(PULU, LOW);
      delayMicroseconds(300);
    }
}
//--------------------------------------------------------//
void up_down_check()
{
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULU, HIGH); 
      delayMicroseconds(300);
      digitalWrite(PULU, LOW);
      delayMicroseconds(300);
    }
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULU, HIGH); 
      delayMicroseconds(200);
      digitalWrite(PULU, LOW);
      delayMicroseconds(200);
    }
  seed_u();
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULU, HIGH); 
      delayMicroseconds(100);
      digitalWrite(PULU, LOW);
      delayMicroseconds(100);
    }
  for (long i = 1; i <= (c-g) * stepsPerRound; i++)
    {
      digitalWrite(PULU, HIGH); 
      delayMicroseconds(40);
      digitalWrite(PULU, LOW);
      delayMicroseconds(40);
    }
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULU, HIGH); 
      delayMicroseconds(100);
      digitalWrite(PULU, LOW);
      delayMicroseconds(100);
    }
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULU, HIGH); 
      delayMicroseconds(200);
      digitalWrite(PULU, LOW);
      delayMicroseconds(200);
    }
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULU, HIGH); 
      delayMicroseconds(300);
      digitalWrite(PULU, LOW);
      delayMicroseconds(300);
    }
}
//--------------------------------------------------------//
void up_down_seed_check()
{
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULU, HIGH); 
      delayMicroseconds(300);
      digitalWrite(PULU, LOW);
      delayMicroseconds(300);
    }
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULU, HIGH); 
      delayMicroseconds(200);
      digitalWrite(PULU, LOW);
      delayMicroseconds(200);
    }
  seed_u();
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULU, HIGH); 
      delayMicroseconds(100);
      digitalWrite(PULU, LOW);
      delayMicroseconds(100);
    }
  for (long i = 1; i <= (g-1) * stepsPerRound; i++)
    {
      digitalWrite(PULU, HIGH); 
      delayMicroseconds(40);
      digitalWrite(PULU, LOW);
      delayMicroseconds(40);
    }
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULU, HIGH); 
      delayMicroseconds(100);
      digitalWrite(PULU, LOW);
      delayMicroseconds(100);
    }
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULU, HIGH); 
      delayMicroseconds(200);
      digitalWrite(PULU, LOW);
      delayMicroseconds(200);
    }
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULU, HIGH); 
      delayMicroseconds(300);
      digitalWrite(PULU, LOW);
      delayMicroseconds(300);
    }
}
//--------------------------------------------------------//
void wing()
{
  for (long i = 1; i <= steps_w; i++)
    {
      digitalWrite(PULW, HIGH); 
      delayMicroseconds(100);
      digitalWrite(PULW, LOW);
      delayMicroseconds(100);
    }
  digitalWrite(PULW, HIGH);
}
//--------------------------------------------------------//
void seed_d()
{
  myservo.write(120);
  delay(50);
  wing();
}
//--------------------------------------------------------//
void seed_u()
{
  myservo.write(0);
}
//--------------------------------------------------------//
void water()
{
  digitalWrite(RELAY, HIGH);
  delay(500);
  digitalWrite(RELAY, LOW);
}
//--------------------------------------------------------//
void start()
{
  for (long m = 1; m <= y; m++)
    {
    for (long n = 1; n <= x; n++)
      {
        digitalWrite(DIR, LOW);
        up_down();
        seed_d();
        digitalWrite(DIR, HIGH);
        up_down();
        water();
        digitalWrite(DIR, HIGH);
        forward_back(); 
      }
    digitalWrite(DIR, LOW);
    up_down();
    seed_d();
    digitalWrite(DIR, HIGH);
    up_down();
    water();
    right_left();
    for (long n = 1; n <= x; n++)
      {
        digitalWrite(DIR, LOW);
        up_down();
        seed_d();
        digitalWrite(DIR, HIGH);
        up_down();
        water();
        digitalWrite(DIR, LOW);
        forward_back(); 
      }
    digitalWrite(DIR, LOW);
    up_down();
    seed_d();
    digitalWrite(DIR, HIGH);
    up_down();
    water();
    right_left();     
    }
  for (long n = 1; n <= x; n++)
    {
      digitalWrite(DIR, LOW);
      up_down();
      seed_d();
      digitalWrite(DIR, HIGH);
      up_down();
      water();
      digitalWrite(DIR, HIGH);
      forward_back();
    }
  digitalWrite(DIR, LOW);
  up_down();
  seed_d();
  digitalWrite(DIR, HIGH);
  up_down();
  water();
}
//--------------------------------------------------------//
void firstpoint()
{
  digitalWrite(DIR, LOW);
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULR, HIGH); 
      delayMicroseconds(300);
      digitalWrite(PULR, LOW);
      delayMicroseconds(300);
    }
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULR, HIGH); 
      delayMicroseconds(200);
      digitalWrite(PULR, LOW);
      delayMicroseconds(200);
    }
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULR, HIGH); 
      delayMicroseconds(100);
      digitalWrite(PULR, LOW);
      delayMicroseconds(100);
    } 
  for (long i = 1; i <= 2*((b+1)*y-1)*stepsPerRound; i++)
    {
      digitalWrite(PULR, HIGH); 
      delayMicroseconds(40);
      digitalWrite(PULR, LOW);
      delayMicroseconds(40);
    }
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULR, HIGH); 
      delayMicroseconds(100);
      digitalWrite(PULR, LOW);
      delayMicroseconds(100);
    }
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULR, HIGH); 
      delayMicroseconds(200);
      digitalWrite(PULR, LOW);
      delayMicroseconds(200);
    }
  for (long i = 1; i <= stepsPerRound/6; i++)
    {
      digitalWrite(PULR, HIGH); 
      delayMicroseconds(300);
      digitalWrite(PULR, LOW);
      delayMicroseconds(300);
    }
  for (long i = 1; i <= stepsPerRound; i++) // fix distance
    {
      digitalWrite(PULR, HIGH); 
      delayMicroseconds(300);
      digitalWrite(PULR, LOW);
      delayMicroseconds(300);
    }    
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
  for (long i = 1; i <= stepsPerRound/2; i++) 
    {
      digitalWrite(PULF, HIGH); 
      delayMicroseconds(120);
      digitalWrite(PULF, LOW);
      delayMicroseconds(120);
    }
  for (long i = 1; i <= ((a+1)*x-1)*stepsPerRound; i++) 
    {
      digitalWrite(PULF, HIGH); 
      delayMicroseconds(70);
      digitalWrite(PULF, LOW);
      delayMicroseconds(70);
    }
  for (long i = 1; i <= stepsPerRound/2; i++) // fix distance
    {
      digitalWrite(PULF, HIGH); 
      delayMicroseconds(120);
      digitalWrite(PULF, LOW);
      delayMicroseconds(120);
    }
}
//--------------------------------------------------------//
void watertime()
{
  for (long m = 1; m <= y; m++)
    {
    for (long n = 1; n <= x; n++)
      {
        water();
        digitalWrite(DIR, HIGH);
        forward_back(); 
      }
    water();
    digitalWrite(DIR, HIGH);
    right_left();
    for (long n = 1; n <= x; n++)
      {
        water();
        digitalWrite(DIR, LOW);
        forward_back(); 
      }
    water();
    digitalWrite(DIR, HIGH);
    right_left();     
    }
  for (long n = 1; n <= x; n++)
    {
      water();
      digitalWrite(DIR, HIGH);
      forward_back();
    }
  water();
}
//--------------------------------------------------------//
void sensor_detect()
{
  time1 = millis();
  while ( (unsigned long) (millis() - time1) < timedetect )
    {
      receive_data_loop();
    }
  if (l01 == 1)
    {
      digitalWrite(DIR, LOW);
      up_down_seed_check();
      seed_d();
      digitalWrite(DIR, HIGH);
      up_down_seed_check();
      water();
    }
  else if (s01 == 1)
    { water();} 
}
//--------------------------------------------------------//
void checktime()
{
  for (long m = 1; m <= y; m++)
    {
    for (long n = 1; n <= x; n++)
      {
        digitalWrite(DIR, LOW);
        up_down_check();
        sensor_detect();
        digitalWrite(DIR, HIGH);
        up_down_check();
        digitalWrite(DIR, HIGH);
        forward_back(); 
      }
    digitalWrite(DIR, LOW);
    up_down_check();
    sensor_detect();
    digitalWrite(DIR, HIGH);
    up_down_check();
    right_left();
    for (long n = 1; n <= x; n++)
      {
        digitalWrite(DIR, LOW);
        up_down_check();
        sensor_detect();
        digitalWrite(DIR, HIGH);
        up_down_check();
        digitalWrite(DIR, LOW);
        forward_back(); 
      }
    digitalWrite(DIR, LOW);
    up_down_check();
    sensor_detect();
    digitalWrite(DIR, HIGH);
    up_down_check();
    right_left();     
    }
  for (long n = 1; n <= x; n++)
    {
      digitalWrite(DIR, LOW);
      up_down_check();
      sensor_detect();
      digitalWrite(DIR, HIGH);
      up_down_check();
      digitalWrite(DIR, HIGH);
      forward_back();
    }
  digitalWrite(DIR, LOW);
  up_down_check();
  sensor_detect();
  digitalWrite(DIR, HIGH);
  up_down_check();
}
//--------------------------------------------------------//
void receive_data_begin()
{
  if (Serial.available())
    {
      String dataRX;
      while(Serial.available())
        {
          char g = Serial.read();
          dataRX += g;
          mySerial.println(dataRX);
        }   
      s= dataRX.indexOf("a")- dataRX.indexOf("?");
      if (s==2){ x01 =dataRX[dataRX.indexOf("?")+1]-'0';}
      else if (s==3){ chuc =dataRX[dataRX.indexOf("?")+1]-'0'; dv =dataRX[dataRX.indexOf("?")+2]-'0'; x01=chuc*10 +dv;}
            
      s= dataRX.indexOf("b")- dataRX.indexOf("a");
      if (s==2) { y01 =dataRX[dataRX.indexOf("a")+1]-'0';}
      else if (s==3){ chuc =dataRX[dataRX.indexOf("a")+1]-'0'; dv =dataRX[dataRX.indexOf("a")+2]-'0'; y01=chuc*10 +dv;}
          
      s= dataRX.indexOf("c")- dataRX.indexOf("b");
      if (s==2) { z01 =dataRX[dataRX.indexOf("b")+1]-'0';}
      else if (s==3){ chuc =dataRX[dataRX.indexOf("b")+1]-'0'; dv =dataRX[dataRX.indexOf("b")+2]-'0'; z01=chuc*10 +dv;}
        
      x = x01; //28, 14, 9, 7, 5, 4, 3, 2, 1  
      y = y01;
      z = z01; // 7, 5, 3

//      mySerial.println(x);
//      mySerial.println(y);
//      mySerial.println(z);
      
      a = (28/x)-1;
      b = (24/y)-1;
      c = z;
              
      steps_fb = a * stepsPerRound; //28 (-1)
      steps_rl = b * stepsPerRound; //48 (-1)
      steps_ud = c * stepsPerRound;  //8 (-1)
      steps_w = 1 * stepsPerRound;
    }
}
//--------------------------------------------------------//
void receive_data_loop()
{
  if (Serial.available())
    {
      String dataRX;
      while(Serial.available())
        {
          char g = Serial.read();
          dataRX += g;
          mySerial.println(dataRX);
        }
      s= dataRX.indexOf("c")- dataRX.indexOf("b");
      if (s==2) { z01 =dataRX[dataRX.indexOf("b")+1]-'0';}
      else if (s==3){ chuc =dataRX[dataRX.indexOf("b")+1]-'0'; dv =dataRX[dataRX.indexOf("b")+2]-'0'; z01=chuc*10 +dv;}
      z = z01;
      
      s= dataRX.indexOf("d")- dataRX.indexOf("c");
      if (s==2) { d01 =dataRX[dataRX.indexOf("c")+1]-'0';}
      else if (s==3){ chuc =dataRX[dataRX.indexOf("c")+1]-'0'; dv =dataRX[dataRX.indexOf("c")+2]-'0'; d01=chuc*10 +dv;}
      
      s= dataRX.indexOf("e")- dataRX.indexOf("d");
      if (s==2){ p01 =dataRX[dataRX.indexOf("d")+1]-'0';}
      else if (s==3){ chuc =dataRX[dataRX.indexOf("d")+1]-'0'; dv =dataRX[dataRX.indexOf("d")+2]-'0'; p01=chuc*10 +dv;}
            
      s= dataRX.indexOf("f")- dataRX.indexOf("e");
      if (s==2) { k01 =dataRX[dataRX.indexOf("e")+1]-'0';}
      else if (s==3){ chuc =dataRX[dataRX.indexOf("e")+1]-'0'; dv =dataRX[dataRX.indexOf("e")+2]-'0'; k01=chuc*10 +dv;}
          
      s= dataRX.indexOf("g")- dataRX.indexOf("f");
      if (s==2) { l01 =dataRX[dataRX.indexOf("f")+1]-'0';}
      else if (s==3){ chuc =dataRX[dataRX.indexOf("f")+1]-'0'; dv =dataRX[dataRX.indexOf("f")+2]-'0'; l01=chuc*10 +dv;}

      s= dataRX.indexOf("h")- dataRX.indexOf("g");
      if (s==2) { s01 =dataRX[dataRX.indexOf("g")+1]-'0';}
      else if (s==3){ chuc =dataRX[dataRX.indexOf("f")+1]-'0'; dv =dataRX[dataRX.indexOf("g")+2]-'0'; s01=chuc*10 +dv;}
    }
}
//--------------------------------------------------------//
void control()
{
  time1 = millis();
  while ( (unsigned long) (millis() - time1) < 4000 )
    {
      receive_data_loop();
    }
  if ( p01 == 1) 
    { 
      watertime();
      firstpoint();
    }
  if ( millis()/60000 >= d01)
    { 
      if (k01 == 1)
        { 
          checktime();
          firstpoint();
        }
    }
}
