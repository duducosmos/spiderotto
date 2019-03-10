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
#include <Velocity.h>

Legs legs;
Velocity velocity(5, 4);
bool turn = false;
bool bye = false;

void setup() {
    Serial.begin(9600);
    legs.start_i2c();
    legs.set_servos(6, 7, 8, 9, 10, 11, 12, 13);
    legs.zero_pos();
    legs.set_current_state(FORWARD);
    velocity.average_distance_cm();
    delay(1000);
}

void loop() {
    legs.set_distance(velocity.average_distance_cm());
    delay(10);

    if(legs.get_distance() < 20){
      turn = true;
    }

    /*

    if(bye == true){
      if(legs.get_current_state() == FORWARD){
        legs.set_current_state(BYELEFT);
      }else if(legs.is_last_step_movimet() == true && bye == true){
        bye = false;
        turn = true;
      }

    }
    */

    if(turn == true){
      if(legs.get_current_state() == FORWARD){
        legs.set_current_state(LEFT);
      }else if(legs.is_last_step_movimet() == true){
        bye = false;
        turn = false;
        legs.set_current_state(FORWARD);
      }
    }

    legs.move_according_state();
}
