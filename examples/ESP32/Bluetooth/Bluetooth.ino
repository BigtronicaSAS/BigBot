#include <Bigbot.h>
#include "Bluetooth.h"

//Pinout BotARDUINO = {10, 12, 11, 13, 8, 7, 4};
Pinout BotESP32 = {5, 19, 23, 18, 12, 14, 17};

Bot bot(BotESP32);
BluetoothSerial BT; 
int bt_data;

void setup()
{
  Serial.begin(9600); 
  BT.begin("BIGBOT"); 
  Serial.println("El dispositivo Bluetooth está listo para emparejarse");
}

void loop()
{
  if (BT.available())
  {
    bt_data = BT.read();
    Serial.print("Recibido: ");
    Serial.println(bt_data);
    if (bt_data == 70)
    {
      bot.adelante(255);
    }
    else if (bt_data == 66)
    {
      bot.atras(255);
    }
    else if (bt_data == 76)
    {
      bot.girar_izquierda(255);
    }
    else if (bt_data == 82)
    {
      bot.girar_derecha(255);
    }
    else if (bt_data == 83)
    {
      bot.parar();
    }
  }

}