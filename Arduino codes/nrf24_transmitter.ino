
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define Joystick_min_value 0
#define Joystick_max_value 1023
#define Joystick_mid_value 511
#define Joystick_mid_buffer 30

#define min_value 0
#define max_value 254
#define mid_value 127

#define sw_pin 2

#define headlight 3
const uint64_t pipeOut = 0xF9E8F0F0E1LL;   //IMPORTANT: The same as in the receiver 0xF9E8F0F0E1LL

RF24 radio(9, 10); // select CE,CSN pin

struct PacketData
{
  byte Xaxis_val;
  byte Yaxis_val;
  byte Headlight_flag;
  byte SW_status;
} data;

void setup()
{

  Serial.begin(9600);


  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipeOut);
  radio.stopListening(); //start the radio Transmitter

  pinMode(headlight, INPUT_PULLUP);
  pinMode(sw_pin, INPUT_PULLUP);
  data.Xaxis_val = mid_value; // Center
  data.Yaxis_val = mid_value; // Center
}

// Map joystick values to be sent per byte. So max value for 1 byte is 255. We select max as 254 so that center value is 127.
int mapAndAdjustValues(int val, int lower, int middle, int upper, bool reverse)
{
  val = constrain(val, lower, upper);

  //middle == 0: This is the case when joystick is not auto centered type. We map full range here.
  if (middle == 0)
  {
    val = map(val, lower , upper, min_value , max_value);
    return (reverse ? max_value - val : val);
  }

  if ( val <= middle - Joystick_mid_buffer )
  {
    val = map(val, lower , middle - Joystick_mid_buffer, min_value , mid_value);
  }
  else if (val >= middle + Joystick_mid_buffer)
  {
    val = map(val, middle + Joystick_mid_buffer , upper, mid_value, max_value);
  }
  else
  {
    val = mid_value;
  }

  return (reverse ? max_value - val : val);
}



void loop()
{
  int Xaxis_val = analogRead(A1);
  int Yaxis_val = analogRead(A3);

  data.Xaxis_val = mapAndAdjustValues( Xaxis_val, Joystick_min_value, Joystick_mid_value, Joystick_max_value, false );     // "true" for reverse direction
  data.Yaxis_val = mapAndAdjustValues( Yaxis_val, Joystick_min_value, Joystick_mid_value, Joystick_max_value, true );       // "true" for reverse direction
  data.Headlight_flag = digitalRead(headlight);
  data.SW_status=digitalRead(sw_pin);

  Serial.println("The raw value is ");
  Serial.println(Xaxis_val);
  Serial.println(Yaxis_val);
  Serial.println("The mapped value is ");
  Serial.println(data.Xaxis_val);
  Serial.println(data.Yaxis_val);
  Serial.println(radio.isChipConnected());
  delay(10);


  radio.write(&data, sizeof(PacketData));
}
