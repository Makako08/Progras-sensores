//10.5k
//Rc 4.5k

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


const int sensorPin = A0;
const int Rc = 4570;  // valor de la resistencia de calibración

float V;          // almacena el valor medido
float Rsensor;      // almacena la resistencia calculada
float res;
float uy;

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {
  display.clearDisplay();
  V = analogRead(sensorPin);    //realizar la lectura
  Rsensor = 1024L * Rc / V - Rc;   //calcular el valor de la resistencia
  uy = (Rc*pow(1024L, 2)/(5*pow(V, 2)))*0.025;

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print(Rsensor);
  display.print(" ");
  display.println((char)0xE9);
  display.println("");
  display.print("(");
  display.print((char)240);
  display.print(uy);
  display.print((char)0xE9);
  display.println(")");
  display.display();
}
