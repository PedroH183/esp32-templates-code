#include <Arduino.h>
#include <ESP32Servo.h>

Servo servo_x_machine;
int servo_x_pin = 18;

Servo servo_y_machine;
int servo_y_pin = 19;

int joystick_pin_x   = A0; // GPIO 36
int joystick_pin_y   = A10; // GPIO 4

int state_y_position = 0;
int state_x_position = 90;


void setup() {
    servo_x_machine.attach(servo_x_pin);
    servo_x_machine.write(state_x_position);

    servo_y_machine.attach(servo_y_pin);
    servo_y_machine.write(state_y_position);
    Serial.begin(115200);
}

void loop() {
    int map_volts_x_value = analogRead(joystick_pin_x);
    int map_volts_y_value = analogRead(joystick_pin_y);

    if (map_volts_x_value < 200 && state_x_position < 180){
        state_x_position++;
    }
    if (map_volts_x_value > 3895 && state_x_position > 0){
        state_x_position--;
    }

    if (map_volts_y_value < 200 && state_y_position < 90){
        state_y_position++;
    }
    if (map_volts_y_value > 3895 && state_y_position > 0){
        state_y_position--;
    }

    Serial.printf("X : %d \n", analogRead(joystick_pin_x));
    Serial.printf("Y : %d \n", analogRead(joystick_pin_y));
    servo_x_machine.write(state_x_position);
    servo_y_machine.write(state_y_position);
    delay(15);
}