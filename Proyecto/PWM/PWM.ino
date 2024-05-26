led = 9;
sw = 2;
pot = A0;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(sw, INPUT);
  pinMode(pot, INPUT);

}

void loop() {
  while (digitalRead(sw) == 1){
    for (int i = 0; i < 255; i++)
    {
      analogWrite(led, i);
      delay(30);
    }
    for (int i = 255; i > 0 ; i--)
    {
      analogWrite(led, i);
      delay(30);
    }
  }

  while (digitalRead(sw) == 0){
    analogWrite(led, analogRead(pot));
  }
}
