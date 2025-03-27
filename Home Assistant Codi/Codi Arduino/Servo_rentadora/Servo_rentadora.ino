// Modificar servo per rotació contínua
// https://www.youtube.com/watch?v=4C8Y3caU4y0

#include <Servo.h>

#define BOTO  0     // Polsador entre GND (pin 8) i GPIO0 (pin 6)
#define LLUM  2     // Led blau entre Vcc +3,3V (pin 1) i GPIO2 (pin 7) amb resistència de 470 Ohms
#define SERVO 3     // Servo alimentat entre GND (pin 8) i +5V (pin 3 modificat). Control per GPIO3 (pin 5)

#define ATURA     88
#define DRETA     150
#define ESQUERRA  0

#define TEMPS_RENTAT   120000    // Definim un cicle de rentat de 2 minuts = 120.000 ms
#define CANVI_GIR      10000     // Cada 10 seg canviarem el sentit de gir

Servo elmeuservo;   // crea l'objecte servo per a controlar-lo
int rentadora = false;
unsigned long temps_inici = 0;
unsigned long temps_gir = 0;
int premut_stop = false;
int sentit_gir = true;

void setup() {
    pinMode(BOTO, INPUT);           // inicialitzem el pin digital com a entrada (INPUT)
    pinMode(LLUM, OUTPUT);          // inicialitzem el pin digital com a sortida (OUTPUT)
    digitalWrite(LLUM, HIGH);       //   i el posem en estat apagat

    elmeuservo.attach(SERVO);   // associa el servo al GPIO
    delay(2000);                // esperem que s'auto-inicialitzi
    elmeuservo.write(ATURA);        // col·loquem el servo aturat
}

void loop() {
    if (digitalRead(BOTO) == LOW) {
        if (rentadora == true) premut_stop = true;
        if (rentadora == false) {
            temps_inici = millis();
            temps_gir = 0;
            digitalWrite(LLUM, LOW);
            rentadora = true;
        }
        delay(1000);    // retard per evitar rebots del polsador
    }
    if (rentadora == true) {
        if ((millis() - temps_gir) > CANVI_GIR) {
            if (sentit_gir == true) elmeuservo.write(DRETA);
            else elmeuservo.write(ESQUERRA);
            temps_gir = millis();
            sentit_gir = !sentit_gir;
        }
        if (((millis() - temps_inici) > TEMPS_RENTAT) || (premut_stop == true)) {
            elmeuservo.write(ATURA);
            digitalWrite(LLUM, HIGH);
            rentadora = false;
            premut_stop = false;
        }
    }
}
