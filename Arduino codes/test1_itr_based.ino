
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <TinyGPS++.h>

TinyGPSPlus gps; // create gps object
#define SIGNAL_TIMEOUT 500 
#define LED A1
const uint64_t pipeIn = 0xF9E8F0F0E1LL;
RF24 radio(22, 23);
unsigned long lastRecvTime = 0;

struct PacketData
{
  byte xAxisValue;
  byte yAxisValue;
  byte HEADLIGHTS;
  byte switchStatus;
} receiverData;

int triggerPin=40;
int echoPin=41;
const int sensorPin = A0;
const int sensorPin1 = A1;
const int sensorPin2 = A2;

int enableAMotor1=2;
int MotorAinput1=22;
int MotorAinput2=23;
int enableBMotor1=3;
int MotorBinput1=24;
int MotorBinput2=25;
int enableCMotor1=4;
int MotorCinput1=26;
int MotorCinput2=27;
int enableDMotor1=5;
int MotorDinput1=28;
int MotorDinput2=29;
int enableEMotor1=6;
int MotorEinput1=30;
int MotorEinput2=31;
int enableFMotor1=7;
int MotorFinput1=32;
int MotorFinput2=33;


void setup()
{
  cli();//stop interrupts

//set timer0 interrupt at 2kHz
  TCCR0A = 0;// set entire TCCR0A register to 0
  TCCR0B = 0;// same for TCCR0B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = 124;// = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);

  Serial.begin(9600);
  pinMode(enableAMotor1, OUTPUT);
  pinMode( MotorAinput1, OUTPUT);
  pinMode( MotorAinput2, OUTPUT);

  pinMode(enableBMotor1, OUTPUT);
  pinMode( MotorBinput1, OUTPUT);
  pinMode( MotorBinput2, OUTPUT);

 pinMode(enableCMotor1, OUTPUT);
  pinMode( MotorCinput1, OUTPUT);
  pinMode( MotorCinput2, OUTPUT);

  pinMode(enableDMotor1, OUTPUT);
  pinMode( MotorDinput1, OUTPUT);
  pinMode( MotorDinput2, OUTPUT);

  pinMode(enableEMotor1, OUTPUT);
  pinMode( MotorEinput1, OUTPUT);
  pinMode( MotorEinput2, OUTPUT);

 pinMode(enableFMotor1, OUTPUT);
  pinMode( MotorFinput1, OUTPUT);
  pinMode( MotorFinput2, OUTPUT);
  
  pinMode(LED, OUTPUT);
  stopRover();
  digitalWrite(LED, LOW);
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1, pipeIn);
  radio.startListening(); //start the radio receiver
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial3.begin(9600); // connect gps sensor
  sei();//allow interrupts
}
ISR(TIMER0_COMPA_vect){//timer0 interrupt 2kHz toggles pin 8
//generates pulse wave of frequency 2kHz/2 = 1kHz (takes two cycles for full wave- toggle high then toggle low)
  if(Serial3.available()){ // check for gps data
    if(gps.encode(Serial3.read()))// encode gps data
    { 
    
    //Latitude
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(),6);
    
    //Longitude
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(),6); 

    //Altitude
    Serial.print("Altitude: "); 
    Serial.println(gps.altitude.feet());

    //Speed
    Serial.print("Speed: "); 
    Serial.println(gps.speed.mph());

    // Number of satellites connected
    Serial.print("Number of Sats connected: "); 
    Serial.println(gps.satellites.value());
   }
}
}
void loop() {
  // Check if RF is connected and packet is available
  if (radio.isChipConnected() && radio.available()) {
    radio.read(&receiverData, sizeof(PacketData));

    // Process joystick values
    int yAxisValue = receiverData.xAxisValue;
    int xAxisValue = receiverData.yAxisValue;

    // Move the rover based on joystick values
    if (yAxisValue > 127) {
      // Move forward
      moveForward();
    } else if (yAxisValue < 127) {
      // Move backward
      moveBackward();
    } else if (xAxisValue > 127) {
      // Turn right
      turnRight();
    } else if (xAxisValue < 127) {
      // Turn left
      turnLeft();
    } else {
      // Stop the rover
      stopRover();
    }

    // Control headlights based on the switch status
    if (receiverData.switchStatus == HIGH) {
      turnOnHeadlights();
    } else {
      turnOffHeadlights();
    }

    lastRecvTime = millis();
  } else {
    // Signal lost. Reset the rover to stop
    unsigned long now = millis();
    if (now - lastRecvTime > SIGNAL_TIMEOUT) {
      stopRover();
    }
  }

  // Ultrasonic sensor obstacle detection
  long duration;
  int distance;
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("HC-SR04 Value: ");
   Serial.println(distance);
  if (distance < 30) {
    stopRover();
  }
  // Read analog value from the sensor
  int sensorValue = analogRead(sensorPin);

  // // Convert analog value to voltage
  float voltage = sensorValue * (5.0 / 1023.0);

  // Print the sensor value and voltage to the Serial Monitor
  Serial.print("MQ-4 Value: ");
  Serial.println(sensorValue);
   int sensorValue1 = analogRead(sensorPin1);

  // // Convert analog value to voltage
  float voltage = sensorValue * (5.0 / 1023.0);

  // Print the sensor value and voltage to the Serial Monitor
  Serial.print("MQ-7 Value: ");
  Serial.println(sensorValue1);

   int sensorValue2 = analogRead(sensorPin2);

  // Convert analog value to voltage
  float voltage = sensorValue * (5.0 / 1023.0);

  // Print the sensor value and voltage to the Serial Monitor
  Serial.print("MQ-2 Value: ");
  Serial.println(sensorValue2);
}

