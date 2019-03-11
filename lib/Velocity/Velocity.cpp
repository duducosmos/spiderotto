#include "Arduino.h"
#include "Velocity.h"


Velocity::Velocity(){
        start_reads();
}

Velocity::Velocity(int trigger_pin, int echo_pin){
        this->trigger_pin = trigger_pin;
        this->echo_pin = echo_pin;
        pinMode(trigger_pin, OUTPUT);
        pinMode(echo_pin, INPUT);
        start_reads();
}


void Velocity::start_reads(){
        for(int i=0; i < readsize; i++) {
                reads[i] =  0;
        }
}

void Velocity::set_pins(int trigger_pin, int echo_pin){
        set_echo_pin(echo_pin);
        set_trigger_pin(trigger_pin);

        pinMode(trigger_pin, OUTPUT);
        pinMode(echo_pin, OUTPUT);
}


double Velocity::measure_distance_cm(){

        // Make sure that trigger pin is LOW.
        digitalWrite(trigger_pin, LOW);
        delayMicroseconds(2);
        // Hold trigger for 10 microseconds, which is signal for sensor to measure distance.
        digitalWrite(trigger_pin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigger_pin, LOW);
        // Measure the length of echo signal, which is equal to the time needed for sound to go there and back.
        unsigned long durationMicroSec = pulseIn(echo_pin, HIGH, 10000);
        double distanceCm = durationMicroSec / 2.0 * 0.0343;
        if (distanceCm == 0 || distanceCm > 400) {
                return -1.0;
        } else {
                return distanceCm;
        }
}

void Velocity::calc_error_dist(){
        double diffsquare;
        totalDiffSquare = 0;

        for(int i = 0; i < readsize; i++) {

                diffsquare = (reads[i] - averageReads);
                diffsquare *= diffsquare;
                totalDiffSquare += diffsquare;

        }

        error = sqrt(totalDiffSquare / ((double) readsize - 1));
}


double Velocity::average_distance_cm(){

        double mesure = measure_distance_cm();

        if(mesure > 0) {
                totalReads = totalReads - reads[readIndex];

                reads[readIndex] = mesure;

                totalReads = totalReads + reads[readIndex];
                readIndex += 1;
                if(readIndex >= readsize) {
                        readIndex = 0;
                        averageReads = totalReads / readsize;
                        calc_error_dist();
                }

        }

        return averageReads;
}

double Velocity::velocity_cm_per_s(){

        if(millis() - t0 > dt) {

                v = s0 - average_distance_cm();
                v = v / ( (double) dt / 1000.0);
                s0 = average_distance_cm();
                t0 = millis();
        }

        return v;
}
