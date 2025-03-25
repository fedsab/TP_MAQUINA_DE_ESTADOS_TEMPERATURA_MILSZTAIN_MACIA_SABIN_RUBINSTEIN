//LIBRERIAS
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Dimensiones de la pantalla
#define LONGITUD 128 // longitud
#define ALTURA 64 // altura

Adafruit_SSD1306 display(LONGITUD, ALTURA, &Wire, -1);

void setup() 
{
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //inicializa el display

  delay(1000);
  display.clearDisplay(); //Vacía el display
  display.setTextSize(1); //Establece el tamaño de texto
  display.setCursor(0, 10);

  
  display.println("Hello world!");
  display.display(); //Muestra el texto
}

void loop() 
{
  
}