void moveForward() {
  // Set motor 1 configuration
  digitalWrite(MotorAinput1, HIGH);
  digitalWrite(MotorAinput2, LOW);
  analogWrite(enableAMotor1, 255);

  // Set motor 2 configuration
  digitalWrite(MotorBinput1, HIGH);
  digitalWrite(MotorBinput2, LOW);
  analogWrite(enableBMotor1, 255);

  // Set motor 3 configuration
  digitalWrite(MotorCinput1, HIGH);
  digitalWrite(MotorCinput2, LOW);
  analogWrite(enableCMotor1, 255);

  // Set motor 4 configuration
  digitalWrite(MotorDinput1, HIGH);
  digitalWrite(MotorDinput2, LOW);
  analogWrite(enableDMotor1, 255);

  // Set motor 5 configuration
  digitalWrite(MotorEinput1, HIGH);
  digitalWrite(MotorEinput2, LOW);
  analogWrite(enableEMotor1, 255);

  // Set motor 6 configuration
  digitalWrite(MotorFinput1, HIGH);
  digitalWrite(MotorFinput2, LOW);
  analogWrite(enableFMotor1, 255);
}

void moveBackward() {
  // Set motor 1 configuration
  digitalWrite(MotorAinput1, LOW);
  digitalWrite(MotorAinput2, HIGH);
  analogWrite(enableAMotor1, 255);

  // Set motor 2 configuration
  digitalWrite(MotorBinput1, LOW);
  digitalWrite(MotorBinput2, HIGH);
  analogWrite(enableBMotor1, 255);

  // Set motor 3 configuration
  digitalWrite(MotorCinput1, LOW);
  digitalWrite(MotorCinput2, HIGH);
  analogWrite(enableCMotor1, 255);

  // Set motor 4 configuration
  digitalWrite(MotorDinput1, LOW);
  digitalWrite(MotorDinput2, HIGH);
  analogWrite(enableDMotor1, 255);

  // Set motor 5 configuration
  digitalWrite(MotorEinput1, LOW);
  digitalWrite(MotorEinput2, HIGH);
  analogWrite(enableEMotor1, 255);

  // Set motor 6 configuration
  digitalWrite(MotorFinput1, LOW);
  digitalWrite(MotorFinput2, HIGH);
  analogWrite(enableFMotor1, 255);
}

void turnLeft() {
  // Set motor 1 configuration
  digitalWrite(MotorAinput1, HIGH);
  digitalWrite(MotorAinput2, LOW);
  analogWrite(enableAMotor1, 255);

  // Set motor 2 configuration
  digitalWrite(MotorBinput1, LOW);
  digitalWrite(MotorBinput2, HIGH);
  analogWrite(enableBMotor1, 255);

  // Set motor 3 configuration
  digitalWrite(MotorCinput1, HIGH);
  digitalWrite(MotorCinput2, LOW);
  analogWrite(enableCMotor1, 255);

  // Set motor 4 configuration
  digitalWrite(MotorDinput1, LOW);
  digitalWrite(MotorDinput2, HIGH);
  analogWrite(enableDMotor1, 255);

  // Set motor 5 configuration
  digitalWrite(MotorEinput1, HIGH);
  digitalWrite(MotorEinput2, LOW);
  analogWrite(enableEMotor1, 255);

  // Set motor 6 configuration
  digitalWrite(MotorFinput1, LOW);
  digitalWrite(MotorFinput2, HIGH);
  analogWrite(enableFMotor1, 255);
}

void turnRight() {
  // Set motor 1 configuration
  digitalWrite(MotorAinput1, LOW);
  digitalWrite(MotorAinput2, HIGH);
  analogWrite(enableAMotor1, 255);

  // Set motor 2 configuration
  digitalWrite(MotorBinput1, HIGH);
  digitalWrite(MotorBinput2, LOW);
  analogWrite(enableBMotor1, 255);

  // Set motor 3 configuration
  digitalWrite(MotorCinput1, LOW);
  digitalWrite(MotorCinput2, HIGH);
  analogWrite(enableCMotor1, 255);

  // Set motor 4 configuration
  digitalWrite(MotorDinput1, HIGH);
  digitalWrite(MotorDinput2, LOW);
  analogWrite(enableDMotor1, 255);

  // Set motor 5 configuration
  digitalWrite(MotorEinput1, LOW);
  digitalWrite(MotorEinput2, HIGH);
  analogWrite(enableEMotor1, 255);

  // Set motor 6 configuration
  digitalWrite(MotorFinput1, HIGH);
  digitalWrite(MotorFinput2, LOW);
  analogWrite(enableFMotor1, 255);
}

void stopRover() {
  // Set motor 1 configuration
  digitalWrite(MotorAinput1, LOW);
  digitalWrite(MotorAinput2, LOW);
  analogWrite(enableAMotor1, 0);

  // Set motor 2 configuration
  digitalWrite(MotorBinput1, LOW);
  digitalWrite(MotorBinput2, LOW);
  analogWrite(enableBMotor1, 0);

  // Set motor 3 configuration
  digitalWrite(MotorCinput1, LOW);
  digitalWrite(MotorCinput2, LOW);
  analogWrite(enableCMotor1, 0);

  // Set motor 4 configuration
  digitalWrite(MotorDinput1, LOW);
  digitalWrite(MotorDinput2, LOW);
  analogWrite(enableDMotor1, 0);

  // Set motor 5 configuration
  digitalWrite(MotorEinput1, LOW);
  digitalWrite(MotorEinput2, LOW);
  analogWrite(enableEMotor1, 0);

  // Set motor 6 configuration
  digitalWrite(MotorFinput1, LOW);
  digitalWrite(MotorFinput2, LOW);
  analogWrite(enableFMotor1, 0);
}

