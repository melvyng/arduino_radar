//Prueba de codigo remoto inicio
#define BLYNK_PRINT Serial
#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>

char auth[] = "jS8YjyVdKQTiKTig2oUbag786qBm5Ecs";

BlynkTimer timer;

//Prueba de codigo remoto fin

// Include para la libreria Servo
#include <Servo.h>
// Define el pin Trig y Echo de el Sensor Ultrasonico
const int servoPin = 9;
const int trigPin = 8;
const int echoPin = 7;
const int speaker = 4;

// Variables para la duracion y la distancia
long duracion;
int distancia;

Servo myServo; // Crea un objeto servo para controlar el servo motor

void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V3, millis() / 1000);
}


void myAlert()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V1, 1);
}

void setup() {
  pinMode(trigPin, OUTPUT); // Configurar el trigPin como Output
  pinMode(echoPin, INPUT); // Configurar el echoPin como Input
  pinMode(speaker, OUTPUT);
  Serial.begin(9600);
  myServo.attach(servoPin); // Define en que pin esta el servo motor conectado

  //Prueba de codigo remoto inicio
  Blynk.begin(auth);
  timer.setInterval(1000L, myTimerEvent);
  timer.setInterval(1L, myAlert);
  //Prueba de codigo remoto fin
}
void loop() {
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
  //char dato=Serial.read();
  //if(dato == '1'){

  // rota el servo motor de 0 a 180 grados
  for (int i = 0; i <= 180; i++) {
    myServo.write(i);
    delay(30);
    distancia = calcularDistancia();// Llama a una funcion para calcular la distancia medida por el sensor Ultrasonico para cada grado

    //Serial.print("Grado: ");
    Serial.print(i); // Envia el grado actual al Puerto Serial
    Serial.print(","); // Envía un carácter de adición justo al lado del valor anterior que se necesita más adelante en el Processing IDE para la indexación
    //Serial.print("Distancia: ");
    Serial.print(distancia); // Envía el valor de la distancia al puerto serie
    Serial.print("."); // Envía un carácter de adición justo al lado del valor anterior que se necesita más adelante en el Processing IDE para la indexación
  }

  // Repite las líneas anteriores de 180 a 0 grados
  for (int i = 180; i > 0; i--) {
    myServo.write(i);
    delay(30);
    distancia = calcularDistancia();
    //Serial.print("Grado: ");
    Serial.print(i);
    Serial.print(",");
    //Serial.print("Distancia: ");
    Serial.print(distancia);
    Serial.print(".");
  }
  //}else if(dato == '0'){
  //myServo.write(90);
  //delay(3000);
  //analogWrite(speaker, 0);
  //}
  
}
// Funcion para calcular la distancia medida por el sensor Ultrasonic
int calcularDistancia() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Set el trigPin en estado HIGH por 10 microsegundos
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duracion = pulseIn(echoPin, HIGH); // Lee el echoPin, devuelve el tiempo de viaje de la onda de sonido en microsegundos
  distancia = duracion * 0.034 / 2;
  if (distancia < 7) {
    analogWrite(speaker, 1023);
  } else if (distancia >= 7 && distancia < 14) {
    analogWrite(speaker, 639);
  } else if (distancia >= 14 && distancia < 21) {
    analogWrite(speaker, 200);
  } else if (distancia >= 21 && distancia < 40) {
    analogWrite(speaker, 50);
  } else if (distancia >= 100) {
    analogWrite(speaker, 0);
  }
  return distancia;
}
