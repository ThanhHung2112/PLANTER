#include "esp_camera.h"
#include <WiFi.h>
#include <FirebaseESP32.h>
#include "DHT.h"
// WARNING!!! PSRAM IC required for UXGA resolution and high JPEG quality
//            Ensure ESP32 Wrover Module or other board with PSRAM is selected
//            Partial images will be transmitted if image exceeds buffer size
//
// Select camera model
//#define CAMERA_MODEL_WROVER_KIT // Has PSRAM
//#define CAMERA_MODEL_ESP_EYE // Has PSRAM
//#define CAMERA_MODEL_M5STACK_PSRAM // Has PSRAM
//#define CAMERA_MODEL_M5STACK_V2_PSRAM // M5Camera version B Has PSRAM
//#define CAMERA_MODEL_M5STACK_WIDE // Has PSRAM
//#define CAMERA_MODEL_M5STACK_ESP32CAM // No PSRAM
#define CAMERA_MODEL_AI_THINKER // Has PSRAM
//#define CAMERA_MODEL_TTGO_T_JOURNAL // No PSRAM
#include "camera_pins.h"

#define FIREBASE_HOST "new1-b591a-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "1SToaOUtt1dJTTbW0R0sBD4KWOmQaNH8ZasdBAPk"

//here we use pin IO14 of ESP32 to read data
#define DHTPIN 14
//our sensor is DHT11 type
#define DHTTYPE DHT11
//sensor soil
int sensorPin = 15; 
int sensorValue; 
int percentSoil = 33;
int read_pS, average_pS;

FirebaseData fbdt;
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "stc";
const char* password = "suthanhcon";

void startCameraServer();

void setup() 
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  // if PSRAM IC present, init with UXGA resolution and higher JPEG quality
  //                      for larger pre-allocated frame buffer.
  if(psramFound())
    {
      config.frame_size = FRAMESIZE_UXGA;
      config.jpeg_quality = 10;
      config.fb_count = 2;
    } 
  else 
    {
      config.frame_size = FRAMESIZE_SVGA;
      config.jpeg_quality = 12;
      config.fb_count = 1;
    }
#if defined(CAMERA_MODEL_ESP_EYE)
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
#endif
  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) 
    {
      Serial.printf("Camera init failed with error 0x%x", err);
      return;
    }
  sensor_t * s = esp_camera_sensor_get();
  // initial sensors are flipped vertically and colors are a bit saturated
  if (s->id.PID == OV3660_PID) 
    {
      s->set_vflip(s, 1); // flip it back
      s->set_brightness(s, 1); // up the brightness just a bit
      s->set_saturation(s, -2); // lower the saturation
    }
  // drop down frame size for higher initial frame rate
  s->set_framesize(s, FRAMESIZE_QVGA);
#if defined(CAMERA_MODEL_M5STACK_WIDE) || defined(CAMERA_MODEL_M5STACK_ESP32CAM)
  s->set_vflip(s, 1);
  s->set_hmirror(s, 1);
#endif

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
  Serial.println("");
  Serial.println("WiFi connected");

  startCameraServer();

  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setString(fbdt,"IP", WiFi.localIP().toString());
  
  Serial.println(F("DHT11 test!"));
  dht.begin();
}

void loop()
{
  sensorValue = digitalRead(sensorPin); 
  Serial.print("Sensor Value : ");
  Serial.println(sensorValue);
  Dht11();
  soilMoisture();
  delay(500);
}
//----------------------------------------------------------------//
void Dht11()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) 
    {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");
  Firebase.setFloat(fbdt,"sensor/temp",t);
  Firebase.setFloat(fbdt,"sensor/humi",h);
}
//----------------------------------------------------------------//
void soilMoisture()
{
 // Soil moisture
 if(sensorValue == 1)
    {
//      Firebase.setInt(fbdt,"pump",0);
      Serial.println("Dry");
    }
 if(sensorValue == 0)
    {
//      Firebase.setInt(fbdt,"pump",1);
      Serial.println("Moist");
    }
  for(int i=0;i<=9;i++)
    {
      read_pS += analogRead(percentSoil);     
    }
  average_pS = read_pS/10;
  int percentV = map(average_pS, 0, 4095, 0, 100);
  int percentR = 100 - percentV;
  delay (500);
  read_pS=0;
  Firebase.setInt(fbdt,"sensor/soil",percentR); 
  Firebase.setInt(fbdt,"sensor/soil_state",sensorValue);
}
