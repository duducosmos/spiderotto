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

#include "Legs.h"
#include <Wire.h>

Legs * Legs::legsi2c = NULL;

Legs::Legs(){
    /*
    Constructor fo classe. 
    Start legsi2c as the current object.
    */
    legsi2c = this;
}

states Legs::get_current_state(){
    /*
    Return the current moviment state.
    States enumerator order:
        FORWARD
        BACKWARD
        LEFT
        RIGHT
        BYELEFT
        BYERIGHT
        STOP
        ENDSTATE
    */
    return current_state;
}

void Legs::set_servos(int rs1, int ri1,
          int rs2, int ri2,
          int ls1, int li1,
          int ls2, int li2){
    /*
    set servos ports.
    Parameters:
        rs1: integer port connected to right front superior servo.
        ri1: integer port connected to right front inferior servo.
        rs2: integer port connected to right back superior servo.
        ri2: integer port connected to right back inferior servo.
        ls1: integer port connected to left front superior servo.
        li1: integer port connected to left front inferior servo.
        ls2: integer port connected to left back superior servo.
        li2: integer port connected to left back inferior servo.

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
         -----                           -----
        | LI2 |                          | RI2 |
         -----                            -----
    */

    servo_rs1.attach(rs1);
    servo_ri1.attach(ri1);
    servo_rs2.attach(rs2);
    servo_ri2.attach(ri2);
    servo_ls1.attach(ls1);
    servo_li1.attach(li1);
    servo_ls2.attach(ls2);
    servo_li2.attach(li2);

}

void Legs::start_i2c(){
    /*
    Start i2c communication.
    */
    Wire.begin(i2c_address);
    Wire.onReceive(this->receive_data);
    Wire.onRequest(this->send_data);
}

void Legs::receive_data(int byte_count){
    /*
    Receive data from i2c communication.
    Parameter:
        byte_count: integer;
    */
    
    while(Wire.available()){
        int read = Wire.read();
        
        switch(read){
            case 0:
            legsi2c->set_current_state(FORWARD);
            break;
            case 1:
            legsi2c->set_current_state(BACKWARD);
            break;
            case 2:
            legsi2c->set_current_state(LEFT);
            break;
            case 3:
            legsi2c->set_current_state(RIGHT);
            break;
            case 4:
            legsi2c->set_current_state(BYELEFT);
            break;
            case 5:
            legsi2c->set_current_state(BYERIGHT);
            break;
            case 6:
            legsi2c->set_current_state(STOP);
            break;
            default:
            legsi2c->set_current_state(STOP);
            break;
        }
    }
}

void Legs::send_data(){
    /*
    Send data to i2c communication.
    Send the current legs moviment state.
    Info total bytes: 32
    */
    String info = "s:" + 
                  String(legsi2c->get_current_state()) +
                  ",ls:" +
                  String(legsi2c->is_last_step_movimet()) +
                  ",v:" +
                  String(legsi2c->get_velocity(), 3) +
                  ",d:" +
                  String(legsi2c->get_distance(), 3);

    Serial.println(info);
                  
    Wire.write(info.c_str());
   
}

void Legs::zero_pos(){
    /*
    Put all servos in initial position.
    */
    //  rs1, rs2, ls1, ls2, ri1, ri2, li1, li2
    step(180, 0, 0, 180, 0, 180, 180, 0);
}

void Legs::step(int rs1, int  rs2, int  ls1, int  ls2,
                int ri1, int  ri2, int  li1, int  li2){
    /*
    Move all servos to a defined angle:
    Parameters:
        rs1: integer angle of right front superior servo.
        ri1: integer angle of right front inferior servo.
        rs2: integer angle of right back superior servo.
        ri2: integer angle of right back inferior servo.
        ls1: integer angle of left front superior servo.
        li1: integer angle of left front inferior servo.
        ls2: integer pngle of left back superior servo.
        li2: integer angle of left back inferior servo.

    */
    servo_rs1.write(rs1);
    servo_rs2.write(rs2);
    servo_ls1.write(ls1);
    servo_ls2.write(ls2);

    servo_ri1.write(ri1);
    servo_ri2.write(ri2);
    servo_li1.write(li1);
    servo_li2.write(li2);

}

void Legs::move_forward(){
    /*
    Move robot forward.
    */
    if(cont_back_for > 13){
        cont_back_for = 0;
        last_step_movimet = true;
    }else{
        last_step_movimet = false;
    }

    if(millis() - t0 >= _delay_step){
        t0 = millis();
        // rs1, rs2, ls1, ls2, ri1, ri2, li1, li2
        step((int) _foward[cont_back_for][0],(int) _foward[cont_back_for][1],
             (int)_foward[cont_back_for][2],(int) _foward[cont_back_for][3],
             (int)_foward[cont_back_for][4],(int) _foward[cont_back_for][5],
             (int) _foward[cont_back_for][6],(int) _foward[cont_back_for][7]);
        cont_back_for += 1;
    }
}

