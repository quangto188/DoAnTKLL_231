//Receiver program
#include <SPI.h>
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"
Nrf24l Mirf = Nrf24l(8,10);
int ENA = 3;
int ENB = 9;
int MotorA1 = 4;
int MotorA2 = 5;
int MotorB1 = 6;
int MotorB2 = 7;
struct data {
  int xAxis;
  int yAxis;

};
data receive_data;

void setup()
{
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(MotorA1, OUTPUT);
  pinMode(MotorA2, OUTPUT);
  pinMode(MotorB1, OUTPUT);
  pinMode(MotorB2, OUTPUT);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();

  Mirf.setRADDR((byte *)"FGHIJ"); //Set your own address (receiver address) using 5 characters
  Mirf.payload = sizeof(receive_data);
  Mirf.channel = 90;             //Set the used channel
  Mirf.config();
  Serial.println("Listening...");  //Start listening to received data
}

void loop()
{
  if (Mirf.dataReady()) { //When the program is received, the received data is output from the serial port
    Mirf.getData((byte *) &receive_data);
    Serial.print("Got data: ");
    // Serial.println(receive_data.xAxis);
    // Serial.println(receive_data.yAxis);
    // Serial.println("");
if(receive_data.yAxis > 400) {
  //Đi thẳng
Serial.println("đi thẳng");

  digitalWrite(MotorA1, LOW);
  digitalWrite(MotorA2, HIGH);
  digitalWrite(MotorB1, LOW);
  digitalWrite(MotorB2, HIGH);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  
}else if(receive_data.yAxis < 320) {
  //đi lùi
Serial.println("đi lùi");

  digitalWrite(MotorA1, HIGH);
  digitalWrite(MotorA2, LOW);
  digitalWrite(MotorB1, HIGH);
  digitalWrite(MotorB2, LOW);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
} else if(receive_data.xAxis < 320){
  //Rẽ trái
Serial.println("Rẽ trái");

   digitalWrite(MotorA1, HIGH);
  digitalWrite(MotorA2, LOW);
  digitalWrite(MotorB1, LOW);
  digitalWrite(MotorB2, HIGH);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
}else if(receive_data.xAxis > 400){
  //Rẽ phải
Serial.println("Rẽ phải");
 digitalWrite(MotorA1, LOW);
  digitalWrite(MotorA2, HIGH);
  digitalWrite(MotorB1, HIGH);
  digitalWrite(MotorB2, LOW);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
}else {
  Serial.println("Stop!!");

  digitalWrite(MotorA1, LOW);
  digitalWrite(MotorA2, LOW);
  digitalWrite(MotorB1, LOW);
  digitalWrite(MotorB2, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  }
  }

}







