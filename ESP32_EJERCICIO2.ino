//MILSZTAIN_MACIA_SABIN_RUBINSTEIN
//LIBRERIAS
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

//Dimensiones de la pantalla
#define LONGITUD 128 // longitud
#define ALTURA 64 // altura
Adafruit_SSD1306 display(LONGITUD, ALTURA, &Wire, -1);

//Pin sensor temp
#define DHTPIN 23
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() 
{
  Serial.begin(9600);

  dht.begin(); //inicializa en sensor de temperatura

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //inicializa el display
}

void loop() 
{
  //Se lee la temperatura (en celcious)
  float temp = dht.readTemperature();
  
  display.clearDisplay();
  display.setCursor(0, 10);
  display.setTextSize(2); //Establece el tamaño de texto
  display.setTextColor(WHITE);
  display.println(temp); //display de temperatura
  display.display(); //Muestra la temperatura
  
  Serial.println(temp);
  delay(2000);
}
