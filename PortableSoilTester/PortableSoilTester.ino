#include <DHT.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 13
#define DHTPIN 2

Adafruit_SSD1306 display(OLED_RESET);

#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);


int analogPin = A0;
int moisture;
int percentage;
int map_low = 1023;
int map_high = 475;

void setup()
{
  Serial.begin(9600);
  display.begin(0x3C);  
  display.clearDisplay();
  dht.begin();
}

void loop() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float df = t*(9.0/5.0)+32;
  if (isnan(h) || isnan(t)) { h=0; df=0; }
//  float h2 = dht2.readHumidity();
//  float t2 = dht2.readTemperature();
//  float df2 = t2*(9.0/5.0)+32;
//  if (isnan(h2) || isnan(t2)) { h2=0; df2=0; }
  Serial.print(h);  Serial.print("\t");
  Serial.print(df);  Serial.print("\t");
//  Serial.print(h2);  Serial.print("\t");
//  Serial.println(df2);
  delay(5000);


  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
//  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
//  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
//  float f = dht.readTemperature(true);
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Temperature:");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(75,0);
  display.println(df);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(110,0);
  display.println("*F");

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("Humidity   :");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(75,10);
  display.println(h);
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


  Serial.print("Temperature = ");
  Serial.println(t);
  Serial.print("Humidity = ");
  Serial.println(h);
  Serial.print("Soil Moisture: ");
  Serial.print(percentage);
  Serial.println("%");

  delay(1000);
}