void Legs::move_backward(){
    /*
    Move robot backward.
    */

    if(cont_back_for > 14){
        cont_back_for = 0;
        last_step_movimet = true;
    }else{
        last_step_movimet = false;
    }

    if(millis() - t0 >= _delay_step){
        t0 = millis();
        // rs1, rs2, ls1, ls2, ri1, ri2, li1, li2
        step((int)_backward[cont_back_for][0],(int) _backward[cont_back_for][1],
             (int) _backward[cont_back_for][2],(int) _backward[cont_back_for][3],
             (int) _backward[cont_back_for][4],(int) _backward[cont_back_for][5],
             (int) _backward[cont_back_for][6], (int)_backward[cont_back_for][7]);
        cont_back_for += 1;
    }
}


void Legs::turn_right(){
    /*
    Turn robot to right direction.
    */

    if(cont_left_right > 3){
        cont_back_for = 0;
        last_step_movimet = true;
    }else{
        last_step_movimet = false;
    }

    if(millis() - t0 >= _delay_turn){
        t0 = millis();
        // rs1, rs2, ls1, ls2, ri1, ri2, li1, li2
        step((int)_right[cont_left_right][0],(int) _right[cont_left_right][1],
             (int)_right[cont_left_right][2],(int) _right[cont_left_right][3],
             (int)_right[cont_left_right][4],(int) _right[cont_left_right][5],
             (int) _right[cont_left_right][6],(int) _right[cont_left_right][7]);
        cont_left_right += 1;
    }
}


void Legs::turn_left(){
    /*
    Turn robot to the left direction.
    */

    if(cont_left_right > 3){
        cont_left_right = 0;
        last_step_movimet = true;
    }else{
        last_step_movimet = false;
    }

    if(millis() - t0 >= _delay_turn){
        t0 = millis();
        // rs1, rs2, ls1, ls2, ri1, ri2, li1, li2
        step((int)_left[cont_left_right][0], (int) _left[cont_left_right][1],
             (int) _left[cont_left_right][2],(int) _left[cont_left_right][3],
             (int) _left[cont_left_right][4],(int) _left[cont_left_right][5],
             (int) _left[cont_left_right][6],(int) _left[cont_left_right][7]);
        cont_left_right += 1;
    }
}

void Legs::bye_bye_left(){
    /*
    Send bye with left front leg.
    */

    if(cont_bye > 6){
        cont_bye = 0;
        last_step_movimet = true;
    }else{
        last_step_movimet = false;
    }

    if(millis() - t0 >= _delay_bye){
        t0 = millis();
        // rs1, rs2, ls1, ls2, ri1, ri2, li1, li2
        step((int)_bye_left[cont_bye][0], (int) _bye_left[cont_bye][1],
             (int) _bye_left[cont_bye][2], (int) _bye_left[cont_bye][3],
             (int) _bye_left[cont_bye][4],(int) _bye_left[cont_bye][5],
             (int)_bye_left[cont_bye][6],(int) _bye_left[cont_bye][7]);
        cont_bye += 1;
    }

}

void Legs::bye_bye_right(){
    /*
    Send bye with right front leg.
    */

    if(cont_bye > 6){
        cont_bye = 0;
        last_step_movimet = true;
    }else{
        last_step_movimet = false;
    }

    if(millis() - t0 >= _delay_bye){
        t0 = millis();
        // rs1, rs2, ls1, ls2, ri1, ri2, li1, li2
        step((int)_bye_right[cont_bye][0], (int)_bye_right[cont_bye][1],
             (int) _bye_right[cont_bye][2],(int) _bye_right[cont_bye][3],
             (int)_bye_right[cont_bye][4], (int)_bye_right[cont_bye][5],
             (int) _bye_right[cont_bye][6], (int)_bye_right[cont_bye][7]);
        cont_bye += 1;
    }

}


void Legs::move_according_state(){
    /*
    Given the current state, update the moviment.
    */
    switch (get_current_state()) {
        case FORWARD:
        move_forward();
        break;
        case BACKWARD:
        move_backward();
        break;
        case LEFT:
        turn_left();
        break;
        case RIGHT:
        turn_right();
        break;
        case BYELEFT:
        bye_bye_left();
        break;
        case BYERIGHT:
        bye_bye_right();
        break;
        case STOP:
        zero_pos();
        break;
        default:
        zero_pos();
        break;
    }

}

String Legs::get_current_state_name(){
    /*
    Return a String representing the current state.
    */
    switch (get_current_state()) {
        case FORWARD:
        return "FORWARD";
        break;
        case BACKWARD:
        return "BACKWARD";
        break;
        case LEFT:
        return "LEFT";
        break;
        case RIGHT:
        return "RIGHT";
        break;
        case BYELEFT:
        return "BYELEFT";
        break;
        case BYERIGHT:
        return "BYERIGHT";
        break;
        case STOP:
        return "STOP";
        break;
        default:
        return "STOP";
        break;
    }
}
