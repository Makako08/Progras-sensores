#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
display.clearDisplay();

}

void loop() {
 display.setTextSize(1);
 display.setTextColor(WHITE);
 display.setCursor(0,0);
 display.println("Hola Hola hola hola");      // here the message is inside the "" 
 display.display();
 delay(1000);

}
