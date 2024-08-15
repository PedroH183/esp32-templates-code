#include "BluetoothSerial.h"

String device_name = "ESP32-BT-Slave";

// Check if Bluetooth is available
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Check Serial Port Profile
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;
char *temperatura;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_DEVICE");
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
  pinMode(2, OUTPUT);

  temperatura = (char*) malloc(sizeof(char));
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
  temperatura = itoa(random(0, 100), temperatura, 10);
  SerialBT.printf("Temperatura : %s C\n", temperatura);

  delay(1000);
}
