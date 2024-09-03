#include <Arduino.h>
#include <ESP32Servo.h>

#define true 1
#define false 0

// joystick config
int joystick_pin_x   = A0; // GPIO 36 VP Analogico
int joystick_pin_y   = A3; // GPIO 39 VN Analogico
int sw_pin_joystick = A6; // GPIO 34 

// Servos config
Servo servo_x_machine;
int servo_x_pin = 18;

Servo servo_y_machine;
int servo_y_pin = 19;

int state_y_position = 0;
int state_x_position = 90;

// mapas config
int offset_x_valid = 0; // diferença de intervalos maximo de x
int offset_y_valid = 0; // diferença de intervalos maximo de y

int cantoSuperiorEsquerdoX = 0;
int cantoSuperiorEsquerdoY = 0;

int cantoInferiorDireitoX = 0;
int cantoInferiorDireitoY = 0;


// configurações de eventos
bool inicio = false;


void incrementXYJoyStick(){
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
    if (map_volts_y_value > 3695 && state_y_position > 0){
        state_y_position--;
    }
    delay(3);
}

void setupSuperiorEsquerdo(){
    while(!digitalRead(sw_pin_joystick)){
        incrementXYJoyStick();
        cantoSuperiorEsquerdoX = state_x_position;
        cantoSuperiorEsquerdoY = state_y_position;
    }
    Serial.printf("CLICOUUUUUUUUUUUU");
}

void setupInferiorDireito(){
    while(!digitalRead(sw_pin_joystick)){
        incrementXYJoyStick();
        cantoInferiorDireitoX = state_x_position;
        cantoInferiorDireitoY = state_y_position;
    }
    Serial.printf("CLICOUUUUUUUUUUUU");
}

void setup() {
    pinMode(sw_pin_joystick, INPUT_PULLUP);
    servo_x_machine.attach(servo_x_pin);
    servo_x_machine.write(state_x_position);

    servo_y_machine.attach(servo_y_pin);
    servo_y_machine.write(state_y_position);
    Serial.begin(115200);
}

void loop() {

    if(1){
        while(!digitalRead(sw_pin_joystick)){
            incrementXYJoyStick();
            cantoSuperiorEsquerdoX = state_x_position;
            cantoSuperiorEsquerdoY = state_y_position;
        }
        Serial.printf("CLICOUUUUUUUUUUUU");

        setupInferiorDireito();
        inicio = 0;
    }

    incrementXYJoyStick();

    Serial.printf("X : %d \n", analogRead(joystick_pin_x));
    Serial.printf("Y : %d \n", analogRead(joystick_pin_y));
    servo_x_machine.write(state_x_position);
    servo_y_machine.write(state_y_position);

    delay(3);
}