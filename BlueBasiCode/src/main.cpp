#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
void setup() {
    pinMode(2, OUTPUT);
    Serial.begin(115200);
    SerialBT.begin("cleitin"); //Bluetooth device name
}

void Conexao(){
    if(SerialBT.connected()){
        digitalWrite(2, HIGH);
    }else{
        digitalWrite(2, LOW);
    }
}


void loop() {
    Conexao();
    if (Serial.available()) {
        SerialBT.write(Serial.read());
    }
    if (SerialBT.available()) {
        Serial.write(SerialBT.read());
    }
    delay(200);
}