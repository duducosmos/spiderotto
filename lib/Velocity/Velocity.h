
#ifndef VELOCITY_H
#define VELOCITY_H
#include "Arduino.h"


class Velocity {
private:

    #define readsize 30
unsigned int readIndex = 0;
double s0=0;

double reads[readsize];
double totalReads;
double averageReads=0;
double totalDiffSquare=0;
double error_dist;
double error_vel;

int trigger_pin;
int echo_pin;

unsigned long dt = 500;
double v = 0;
unsigned long t0=millis();

void start_reads();
void calc_error_dist();

public:

Velocity();
Velocity(int trigger_pin, int echo_pin);
void set_pins(int trigger_pin, int echo_pin);
double measure_distance_cm(int timeout);
double measure_distance_cm();
void set_trigger_pin(int _trigger_pin){
        trigger_pin = _trigger_pin;
}
void set_echo_pin(int _echo_pin){
        echo_pin=_echo_pin;
}
double average_distance_cm();
double velocity_cm_per_s();
double get_error_dist(){
        return error_dist;
}
double get_error_vel(){
        return error_vel;
}

};

#endif
