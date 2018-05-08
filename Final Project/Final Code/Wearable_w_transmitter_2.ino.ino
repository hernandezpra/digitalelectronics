//Include needed Libraries at beginning
#include "nRF24L01.h" //NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24
#include "RF24.h"
#include "SPI.h"

int SentMessage[1] = {000}; // Used to store value before being sent through the NRF24L01

RF24 radio(9, 10); // NRF24L01 used SPI pins + Pin 9 and 10 on the NANO

const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01

//Constants:

const int ledPinR1 = 2;
const int ledPinR2 = 3;
const int ledPinR3 = 4;

const int ledPinL1 = 7;
const int ledPinL2 = 6;
const int ledPinL3 = 5;

const int ledPinShift1 = 11;
const int ledPinShift2 = 12;
const int ledPinShift3 = 13;


const int ledNeutral = A3;
const int led30deg = A4;
const int led20deg = A2;

const int flexPinR = A1; //pin A1 to read analog input
const int flexPinL = A0;
bool startR = true;
bool startL = true;
bool gamebegin = true;

bool ledStateNeutral = HIGH;
bool ledState30deg = HIGH;

bool transmit = false;

unsigned long previousMillis = 0;

//Variables:
int value; //save analog value
int value2; //save analog value
int value3; //save analog value
int value4; //save analog value
int value5; //save analog value

int valueA; //save analog value
int value2A; //save analog value
int value3A; //save analog value
int value4A; //save analog value
int value5A; //save analog value

unsigned long trigger;
bool hold = false;


// the setup function runs once when you press reset or power the board
void setup() {
  
  radio.begin(); // Start the NRF24L01
  radio.openWritingPipe(pipe); // Get NRF24L01 ready to transmit
  Serial.begin(9600);


  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ledPinShift1, OUTPUT);
  pinMode(ledPinShift2, OUTPUT);
  //  pinMode(ledPinShift3, OUTPUT);


  pinMode(ledPinR1, OUTPUT);
  pinMode(ledPinR2, OUTPUT);
  pinMode(ledPinR3, OUTPUT);
  pinMode(ledPinL1, OUTPUT);
  pinMode(ledPinL2, OUTPUT);
  pinMode(ledPinL3, OUTPUT);
  pinMode(ledNeutral, OUTPUT);
  pinMode(led30deg, OUTPUT);
  pinMode(led20deg, OUTPUT);
  Serial.begin(9600);       //Begin serial communication
}


// the loop function runs over and over again forever
void loop() {

  if (transmit == true) { // If Switch is Activated
    SentMessage[0] = 111;
    radio.write(SentMessage, 1); // Send value through NRF24L01
    Serial.println("hello");
  }
  else {
    SentMessage[0] = 000;
    radio.write(SentMessage, 1);
    Serial.println("nothing");
  }


  neutralstart();


  value = analogRead(flexPinR);         //Read and save analog value from potentiometer
  //Print value
  value2 = map(value, 800, 900, 0, 500);//Map value 0-1023 to 0-255 (PWM)
  Serial.println(value2);
  delay(200); //Small delay

  valueA = analogRead(flexPinL);         //Read and save analog value from potentiometer
  //Print value
  value2A = map(valueA, 800, 900, 0, 500);//Map value 0-1023 to 0-255 (PWM)
  Serial.println(value2A);
  delay(200); //Small delay


  if (value2 <= 740) {
    value3 = map(value2, 0, 500, 0, 255);//Map value 0-1023 to 0-255 (PWM)
    digitalWrite(ledPinR1, value3);
  } else {
    digitalWrite(ledPinR1, LOW);
  }


  if (value2 <= 710) {
    value4 = map(value2, 700, 900, 0, 255);//Map value 0-1023 to 0-255 (PWM)
    digitalWrite(ledPinR2, value4);
  } else {
    digitalWrite(ledPinR2, LOW);
  }


  if (value2 <= 690) {
    value5 = map(value2, 700, 900, 0, 255);//Map value 0-1023 to 0-255 (PWM)
    digitalWrite(ledPinR3, value5);
    fullyreachedR();
  } else {
    digitalWrite(ledPinR3, LOW);
  }




  if (value2A <= 660) {
    value3A = map(value2A, 0, 500, 0, 255);//Map value 0-1023 to 0-255 (PWM)
    digitalWrite(ledPinL1, value3A);
  } else {
    digitalWrite(ledPinL1, LOW);
  }


  if (value2A <= 640) {
    value4A = map(value2A, 700, 900, 0, 255);//Map value 0-1023 to 0-255 (PWM)
    digitalWrite(ledPinL2, value4A);
  } else {
    digitalWrite(ledPinL2, LOW);
  }


  if (value2A <= 620) {
    value5A = map(value2A, 700, 900, 0, 255);//Map value 0-1023 to 0-255 (PWM)
    digitalWrite(ledPinL3, value5A);
    fullyreachedL();
  } else {
    digitalWrite(ledPinL3, LOW);
  }

}

int fullyreachedR() {
  if (startR == true) {
    Serial.println("blink");
    for (int i; i < 11; i++) {
      digitalWrite(led30deg, !digitalRead(led30deg));
      delay(1000);
    }

    startR = false;
    Serial.println("done with blink");
    ///neutral lights with 6 second delay
    digitalWrite(led30deg, LOW);

    transmit = true;
    neutral();

    transmit = false;

    ////
  }
}

int fullyreachedL() {
  if (startL == true) {
    Serial.println("blink");
    for (int i; i < 11; i++) {
      digitalWrite(led20deg, !digitalRead(led20deg));
      delay(1000);
    }

    startL = false;
    Serial.println("done with blink");
    ///neutral lights with 6 second delay
    digitalWrite(led20deg, LOW);
    neutralFinal();
    ////
  }
}

int neutralstart() {

  if (gamebegin == true) {
    unsigned long currentMillis = millis();

    digitalWrite(ledNeutral, ledStateNeutral);

    if (currentMillis >= 3000) {
      ledStateNeutral = LOW;
      digitalWrite(led30deg, HIGH);
    }
  }
}

int neutral() {
  gamebegin = false;
  digitalWrite(led30deg, LOW);
  digitalWrite(ledNeutral, HIGH);
  delay(5000);
  leftexerciselight();
  transmit = true;
}

int neutralFinal() {
  gamebegin = false;
  digitalWrite(led30deg, LOW);
  digitalWrite(ledNeutral, HIGH);

  digitalWrite(ledPinR1, HIGH);
  digitalWrite(ledPinR2, HIGH);
  digitalWrite(ledPinR3, HIGH);
  digitalWrite(ledPinL1, HIGH);
  digitalWrite(ledPinL2, HIGH);
  digitalWrite(ledPinL3, HIGH);

  for (int i; i < 6; i++) {
    digitalWrite(ledNeutral, !digitalRead(ledNeutral));
    digitalWrite(ledPinR1, !digitalRead(ledPinR1));
    digitalWrite(ledPinR2, !digitalRead(ledPinR2));
    digitalWrite(ledPinR3, !digitalRead(ledPinR3));
    digitalWrite(ledPinL1, !digitalRead(ledPinL1));
    digitalWrite(ledPinL2, !digitalRead(ledPinL2));
    digitalWrite(ledPinL3, !digitalRead(ledPinL3));
    delay(200);
  }
// transmit = true;
  delay(1000);

}

int leftexerciselight() {
  digitalWrite(ledNeutral, LOW);
  digitalWrite(led20deg, HIGH);

}










