#define BOTO    0     // Polsador entre GND (pin 8) i GPIO0 (pin 6)
#define LLUM    2     // Led blau entre Vcc +3,3V (pin 1) i GPIO2 (pin 7) amb resistència de 470 Ohms
#define MOTOR1  3     // Motor controlat amb L272M que té dos operacionals, per alimentar-lo amb +5V i -5V per canviar el sentit de gir
#define MOTOR2  1     // Alimentat entre GND (pin 8) i +5V (pin 3 modificat). Control per GPIO3 (pin 5)i GPIO1 (pin 4)

#define TEMPS_RENTAT   60000    // Definim un cicle de rentat de 1 minuts = 60.000 ms
#define CANVI_GIR      5000     // Cada 5 seg canviarem el sentit de gir
#define PAUSA_GIR      1000     // A cada canvi de gir farem una pausa de 1 seg

int rentadora = false;
unsigned long temps_inici = 0;
unsigned long temps_gir = 0;
int premut_stop = false;
int sentit_gir = true;

void setup() {
    pinMode(BOTO, INPUT);    // inicialitzem el pin digital com a entrada (INPUT)
    pinMode(LLUM, OUTPUT);     digitalWrite(LLUM, HIGH);    // inicialitzem el pin digital com a sortida (OUTPUT) i el posem en estat apagat
    pinMode(MOTOR1, OUTPUT);   digitalWrite(MOTOR1, LOW);
    pinMode(MOTOR2, OUTPUT);   digitalWrite(MOTOR2, LOW);   // igual pel motor, el posem en aturat
    delay(500);
}

void loop() {
    if (digitalRead(BOTO) == LOW) {
        if (rentadora == true) premut_stop = true;
        if (rentadora == false) {
            digitalWrite(LLUM, LOW);    delay(300);
            digitalWrite(LLUM, HIGH);   delay(300);
            digitalWrite(LLUM, LOW);    delay(300);
            digitalWrite(LLUM, HIGH);   delay(300);
            digitalWrite(LLUM, LOW);
            rentadora = true;
            temps_inici = millis();
            temps_gir = 0;
        }
        delay(500);    // retard per evitar rebots del polsador
    }
    if (rentadora == true) {
        if ((millis() - temps_gir) > CANVI_GIR) {
            if (sentit_gir == true) {
                digitalWrite(MOTOR2, LOW);
                delay(PAUSA_GIR);
                digitalWrite(MOTOR1, HIGH);
                digitalWrite(MOTOR2, LOW);
            }
            else {
                digitalWrite(MOTOR1, LOW);
                delay(PAUSA_GIR);
                digitalWrite(MOTOR1, LOW);
                digitalWrite(MOTOR2, HIGH);
            }
            temps_gir = millis();
            sentit_gir = !sentit_gir;
        }
        if (((millis() - temps_inici) > TEMPS_RENTAT) || (premut_stop == true)) {
            digitalWrite(MOTOR1, LOW);
            digitalWrite(MOTOR2, LOW);
            digitalWrite(LLUM, HIGH);   delay(300);
            digitalWrite(LLUM, LOW);    delay(300);
            digitalWrite(LLUM, HIGH);   delay(300);
            digitalWrite(LLUM, LOW);    delay(300);
            digitalWrite(LLUM, HIGH);
            rentadora = false;
            premut_stop = false;
        }
    }
}
