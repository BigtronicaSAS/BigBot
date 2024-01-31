#include "Bluetooth.h"


BT::BT() : BluetoothSerial()
{
}

void BT::init()
{
    Serial.begin(9600);
    begin("BIGBOT");
    Serial.println("El dispositivo Bluetooth está listo para emparejarse");
}

void BT::car(Bot &bot, int velocidad)
{
    int bt_data;
    if (available())
    {
        bt_data = read();
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