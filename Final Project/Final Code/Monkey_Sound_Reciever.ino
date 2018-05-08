
#include "I2Cdev.h"
#include "MPU6050.h"

//Include needed Libraries at beginning
#include "nRF24L01.h" // NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24
#include "RF24.h"
#include "SPI.h"

int ReceivedMessage[1] = {000}; // Used to store value received by the NRF24L01

RF24 radio(9, 10); // NRF24L01 used SPI pins + Pin 9 and 10 on the UNO

const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

MPU6050 accelgyro;


int16_t ax, ay, az;
int16_t gx, gy, gz;
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"


SoftwareSerial mySoftwareSerial(7, 8);
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

# define ACTIVATED LOW

boolean isPlaying = false;

#define OUTPUT_READABLE_ACCELGYRO



bool blinkState = false;




const int ledPinM1 = 3;
const int ledPinM2 = 4;
const int ledPinM3 = 5;
const int ledPinM4 = 6;

int ax2;


const int GREEN_PIN = A3;


bool monkeygamebegin = false;
bool ledStateGREEN = HIGH;

void setup() {

  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true) {
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(20);  //Set volume value. From 0 to 30



  Serial.begin(38400);


  radio.begin(); // Start the NRF24L01

  radio.openReadingPipe(1, pipe); // Get NRF24L01 ready to receive

  radio.startListening(); // Listen to see if information received

  pinMode(ledPinM1, OUTPUT);
  pinMode(ledPinM2, OUTPUT);
  pinMode(ledPinM3, OUTPUT);
  pinMode(ledPinM4, OUTPUT);

  pinMode(GREEN_PIN, OUTPUT);

  // join I2C bus (I2Cdev library doesn't do this automatically)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);

#endif

  // initialize device
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();

  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
}

void loop() {

  //  mp3_play (1);


  while (radio.available())
  {
    radio.read(ReceivedMessage, 1); // Read information from the NRF24L01

    if (ReceivedMessage[0] == 111) // Indicates switch is pressed
    {
      Serial.println("hello");
      digitalWrite(GREEN_PIN, HIGH);
      radio.stopListening();
      //      isPlaying = true;
      //      playFirst();
      delay(5000);
      digitalWrite(GREEN_PIN, LOW);
      bananameter();
      monkeygamebegin = false;
    }
    else
    {
      digitalWrite(GREEN_PIN, LOW);
      Serial.println("nohting");
    }
    delay(10);
  }


  // put your main code here, to run repeatedly:

  // read raw accel/gyro measurements from device
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

#ifdef OUTPUT_READABLE_ACCELGYRO
  // display tab-separated accel/gyro x/y/z values
  Serial.print("a/g:\t");
  Serial.print(ax); Serial.print("\t");
  Serial.print(ay); Serial.print("\t");
  Serial.print(az); Serial.print("\t");
  Serial.print(gx); Serial.print("\t");
  Serial.print(gy); Serial.print("\t");
  Serial.println(gz);
  delay(200);
#endif

#ifdef OUTPUT_BINARY_ACCELGYRO
  Serial.write((uint8_t)(ax >> 8)); Serial.write((uint8_t)(ax & 0xFF));
  Serial.write((uint8_t)(ay >> 8)); Serial.write((uint8_t)(ay & 0xFF));
  Serial.write((uint8_t)(az >> 8)); Serial.write((uint8_t)(az & 0xFF));
  Serial.write((uint8_t)(gx >> 8)); Serial.write((uint8_t)(gx & 0xFF));
  Serial.write((uint8_t)(gy >> 8)); Serial.write((uint8_t)(gy & 0xFF));
  Serial.write((uint8_t)(gz >> 8)); Serial.write((uint8_t)(gz & 0xFF));
#endif

  ax2 = map(ax, 10000, 17000, 0, 15);//Map value 0-1023 to 0-255 (PWM)
  Serial.println(ax2);
  delay(200); //Small delay


  if (ax2 >= 14) {
    digitalWrite(ledPinM1, LOW);
    delay(5000);
    if (digitalRead(ledPinM1 == LOW && ledPinM2 == LOW && ledPinM3 == LOW && ledPinM4 == LOW)) {

      if (ReceivedMessage[0] == 111) // Indicates switch is pressed
      {
        //        delay(5000);
        Serial.println("hello");
        digitalWrite(GREEN_PIN, HIGH);
        radio.stopListening();
        delay(5000);
        //        isPlaying = true;
        //        playFirst();
        digitalWrite(GREEN_PIN, LOW);
        bananameter();
        monkeygamebegin = false;

      }
      else
      {
        digitalWrite(GREEN_PIN, LOW);
        Serial.println("nohting");
      }
    }
  }

  if (ax2 <= 13) {
    digitalWrite(ledPinM2, LOW);
  }

  if (ax2 >= 16) {
    digitalWrite(ledPinM3, LOW);
  }

  if (ax2 <= 12) {
    digitalWrite(ledPinM4, LOW);
    
  }


}



int bananameter() {

  myDFPlayer.play(1);  //Play the first mp3

  Serial.print("bananameter running -  -  - ");
  digitalWrite(ledPinM1, HIGH);
  delay(500);
  digitalWrite(ledPinM2, HIGH);
  delay(500);
  digitalWrite(ledPinM3, HIGH);
  delay(500);
  digitalWrite(ledPinM4, HIGH);
  delay(500);
  //  isPlaying = false;
  Serial.println("bananameter done");
}


void printDetail(uint8_t type, int value) {
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}




