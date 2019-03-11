#include "Arduino.h"
#include "Velocity.h"


Velocity::Velocity(){
        /*
           Constructor.
           Used to measure distance, in cm, and estimate relative mean velocity of
           objects in front of the HC-SR04 ultrassonic sensor.
         */
        start_reads();
}

Velocity::Velocity(int trigger_pin, int echo_pin){
        /*
           Constructor.
           Used to measure distance, in cm, and estimate relative mean velocity of
           objects in front of the HC-SR04 ultrassonic sensor.
           Parameters:
           trigger_pin: integer. trigger  pin.
           echo_pin: integet. echo pin.
         */
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
        /*
           Used to set trigger and echo pin after to create the Velocity object.
           Parameters:
           trigger_pin: integer. trigger  pin.
           echo_pin: integet. echo pin.
         */
        set_echo_pin(echo_pin);
        set_trigger_pin(trigger_pin);

        pinMode(trigger_pin, OUTPUT);
        pinMode(echo_pin, OUTPUT);
}



double Velocity::measure_distance_cm(){
        /*
           Return the  distance obtained from HC-SR04 ultrassonic sensor.
           Default timeout of the return pulse from trigger is 10000 microseconds.
         */
        return measure_distance_cm(10000);
}

double Velocity::measure_distance_cm(int timeout){
        /*
           Return the  distance obtained from HC-SR04 ultrassonic sensor.
           Parameters:
           timeout: integer - The timeout, in microseconds to wait for the return pulse
                             from trigger, used by pulseIn function.
         */

        // Make sure that trigger pin is LOW.
        digitalWrite(trigger_pin, LOW);
        delayMicroseconds(2);
        // Hold trigger for 10 microseconds, which is signal for sensor to measure distance.
        digitalWrite(trigger_pin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigger_pin, LOW);
        // Measure the length of echo signal, which is equal to the time needed for sound to go there and back.
        unsigned long durationMicroSec = pulseIn(echo_pin, HIGH, timeout);
        double distanceCm = durationMicroSec / 2.0 * 0.0343;
        if (distanceCm == 0 || distanceCm > 400) {
                return -1.0;
        } else {
                return distanceCm;
        }
}

void Velocity::calc_error_dist(){
        /*
           Estimate the mean square error of distance and velocity measurement.
         */
        double diffsquare;
        totalDiffSquare = 0;

        for(int i = 0; i < readsize; i++) {

                diffsquare = (reads[i] - averageReads);
                diffsquare *= diffsquare;
                totalDiffSquare += diffsquare;

        }

        error_dist = sqrt(totalDiffSquare / ((double) readsize - 1));
        error_vel = error_dist / ( (double) dt / 1000.0);
}


double Velocity::average_distance_cm(){
        /*
           Return the average distance calculated from data of  HC-SR04.
         */

        double measure = measure_distance_cm();

        if(measure > 0) {
                totalReads = totalReads - reads[readIndex];

                reads[readIndex] = measure;

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
        /*
           Return the relative mean velocity, in cm per seconds, of objetc in front of
           HC-SR04. If the HC-SR04 is moving, the velocity represent the relative
           velocity of the sensor.
         */
        if(millis() - t0 > dt) {

                v = s0 - average_distance_cm();
                v = v / ( (double) dt / 1000.0);
                s0 = average_distance_cm();
                t0 = millis();
        }

        return v;
}
