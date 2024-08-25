// Powered By Arduino classroom Youtube Channel
// oRIGINAL https://github.com/filmcup/Esp32_youtube_counter_with_oled/blob/main/Youtube_counter/YoutubeApi.cpp
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <YoutubeApi.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 16

#define SCREEN_WIDTH 128 // OLED width,  in pixels
#define SCREEN_HEIGHT 64 // OLED height, in pixels


//Adafruit_SSD1306 display(OLED_RESET);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const char ssid[] = "OOZTEST";
const char password[] = "diegodiego"; 

#define API_KEY "QUI VA MESSA L'API KEY DI YOUTUBE" 
#define CHANNEL_ID "UCm3gzmmPBf8AwbEvsANWBBg"

WiFiClientSecure client;
YoutubeApi api(API_KEY, client);

unsigned long timeBetweenRequests = 60 * 1000;  // 60 seconds, in milliseconds

void setup() {
  Serial.begin(115200);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); //สั่งให้จอ OLED เริ่มทำงานที่ Address 0x3C
  display.clearDisplay(); // ลบภาพในหน้าจอทั้งหมด
  display.setTextSize(1); // กำหนดขนาดตัวอักษร
  display.setTextColor(WHITE);
  display.setCursor(0,0); // กำหนดตำแหน่ง x,y ที่จะแสดงผล
  display.println(" FOLLOWER COUNTER ");
  display.setCursor(0,20);
  display.setTextSize(2);
  display.setTextColor(BLACK, WHITE); //กำหนดข้อความสีขาว ฉากหลังสีดำ
  display.println(" DIEGOOZ ");
  display.setCursor(0,9);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("UN PROGETTO CON ESP32");
  display.setCursor(0,48);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("YOUTUBE @PIXELSSQUAD"); // แสดงผลข้อความ www.Myarduino.net
  display.display();

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.print("\nConnecting to WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWiFi connected!");
  Serial.print("IP address: ");
  display.print("ISCRITTI: ");
  display.println(api.channelStats.subscriberCount);
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  client.setInsecure();
}

void loop() {
  if (api.getChannelStatistics(CHANNEL_ID)) {
    Serial.println("\n-------Stats---------");

    Serial.print("Subscriber Count: ");
    Serial.println(api.channelStats.subscriberCount);

    Serial.print("View Count: ");
    Serial.println(api.channelStats.viewCount);

    Serial.print("Video Count: ");
    Serial.println(api.channelStats.videoCount);

    Serial.println("------------------------");

    display.clearDisplay(); // ลบภาพในหน้าจอทั้งหมด
    display.setTextSize(1); // กำหนดขนาดตัวอักษร
    display.setTextColor(WHITE);
    display.setCursor(0,0); // กำหนดตำแหน่ง x,y ที่จะแสดงผล
    
    display.println("\n DIEGOOZ YT CHANNEL");
   display.println("-=-=-=-=-=-=-=-=-=-=-");
    display.print("ISCRITTI: ");
    display.println(api.channelStats.subscriberCount);

    display.print("Views: ");
    display.println(api.channelStats.viewCount);

    display.print("Video: ");
    display.println(api.channelStats.videoCount);

    display.println("---------------------");
    display.println("ISCRIVITI AL CANALE");
    display.display();
  }
  delay(timeBetweenRequests);
}
