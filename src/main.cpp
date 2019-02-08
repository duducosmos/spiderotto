#include <Arduino.h>
#include <Legs.h>
#include <Ultrasonic.h>
Ultrasonic ultrasonic(12,11);   // (Trig PIN,Echo PIN)

unsigned long t0;
unsigned long delta_t=5000;
boolean back = false;
boolean left = false;

Legs legs;

void setup() {
    Serial.begin(9600);
    legs.set_servos(10, 9, 8, 7, 6, 5, 4, 3);
    legs.zero_pos();
    delay(1000);
    t0 = millis();
}

void loop() {
    Serial.print("cm: " );
    Serial.println(ultrasonic.Ranging(CM)); // CM or INC
    delay(50);
    if(ultrasonic.Ranging(CM) < 10){
        back = true;
        t0 = millis();
        legs.bye_bye_right();
    }

    /*

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
    */

}
