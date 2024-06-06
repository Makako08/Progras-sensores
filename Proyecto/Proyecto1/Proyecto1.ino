// Incluimos la biblioteca para controlar el servomotor
#include <Servo.h>

// Definimos los pines para los sensores ultrasónicos
const int trig1 = 2;
const int echo1 = 3;
int trig2 = 4;
int echo2 = 5;

// Variables para almacenar el tiempo y la distancia medidas por los sensores
int tiempo1;
int distancia1;
float tiempo2;
float distancia2;

// Definimos los pines para los LEDs
int ledRojo = 7;
int ledVerde = 8;
// Definimos el pin para el servomotor
int servoPin = 9;

// Creamos una instancia del servomotor
Servo servo;

// Definimos las posiciones del servomotor
int servoPosInicial = 0;
int servoPosAbierta = 90;
int servoPosIntermedia = 45;

// Definimos los estados del sistema
enum Estado {
  INICIAL, 
  DETECTANDO_OBJETO1, 
  CERRANDO
};

// Inicializamos el estado actual del sistema
Estado estadoActual = INICIAL;

void setup() {
  // Configuramos la velocidad de comunicación serie
  Serial.begin(9600);
  
  // Configuramos los pines de los sensores ultrasónicos
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  digitalWrite(echo1, LOW);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);

  // Configuramos los pines de los LEDs
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRojo, OUTPUT);

  // Adjuntamos el servomotor al pin correspondiente y lo posicionamos en la posición inicial
  servo.attach(servoPin);
  servo.write(servoPosInicial);

  // Encendemos el LED rojo y apagamos el LED verde
  digitalWrite(ledRojo, HIGH);
  digitalWrite(ledVerde, LOW);

  // Mensaje de estado inicial
  Serial.println("Estado: Reposo - LED Rojo encendido, LED Verde apagado, Servo en posición inicial");
}

void loop() {
  // Medición de distancia con el primer sensor ultrasónico
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  tiempo1 = pulseIn(echo1, HIGH);
  distancia1 = tiempo1 / 59;

  // Imprimimos la distancia medida por el primer sensor
  Serial.print("Distancia: ");
  Serial.print(distancia1);
  Serial.print(" cm");
  delay(100);

  // Medición de distancia con el segundo sensor ultrasónico
  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  tiempo2 = pulseIn(echo2, HIGH);
  distancia2 = tiempo2 / 59;

  // Imprimimos la distancia medida por el segundo sensor
  Serial.print("     ");
  Serial.print("Distancia2: ");
  Serial.print(distancia2);
  Serial.println(" cm");
  delay(100);

  unsigned long tiempoInicio = 0;

  // Máquina de estados
  switch (estadoActual) {
    case INICIAL:
      // Estado inicial
      digitalWrite(ledRojo, HIGH);
      digitalWrite(ledVerde, LOW);
      if (distancia1 < 5) { // Si se detecta un objeto cerca del primer sensor
        servo.write(servoPosAbierta);
        digitalWrite(ledRojo, LOW);
        digitalWrite(ledVerde, HIGH);
        Serial.println("Estado: Abierto - LED Verde encendido, LED Rojo apagado, Servo abierto");
        estadoActual = DETECTANDO_OBJETO1;
        tiempoInicio = millis(); // Registramos el tiempo de inicio
      }
      break;

    case DETECTANDO_OBJETO1:
      // Estado de detección del segundo objeto
      if (distancia2 < 5 && distancia1 > 5) { // Si se detecta un objeto cerca del segundo sensor y no cerca del primero
        Serial.println("Estado: Cerrando - LED Verde apagado, LED Rojo encendido, Cerrando servo");
        estadoActual = CERRANDO;
        tiempoInicio = 0;
      }
      break;

    case CERRANDO:
      // Estado de cierre del servomotor
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledRojo, HIGH);

      // Movemos el servomotor de 90 a 45 grados rápidamente
      servo.write(45);

      // Movemos el servomotor de 45 a 0 grados lentamente
      for (int pos = servoPosIntermedia; pos >= servoPosInicial; pos--) {
        servo.write(pos);
        delay(30); // Ajuste de velocidad
      }

      // Posicionamos el servomotor en la posición inicial
      servo.write(servoPosInicial);
      Serial.println("Estado: Reposo - LED Rojo encendido, LED Verde apagado, Servo en posición inicial");
      estadoActual = INICIAL; 
      break;
  }

  delay(100);
}
