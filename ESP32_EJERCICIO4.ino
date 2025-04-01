//MILSZTAIN_MACIA_SABIN_RUBINSTEIN
//LIBRERIAS
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

//VARIABLES
#define LED 25   //LED INTEGRADO
float umbral = 28; //Temperatura de umbral
int pantalla = 2;    //1 = temp actual y valor umbral / 2 = solo umbral (modificado)
int cambiar = 0;

//BOTONES
#define SWAU 34 //switch de aumentar
int valau;
int bloqau = 0 ;

#define SWRE 35 //switch de reducir
int valre;
int bloqre = 0;

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
  Serial.println("iniciado");

  pinMode(LED, OUTPUT);
  pinMode(SWAU, INPUT);
  pinMode(SWRE, INPUT);

  dht.begin(); //inicializa en sensor de temperatura
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //inicializa el display
}

void loop() 
{
  //Se lee la temperatura (en celcious)
  float temp = dht.readTemperature();
  
  //DISPLAY
  if (pantalla == 1) //temp y umbral
  {
    display.clearDisplay();
    display.setTextSize(2); //Establece el tamaño de texto
    
    display.setCursor(0, 10);
    display.setTextColor(WHITE);
    display.println(temp); //display de temperatura

    display.setCursor(0,40);
    display.setTextColor(WHITE);
    display.println(umbral);

    display.display(); //Muestra el display
  }

  if (pantalla == 2)
  {
    display.clearDisplay();
    display.setTextSize(2); //Establece el tamaño de texto

    display.setCursor(0,10);
    display.setTextColor(WHITE);
    display.println(umbral);

    display.display(); //Muestra el display
  }
  
  //BOTONES
  valau = digitalRead(SWAU);
  valre = digitalRead(SWRE);

  //MODIFICAR UMBRAL
  if (valau == 0 && bloqau == 0 && pantalla == 2)
  {
    umbral = umbral + 1; //aumentar umbral
  }

  if (valre == 0 && bloqre == 0 && pantalla == 2)
  {
    umbral = umbral - 1; //reducir umbral
  }
  
  //CAMBIAR PANTALLA
  if (valau == 0 && valre == 0 && pantalla == 1 && cambiar == 0) //cambiar panatalla
  {
    Serial.println("pantalla 2");
    cambiar = 1;
    pantalla = 2;
  } 

  if (valau == 0 && valre == 0 && pantalla == 2 && cambiar == 0)
  {
    Serial.println("pantalla 1");
    cambiar = 1;
    pantalla = 1;
  } 

  //EVITAR QUE LOS BOTONES SE MANTENGAN EN FUNCIONAMIENTO
  if (valau == 0)
  {
    bloqau = 1;
  }
  if (valau == 1)
  {
    bloqau = 0;
  }

  if (valre == 0)
  {
    bloqre = 1;
  }
  if (valre == 1)
  {
    bloqre = 0;
  }

  //Anti cambio de pantalla
  if (valau == 1 && valre == 1)
  {
    cambiar = 0;
  }

  //PRENDER LED
  if (temp < umbral)
    {
      digitalWrite(LED, LOW);
    }

  if (temp >= umbral)
  {
    digitalWrite(LED, HIGH);
  }
}
