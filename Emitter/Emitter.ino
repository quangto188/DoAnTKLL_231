//Transmitter program

#include <SPI.h>
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"
Nrf24l Mirf = Nrf24l(10, 9);
int value;
struct data{
  int xAxis;
  int yAxis;

};
const int x_out = A0;
const int y_out = A1;
data send_data;
void setup()
{
  Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  //Set your own address (sender address) using 5 characters
  Mirf.setRADDR((byte *)"ABCDE");
  Mirf.payload = sizeof(send_data);
  Mirf.channel = 90;              //Set the channel used
  Mirf.config();
}

void loop()
{
  send_data.xAxis = analogRead(x_out);
  send_data.yAxis = analogRead(y_out);
  Mirf.setTADDR((byte *)"FGHIJ");           //Set the receiver address
  //value = random(255);                      //0-255 random number
  Mirf.send((byte *)&send_data);                //Send instructions, send random number value
  Serial.print("Wait for sending.....");
  while (Mirf.isSending()) delay(1);        //Until you send successfully, exit the loop
  Serial.print("Send success:");
  Serial.println(send_data.xAxis);
  Serial.println(send_data.yAxis);
  Serial.println("");

}