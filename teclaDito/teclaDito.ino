#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27,16,2);

const byte ROWS = 4;  // Number of rows in the keypad (4x4)
const byte COLS = 4;  // Number of columns in the keypad (4x4)

// Define the key layout
char keys[ROWS][COLS] = { 
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Connect keypad rows and columns to Arduino pins
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String password = "5432";
String enteredString = "";  // Variable to store entered keys

bool changingPassword = false;
String bothPasswordNotMatch = "1";
bool pressed = true;

String tempPassword = "";
String newPassword = "";


  int triac2 = 12; // Pin del trigger del sensor
  int eco2 = 13; // Pin del echo del sensor


  int distancia2;
  int duracion2;


  Servo myservo2;
  int pinServo2 = 11;

  int vueltas = 1.2;

  int tiempoPorVuelta = 200; // Tiempo en milisegundos para una vuelta completa, ajusta según tu servo

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();

  Serial.println("Teclado 4x4 con Biblioteca Keypad (Pins 2-9)");
  Serial.println();

  pinMode(triac2, OUTPUT); // Manda la señal
  pinMode(eco2, INPUT); // Recibe señal

  myservo2.attach(pinServo2);

  Serial.begin(9600);

}

void loop() {

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
  if (distancia2 <= 60) {
     lcd.setCursor(0,1);
          lcd.print("Ingrese password");
/*
  Logica del teclado y pantalla
*/

  lcd.display();

  char pressedKey = keypad.getKey();

  if(keypad.getState()  == RELEASED) {
    pressed = false;
  }

  if (pressedKey && pressed) {
    Serial.print("Tecla: ");
    Serial.println(pressedKey);

    if (pressedKey != '#') {
      enteredString += pressedKey;  // Append pressed key to enteredString
    }
    Serial.print("presionados: ");
    Serial.println(enteredString);

    lcd.setCursor(0,0);
    lcd.print(enteredString); 

    if (changingPassword) {
      if (pressedKey == '#' && bothPasswordNotMatch == "1") {
        // Set new password
        tempPassword = enteredString.substring(0, enteredString.length());  //guardamos la temporal
        Serial.print("Escriba nuevamente password");

         lcd.setCursor(0,0);
          lcd.print("Escriba nuevamente ");
          lcd.setCursor (0,1);
           lcd.print("su password");
          delay(5000);

           lcd.clear();

        enteredString = "";
        bothPasswordNotMatch = "2";
      }
      else if (pressedKey == '#' && bothPasswordNotMatch == "2" && tempPassword == enteredString) {
          newPassword = enteredString.substring(0, enteredString.length());
          password = newPassword;
          Serial.print("Nueva password establecida: ");
          Serial.println(password);

           lcd.setCursor(0,0);
          lcd.print("password ok:");
            lcd.setCursor (0,1);
           lcd.print(password);

            delay(5000);

           lcd.clear();


          changingPassword = false;
          bothPasswordNotMatch = 3;
          enteredString = "";
      } else if( bothPasswordNotMatch == "3") {
        Serial.print("El password no coincide... saliendo");
         lcd.setCursor(0,0);
          lcd.print("El password no coincide");
            lcd.setCursor (0,1);
           lcd.print("... saliendo");

            delay(5000);

           lcd.clear();

        changingPassword = false;
        enteredString = "";
      }
    } else {
      if (pressedKey == '#') {

      if (enteredString == "7777") {
        // Start password change process
        Serial.println("Cambiar password.");
        changingPassword = true;
        enteredString = "";
        Serial.print("Escriba la nueva password");

         lcd.setCursor(0,0);
          lcd.print("Cambiar password");
            lcd.setCursor (0,1);
           lcd.print("Escriba la nueva password");

            delay(5000);

           lcd.clear();

       
      }
        // Validate entered password by comparing the last four digits
      else if (enteredString.length() >= 4 && enteredString.substring(enteredString.length() - 4) == password) {
          Serial.println("Validar password");
          Serial.println("Password Correcta. Abriendo...");

      myservo2.write(180); // Ajusta el valor si es necesario para tu servo
      delay(vueltas * tiempoPorVuelta);
      myservo2.write(90);

           lcd.setCursor(0,0);
          lcd.print("Password OK.");
            lcd.setCursor (0,1);
           lcd.print("Abriendo...");
          enteredString = "";                // Clear the entered string
           delay(5000);

           lcd.clear();

               myservo2.write(0); // Ajusta el valor si es necesario para tu servo
      delay(vueltas * tiempoPorVuelta);
      myservo2.write(90);
        
        } else {
          Serial.println("Password Incorrecta");
          lcd.setCursor(0,0);
          lcd.print("Incorrecta");
          enteredString = "";                // Clear the entered string

           delay(5000);

           lcd.clear();
        }
      } 
    }
  }
  pressed = true;
  delay(35);
  } else {
      delay(35);
      enteredString = "";
      lcd.clear();
  }
}
