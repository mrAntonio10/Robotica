int pulsador = 2; 
int estadoAnterior = LOW; 
int estadoActual; 

int pulsador2 = 3; 
int estadoAnterior2 = LOW; 
int estadoActual2; 

//Motor1
int entrada1 = 4;
int entrada2 = 5;

//Motor1
int entrada3 = 6;
int entrada4 = 7;

int vueltas = 1.4;
int tiempoPorVuelta = 550; 

void setup() {
  pinMode(pulsador, INPUT_PULLUP);

  pinMode(pulsador2, INPUT_PULLUP);

  Serial.begin(9600);

  //Puente H
  pinMode(entrada1, OUTPUT);
  pinMode(entrada2, OUTPUT);

    pinMode(entrada3, OUTPUT);
  pinMode(entrada4, OUTPUT);
}

void loop() {
  estadoActual = digitalRead(pulsador); 

  if (estadoAnterior == HIGH) {
      digitalWrite(entrada1, LOW);
      digitalWrite(entrada2, LOW);
     
  } else if(estadoActual == LOW) {
    Serial.print("ejecutado ...");
    digitalWrite(entrada1, HIGH);
    digitalWrite(entrada2, LOW);

  }

  estadoAnterior = estadoActual; 
  //------------------------------------

   estadoActual2 = digitalRead(pulsador2);

     if (estadoAnterior2 == HIGH) {
      digitalWrite(entrada3, LOW);
      digitalWrite(entrada4, LOW);
  } else if(estadoActual2 == LOW) {
    Serial.print("ejecutado2 ...");
      digitalWrite(entrada3, HIGH);
      digitalWrite(entrada4, LOW);
  }

  estadoAnterior2 = estadoActual2; 
}
