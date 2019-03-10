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
Velocity velocity(10, 11);

void setup() {
    Serial.begin(9600);
    legs.start_i2c();
    legs.set_servos(4, 5, 8, 9, 2, 3, 6, 7);
    legs.zero_pos();
}

void loop() {
    legs.set_distance(velocity.average_distance_cm());
    legs.set_velocity(velocity.velocity_cm_per_s());
    legs.move_according_state();
}
