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
#include <Legs.h>
#include <Ultrasonic.h>
Ultrasonic ultrasonic(12,11);   // (Trig PIN,Echo PIN)

unsigned long t0;
unsigned long delta_t=5000;
boolean back = false;
boolean left = false;

float d0 = 0;
float v0 = 0;
float dt;

Legs legs;
float seno;
int frequencia;

void setup() {
    Serial.begin(9600);
    legs.set_servos(10, 9, 8, 7, 6, 5, 4, 3);
    legs.zero_pos();
    delay(1000);
    t0 = millis();
    pinMode(13, OUTPUT);
    dt = millis();
}

void loop() {

    dt = (millis() - dt) / 1000.0;
    v0 = (ultrasonic.Ranging(CM) - d0) / dt;
    dt = millis();
    d0 = ultrasonic.Ranging(CM);

    Serial.print("Velo (cm/s): ");
    Serial.println(v0);

    if(ultrasonic.Ranging(CM) < 10){
        back = true;
        t0 = millis();
        tone(13, 440, 1000);
        legs.bye_bye_right();

    }


    if(back == true){
        while(millis() - t0 < delta_t){
            legs.move_backward();
        }
        back = false;
        left = true;
        t0 = millis();

    }

    if(left == true){
        while(millis() - t0 < delta_t){
            legs.turn_left();
        }
        left = false;
    }

    legs.move_forward();


}
