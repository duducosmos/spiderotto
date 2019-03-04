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

void Legs::set_servos(int rs1, int ri1,
          int rs2, int ri2,
          int ls1, int li1,
          int ls2, int li2){

    servo_rs1.attach(rs1);
    servo_ri1.attach(ri1);
    servo_rs2.attach(rs2);
    servo_ri2.attach(ri2);
    servo_ls1.attach(ls1);
    servo_li1.attach(li1);
    servo_ls2.attach(ls2);
    servo_li2.attach(li2);

}

void Legs::zero_pos(){
    //  rs1, rs2, ls1, ls2, ri1, ri2, li1, li2
    step(180, 0, 0, 180, 0, 180, 180, 0);
}

void Legs::step(int rs1, int  rs2, int  ls1, int  ls2,
                int ri1, int  ri2, int  li1, int  li2){
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
        move_forward();
        break;
    }

}
