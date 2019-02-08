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

    for(int i=0; i<15; i++){
        // rs1, rs2, ls1, ls2, ri1, ri2, li1, li2
        step(_foward[i][0], _foward[i][1], _foward[i][2], _foward[i][3],
             _foward[i][4], _foward[i][5], _foward[i][6], _foward[i][7]);
        delay(_delay_step);
    }

}

void Legs::move_backward(){
    for(int i=0; i< 14; i++){
        // rs1, rs2, ls1, ls2, ri1, ri2, li1, li2
        step(_backward[i][0], _backward[i][1], _backward[i][2], _backward[i][3],
             _backward[i][4], _backward[i][5], _backward[i][6], _backward[i][7]);
        delay(_delay_step);
    }
}


void Legs::turn_right(){
    for(int i=0; i < 4; i++){
        // rs1, rs2, ls1, ls2, ri1, ri2, li1, li2
        step(_right[i][0], _right[i][1], _right[i][2], _right[i][3],
             _right[i][4], _right[i][5], _right[i][6], _right[i][7]);
        delay(_delay_turn);
    }
}


void Legs::turn_left(){
    for(int i=0; i < 4 ; i++){
        // rs1, rs2, ls1, ls2, ri1, ri2, li1, li2
        step(_left[i][0], _left[i][1], _left[i][2], _left[i][3],
             _left[i][4], _left[i][5], _left[i][6], _left[i][7]);
        delay(_delay_turn);
    }
}

void Legs::bye_bye_left(){
    for(int i=0; i < 7 ; i++){
        // rs1, rs2, ls1, ls2, ri1, ri2, li1, li2
        step(_bye_left[i][0], _bye_left[i][1], _bye_left[i][2], _bye_left[i][3],
             _bye_left[i][4], _bye_left[i][5], _bye_left[i][6], _bye_left[i][7]);
        delay(_delay_bye);
    }

}

void Legs::bye_bye_right(){
    for(int i=0; i < 7 ; i++){
        // rs1, rs2, ls1, ls2, ri1, ri2, li1, li2
        step(_bye_right[i][0], _bye_right[i][1], _bye_right[i][2], _bye_right[i][3],
             _bye_right[i][4], _bye_right[i][5], _bye_right[i][6], _bye_right[i][7]);
        delay(_delay_bye);
    }

}
