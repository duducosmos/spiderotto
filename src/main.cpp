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

    legs.set_servos(4, 5, 8, 9, 2, 3, 6, 7);
    legs.zero_pos();

    Serial.begin(9600);

    //bluetooth.begin(9600);
    delay(1000);
    t0 = millis();
    pinMode(A0, OUTPUT);
    dt = millis();
    velocity.average_distance_cm();
    legs.set_current_state(FORWARD);

}

void loop() {

    Serial.println(legs.get_current_state());

    /*

    if(velocity.average_distance_cm() < 10 and legs.is_last_step_movimet() == true){
        tone(A0, 440, 1000);
        legs.set_current_state(BYELEFT);
        legs.set_last_step_movimet(false);
    }

    if(legs.get_current_state() == BYELEFT and legs.is_last_step_movimet() == true){
        legs.set_current_state(FORWARD);
    }
    */

    legs.move_according_state();



    //Serial.println(velocity.velocity_cm_per_s());
    //legs.zero_pos();
    /*
    if (bluetooth.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = bluetooth.read();
    // if it's a capital H (ASCII 72), turn on the LED:
    if (incomingByte == 'W') {
      legs.move_forward();
       bluetooth.println("LED: ON");
    }
    // if it's an L (ASCII 76) turn off the LED:
    if (incomingByte == 'S') {
      legs.move_backward();
    }
  }

    */
        //bluetooth.print("Velo cm/s: ");
        //bluetooth.println(velocity.measure_distance_cm());




}
