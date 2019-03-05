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
#include <Servo.h>
#include <Wire.h>
#ifndef LEGS_H
#define LEGS_H

/*
                  Front
             ---------------
            |     O   O     |
            |---------------|
            |               |
       ----- ---------------  -----
      | RS1 |                | LS1 |
       ----                    ----
  -----                              -----
 | RI1 |                            | LI1 |
  -----                              -----

                  Back
             ---------------
            |               |
            |---------------|
            |               |
       ----- ---------------  -----
      | LS2 |                | RS2 |
       ----                    ----
 -----                              -----
| LI2 |                            | RI2 |
 -----                              -----


*/

enum states {FORWARD, BACKWARD, LEFT, RIGHT, BYELEFT, BYERIGHT, STOP, ENDSTATE};

class Legs {
    
private:
    Servo servo_rs1;
    Servo servo_ri1;
    Servo servo_rs2;
    Servo servo_ri2;
    Servo servo_ls1;
    Servo servo_li1;
    Servo servo_ls2;
    Servo servo_li2;
    unsigned long _delay_step = 100;
    unsigned long _delay_turn = 100;
    unsigned long _delay_bye = 500;
    unsigned long t0=millis();
    int cont_back_for=0;
    int cont_bye=0;
    int cont_left_right=0;
    int i2c_address = 0x04;

    states current_state=STOP;
    boolean last_step_movimet = false;


    byte _foward[14][8] = {     //rs1, rs2, ls1, ls2, ri1, ri2, li1, li2
                                //{120, 30, 30, 120, 30, 130, 140, 30},
                                // R2
                                //rs1, rs2, ls1, ls2, ri1, ri2, li1, li2
                                {110, 10, 30, 170, 30, 100, 160, 30},
                                {110, 60, 30, 170, 30, 100, 160, 30},
                                {110, 60, 30, 170, 30, 130, 160, 30},
                                // R1
                                //rs1, rs2, ls1, ls2, ri1, ri2, li1, li2
                                {110, 60, 30, 170, 60, 130, 160, 30},
                                {170, 60, 30, 170, 60, 130, 160, 30},
                                {170, 60, 30, 170, 30, 130, 160, 30},
                                //All backward
                                {110, 10, 30, 170, 30, 130, 160, 30},
                                //L2
                               //rs1, rs2,ls1,ls2, ri1, ri2, li1, li2
                                {110, 10, 30, 170, 30, 130, 160, 60},
                                {110, 10, 30, 90, 30, 130, 160, 60},
                                {110, 10, 30, 90, 30, 130, 160, 30},
                                //L1
                               //rs1,rs2, ls1, ls2, ri1, ri2, li1, li2
                                {110, 10, 30, 90, 30, 130, 90, 30},
                                {110, 10, 0,  90, 30, 130,  90, 30},
                                {110, 10, 0,  90, 30, 130, 160, 30},
                                //All backward
                                {110, 10, 30, 170, 30, 130, 160, 30}
                    };

    byte _backward[15][8] = { // rs1, rs2, ls1, ls2, ri1, ri2, li1, li2
                        {120, 30, 30, 120, 30, 130, 130, 30},
                        //L1
                        {120, 30, 10, 90, 30, 130, 130, 30},
                        {120, 30, 0, 90, 30, 130, 90, 30},
                        {120, 30, 30, 90, 30, 130, 90, 30},
                        //L2
                        {120, 30, 30, 90, 30, 130, 130, 30},
                        {120, 30, 30, 90, 30, 130, 130, 60},
                        {120, 30, 30, 120, 30, 130, 130, 60},
                        //All backward
                        {120, 30, 60, 160, 30, 130, 130, 30},
                        // R1
                        {160, 60, 30, 120, 30, 130, 130, 30},
                        {160, 60, 30, 120, 60, 130, 130, 30},
                        {120, 60, 30, 120, 60, 130, 130, 30},
                        // R2
                        {120, 60, 30, 120, 30, 130, 130, 30},
                        {120, 60, 30, 120, 30, 100, 130, 30},
                        {120, 30, 30, 120, 30, 100, 130, 30},
                        //All backward
                        {120, 30, 30, 120, 30, 130, 130, 30}

                    };

    byte _left[5][8] = {//rs1, rs2, ls1, ls2, ri1, ri2, li1, li2
                        {120, 30,  30,  120, 30,  130, 130, 30},
                        {120, 30,  30,  120, 30,  110, 110, 30},
                        {120, 60,  60,  120, 30,  110, 110, 30},
                        {120, 60,  60,  120, 60,  130, 130, 60},
                    };

    byte _right[5][8] = {//rs1, rs2, ls1, ls2, ri1, ri2, li1, li2
                        {120, 30,  30,  120, 30,  130, 130, 30},
                        {120, 30,  30,  120, 90,  130, 130, 90},
                        {90,  30,  30,   90, 90,  130, 130, 90},
                        {90,  30,  30,   90, 30,  110, 110, 30},
                    };

    byte _bye_left[7][8] = {//rs1, rs2, ls1, ls2, ri1, ri2, li1, li2
                           {120, 30,  30,  120, 30,  130, 130, 30},
                           {180, 30,  0,   120, 0,   180, 130, 0},
                           {180, 30,  0,   120, 0,   180,  50, 0},
                           {180, 30,  0,   120, 0,   180,  90, 0},
                           {180, 30,  0,   120, 0,   180,  50, 0},
                           {180, 30,  0,   120, 0,   180,  90, 0},
                           {120, 30,  30,  120, 30,  130, 130, 30}
                         };

     byte _bye_right[7][8] = {//rs1, rs2, ls1, ls2, ri1, ri2, li1, li2
                            {120,  30,  30,   120, 30,  130, 130, 30},
                            {120,  30,   0,   120, 50,  180, 180, 0},
                            {120,  30,   0,   120, 90,  180, 180, 0},
                            {120,  30,   0,   120, 50,  180, 180, 0},
                            {120,  30,   0,   120, 90,  180, 180, 0},
                            {120,  30,   0,   120, 50,  180, 180, 0},
                            {120,  30,  30,   120, 30,  130, 130, 30}
                          };

public:
    static Legs * legsi2c;
    static void receive_data(int byte_count);
    static void send_data();
    Legs();
    void start_i2c();
    void set_servos(int rs1, int ri1, int rs2, int ri2,
                    int ls1, int li1, int ls2, int li2);
    void zero_pos();
    void step(int rs1, int rs2, int ls1, int ls2,
              int ri1, int ri2, int li1, int li2);
    void move_forward();
    void move_backward();
    void turn_left();
    void turn_right();
    void bye_bye_left();
    void bye_bye_right();

    states get_current_state(){return current_state;}
    void set_current_state(states state){current_state = state;}
    void move_according_state();
    boolean is_last_step_movimet(){return last_step_movimet;}
    void set_last_step_movimet(boolean cstep){ last_step_movimet = cstep;}
    void set_i2c_address(int address){i2c_address = address;}
    int get_i2c_address(){return i2c_address;}

};

#endif
