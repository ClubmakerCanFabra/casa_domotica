/*
 * PIR sensor tester
 */

int ledPin = 2;    // GPIO2 == pin D4      // choose the pin for the LED
int inputPin = 4;  // GPIO4 == pin D2      // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status

void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input

  Serial.begin(9600);
}

void loop(){
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, LOW);  // turn LED ON
    if (pirState == LOW) {     // we have just turned on
      Serial.println("Motion detected!");   // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, HIGH); // turn LED OFF
    if (pirState == HIGH){   // we have just turned off
      Serial.println("Motion ended!");   // We only want to print on the output change, not state
      pirState = LOW;
    }
  }

  /*digitalWrite(ledPin, HIGH);  // turn LED ON
  delay(500);
  digitalWrite(ledPin, LOW);  // turn LED OFF
  delay(500);*/
}
