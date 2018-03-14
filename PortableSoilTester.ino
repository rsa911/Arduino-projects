#include <dht.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

dht DHT;
#define DHT11_PIN 13

int analogPin = A0;
int moisture;
int percentage;
int map_low = 1023;
int map_high = 200;



void setup()
{
  Serial.begin(9600);
  display.begin(0x3C);  
  display.clearDisplay();
  }

void loop()
{
 display.clearDisplay();
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Temperature:");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(75,0);
  display.println(DHT.temperature);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(110,0);
  display.println("*C");
  
 
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("Humidity   :");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(75,10);
  display.println(DHT.humidity);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(110,10);
  display.println("%");
  
  
  moisture = analogRead(analogPin);
  percentage = map(moisture, map_low, map_high, 0, 100);

  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,20);
  display.println("Soil Moisture:");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(90,20);
  display.println(percentage);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(110,20);
  display.println("%");
 
 display.display();

  DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  Serial.print("Soil Moisture: ");
  Serial.print(percentage);
  Serial.println("%");
  
  delay(1000);
}

