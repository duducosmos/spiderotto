/*
Copyright 2019 Eduardo S. Pereira

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Legs.h>
#include <Velocity.h>

//SoftwareSerial bluetooth(2, 13); // TX, RX (Bluetooth)
int incomingByte;


Velocity velocity(3, 4);   // (Trig PIN,Echo PIN)


unsigned long t0;
unsigned long delta_t=5000;
boolean back = false;
boolean left = false;
boolean bye = false;

float d0 = 0;
float v0 = 0;
float dt;

Legs legs;
float seno;
int frequencia;

void setup() {
    legs.start_i2c();
    legs.set_servos(4, 5, 8, 9, 2, 3, 6, 7);
    legs.zero_pos();
    Serial.begin(9600);
    t0 = millis();
    dt = millis();
 

}

void loop() {

    Serial.println(legs.get_current_state());

    legs.move_according_state();

}
