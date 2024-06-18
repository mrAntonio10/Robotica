#include <Servo.h>

/*
  Variables de sensores ultrasonidos 1 y 2
*/
  int triac = 4; // Pin del trigger del sensor
  int eco = 5; // Pin del echo del sensor

  int triac2 = 12; // Pin del trigger del sensor
  int eco2 = 13; // Pin del echo del sensor


  int distancia;
  int duracion;

  int distancia2;
  int duracion2;


/*
  Variables que controlan el Servomotor 1y 2
*/
  Servo myservo;
  int pinServo = 9;

  Servo myservo2;
  int pinServo2 = 8;

  int vueltas = 6;
  int vueltasBack = 1;

  int tiempoPorVuelta = 700; // Tiempo en milisegundos para una vuelta completa, ajusta según tu servo

/*
  Boleano, control de detectado anteriormente
*/
bool isUp = false;

void setup() {
/*
  PINES Sensor 1 y 2
*/
  pinMode(triac, OUTPUT); // Manda la señal
  pinMode(eco, INPUT); // Recibe señal

  pinMode(triac2, OUTPUT); // Manda la señal
  pinMode(eco2, INPUT); // Recibe señal


/*
  Inicio de servomotor
*/
  myservo.attach(pinServo);

  myservo2.attach(pinServo2);

  Serial.begin(9600); //bits*segundos


}

void loop() {
/*
    Sensor ultrasonido 1. Imprimir distancia en cm. Si detecta a 40cm activa el servomotor
*/
  digitalWrite(triac, HIGH); // Prende
  delay(10); // Espera 10 microsegundos para estabilizar el pulso
  digitalWrite(triac, LOW); // Apaga

  duracion = pulseIn(eco, HIGH);

  // Calcula la distancia en centímetros
  distancia = (duracion / 2) / 29.1;

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  if (distancia <= 20) {
    if(!isUp) {
        Serial.print("No esta arriba y debe levantar: ");
      myservo.write(180); // Ajusta el valor si es necesario para tu servo
      delay(vueltas * tiempoPorVuelta);
      myservo.write(90);

      myservo2.write(0); // Ajusta el valor si es necesario para tu servo
      delay(vueltas * tiempoPorVuelta);
      myservo2.write(92);

      isUp = true;
    }
    
  } else {
    if(isUp) {
      Serial.print("No hay nada, esperamos y bajamos: ");
      delay(4000);

      myservo.write(0); // Ajusta el valor si es necesario para tu servo
      delay(vueltasBack * tiempoPorVuelta);
      myservo.write(90);

      myservo2.write(180); // Ajusta el valor si es necesario para tu servo
      delay(vueltasBack * tiempoPorVuelta);
      myservo2.write(92);

      isUp = false;
      // Detiene el servo
    }
  }


/*
    Sensor ultrasonido 2. Imprimir distancia en cm. Si detecta a 40cm activa el servomotor
*/
  digitalWrite(triac2, HIGH); // Prende
  delay(10); // Espera 10 microsegundos para estabilizar el pulso
  digitalWrite(triac2, LOW); // Apaga

  duracion2 = pulseIn(eco2, HIGH);

  // Calcula la distancia en centímetros
  distancia2 = (duracion2 / 2) / 29.1;

  // Imprime la distancia en el monitor serial para depuración
  Serial.print("Distancia2: ");
  Serial.print(distancia2);
  Serial.println(" cm");

  // Control del motor basado en la distancia medida
  if (distancia2 <= 40) {
   
  
  } else {
    
  }

  // Pequeño retraso para evitar el spam en el monitor serial
  delay(100);
}
