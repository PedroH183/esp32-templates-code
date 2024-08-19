#include <Arduino.h>
#include <ESP32Servo.h>

Servo MyServo;
int pinServo = 18;

const int joystick_x_pin = 12; // tem que ser ADC pins 

void setup() {
    // ServoSetup(MyServo, pinServo);
    MyServo.attach(pinServo);
    MyServo.write(0);

    Serial.begin(115200); // setando o valor de referencia dos bits para comunicação 
}

void loop() {
    int x_delta = analogRead(joystick_x_pin); // value between 0 and 1023, this value is a analog read needs convert
    int x_angle = map(x_delta, 0, 4095, 0, 180); // mapeamento do deslocamento em trechos de 0 - 179 (normalização)

    Serial.println(x_angle);

    MyServo.write(x_angle);
    delay(50);
}