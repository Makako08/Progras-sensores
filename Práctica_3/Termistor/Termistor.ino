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



const int Rc = 4570;  // valor de la resistencia de calibración

float V;   // almacena el valor medido
float Rt;  // almacena la resistencia calculada
float T;
float Treal;
float A;
float B = 3892.36L;
float V1;


void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {
  display.clearDisplay();
  V = analogRead(A0);  //realizar la lectura
  V1 = ((float)V * (5.0 / 1023.0));
  Rt = ((4700L * V1) / (5 - V1));  //calcular el valor de la resistencia

  A = log(Rt / 5100L);
  T = B / (A + (B / 298));
  Treal = T - 273.15;



  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print(Treal);
  display.print(" ");
  display.print((char)0xA7);
  display.println("C");
  display.display();
  Serial.println(V1);
  
}
