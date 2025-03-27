// Modificar servo per rotació contínua
// https://www.youtube.com/watch?v=4C8Y3caU4y0

#include <Servo.h>

Servo elmeuservo;   // crea l'objecte servo per a controlar-lo

void setup() {
    // Obre el port sèrie i espera a que connecti
    Serial.begin(9600);
    while (!Serial) {
        delay(10);
    }
    elmeuservo.attach(8);    // associa el servo al GPIO8
    delay(2000);             // esperem que s'auto-inicialitzi
    elmeuservo.write(0);     // posicionem el servo a 0 graus
}

void loop() {
    int angle, caracter, i;
    char valor[4];

    Serial.println("");
    Serial.println("Posició del servo (0-180): ");
    i=0;
    while(true) {
        if (Serial.available() > 0) {
            caracter = Serial.read();
            if (caracter == 10) {    // Return o Enviar
                valor[i] = 0;   // Fi d'string
                break;
            }
            else {
                if (i < 3) {    // màxim 3 dígits
                    valor[i] = caracter;
                    i++;
                }
            }
        }
    }    
    angle = atoi(valor);
    Serial.print("Mogut a l'angle: ");  Serial.println(angle);
    elmeuservo.write(angle);    // mou el servo a la posició entrada
}
