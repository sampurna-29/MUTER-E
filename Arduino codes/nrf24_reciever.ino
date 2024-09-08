
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

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


int enableAMotor1=2;
int MotorAinput1=8;
int MotorAinput2=9;
int enableBMotor1=3;
int MotorBinput1=10;
int MotorBinput2=11;
int enableCMotor1=4;
int MotorCinput1=12;
int MotorCinput2=13;
int enableDMotor1=5;
int MotorDinput1=14;
int MotorDinput2=15;
int enableEMotor1=6;
int MotorEinput1=16;
int MotorEinput2=17;
int enableFMotor1=7;
int MotorFinput1=18;
int MotorFinput2=19;


void setup()
{
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
  rotateMotor(0, 0);
  digitalWrite(LED, LOW);
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1, pipeIn);
  radio.startListening(); //start the radio receiver

}

void loop()
{

  int motorSpead1 = 0;
  int motorSpead2 = 0;
  Serial.println(radio.isChipConnected());
  Serial.println(radio.available());
  // Check if RF is connected and packet is available
  if (radio.isChipConnected() && radio.available())
  {   
    radio.read(&receiverData, sizeof(PacketData));
    This is default mode to run motors. Switch is open and HIGH if not pushed.
  Serial.print("xAxisValue:");
  Serial.println(receiverData.xAxisValue);
  Serial.print("yAxisValue:");
  Serial.println(receiverData.yAxisValue);
  Serial.println(radio.isChipConnected());
    Serial.print("switch:");
   Serial.println(receiverData.switchStatus);
   Serial.print("HEADLIGHTS:");
  Serial.println(receiverData.HEADLIGHTS);
  Serial.println("");

    if (receiverData.switchStatus)
    {

     moveCar();
     logicToTurnMotorsOnBothSide();
      if (receiverData.HEADLIGHTS == LOW)
        digitalWrite(LED, HIGH);
      else if (receiverData.HEADLIGHTS == HIGH)
        digitalWrite(LED, LOW);
      HEADLIGHTS control

    else
    {
          Serial.println("bhjvhjbkbj");
      logicToTurnMotorsOnBothSide();
    }
    lastRecvTime = millis();
  }
  else
  {
    Serial.println("no radio ");
    // Signal lost. Reset the motor to stop
    unsigned long now = millis();
    if ( now - lastRecvTime > SIGNAL_TIMEOUT )
    {
      rotateMotor(0, 0);
    }
  }

}

void moveCar()
{
  int motorSpead1 = 0;
  int motorSpead2 = 0;
  int throttle = map(receiverData.yAxisValue, 0, 254, -255, 255);
  int mappedXValue = map(receiverData.xAxisValue, 0, 254, 255, -255);
  int motorDirection = 1;
  if (throttle < 0)
  {
    motorDirection = -1;
  }

  motorSpead1 = abs(throttle) - mappedXValue;
  motorSpead2 = abs(throttle) + mappedXValue;

  motorSpead1 = constrain(motorSpead1, 0, 255);
  motorSpead2 = constrain(motorSpead2, 0, 255);

  rotateMotor(motorSpead1 * motorDirection, motorSpead2 * motorDirection);
}

void rotateMotor(int speed1, int speed2)
{
  if (speed1 < 0)
  {
    Serial.println("A");
    digitalWrite(MotorAinput1, LOW);
    digitalWrite(MotorAinput2, HIGH);
    digitalWrite(MotorCinput1, LOW);
    digitalWrite(MotorCinput2, HIGH);
    digitalWrite(MotorEinput1, LOW);
    digitalWrite(MotorEinput2, HIGH);
  }
  else if (speed1 >= 0)
  {
    digitalWrite(MotorAinput1, HIGH);
    digitalWrite(MotorAinput2, LOW);
    digitalWrite(MotorCinput1, HIGH);
    digitalWrite(MotorCinput2, LOW);
    digitalWrite(MotorEinput1, HIGH);
    digitalWrite(MotorEinput2, LOW);
  }

  if (speed2 < 0)
  {
    digitalWrite(MotorBinput1, LOW);
    digitalWrite(MotorBinput2, HIGH);
    digitalWrite(MotorDinput1, LOW);
    digitalWrite(MotorDinput2, HIGH);
    digitalWrite(MotorFinput1, LOW);
    digitalWrite(MotorFinput2, HIGH);
  }
  else if (speed2 >= 0)
  {
    digitalWrite(MotorBinput1, HIGH);
    digitalWrite(MotorBinput2, LOW);
    digitalWrite(MotorDinput1, HIGH);
    digitalWrite(MotorDinput2, LOW);
    digitalWrite(MotorFinput1, HIGH);
    digitalWrite(MotorFinput2, LOW);
  }


 Serial.println(speed1);
  Serial.println(speed2);
  analogWrite(enableAMotor1, abs(speed1));
  analogWrite(enableBMotor1, abs(speed2));
  analogWrite(enableCMotor1, abs(speed1));
  analogWrite(enableDMotor1, abs(speed2));
  analogWrite(enableEMotor1, abs(speed1));
  analogWrite(enableFMotor1, abs(speed2));
}

void logicToTurnMotorsOnBothSide()
{
  int motorSpead1 = 0;
  int motorSpead2 = 0;
  int throttle = map(receiverData.yAxisValue, 0, 254, -255, 255);
  int mappedXValue = map(receiverData.xAxisValue, 0, 254, -255, 255);
  if (throttle < 0)
  {
    mappedXValue = -mappedXValue;
  }

  motorSpead1 = throttle - mappedXValue;
  motorSpead2 = throttle + mappedXValue;

  motorSpead1 = constrain(motorSpead1, -255, 255);
  motorSpead2 = constrain(motorSpead2, -255, 255);

  rotateMotor(motorSpead1, motorSpead2);
}


