# Legs

Eight degree of freedom four legs robot library.


```
               _______________
              |---------------|
              |     Front     |
         ----- ---------------  -----
        | RS1 |                | LS1 |
         ----                    ----
   -----                            -----
  | RI1 |                          | LI1 |
   -----                            -----

               _______________
              |---------------|
              |     Back      |
         ----- ---------------  -----
        | LS2 |                | RS2 |
        ----                    ----
   -----                              -----
  | LI2 |                            | RI2 |
   -----                              -----
```


## Usage

```C
#include <Arduino.h>
#include <Legs.h>

// Define legs as global object.
Legs legs;

void setup() {
    Serial.begin(9600);

    /*
      Set digital pins:
        legs right front: 4, 5;
        legs right back: 6, 7;
        legs left front: 8, 9;
        legs left back: 10, 11;
    */
    legs.set_servos(4, 5, 6, 7, 8, 9, 10, 11);


    // Initial position, used to fix servos and legs.
    legs.zero_pos();


    /*
    Define de current state.
    Possible states:
      FORWARD, BACKWARD, LEFT, RIGHT, BYELEFT, BYERIGHT, STOP

    The ENDSTATE is used to verify if the current moviment is finished.
    */
    legs.set_current_state(FORWARD);
}

void loop() {
    /*
    Update the moviment according to the value defined by `set_current_state`
    method.
    */
    legs.move_according_state();
}
```

## Important Public Methods


### `start_i2c`
Start i2c communication.

### `set_servos`

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

### `zero_pos`
  Put all servos in initial position.

### `step`
  Move all servos to a defined angle.

  Parameters:

      rs1: integer angle of right front superior servo.

      ri1: integer angle of right front inferior servo.

      rs2: integer angle of right back superior servo.

      ri2: integer angle of right back inferior servo.

      ls1: integer angle of left front superior servo.

      li1: integer angle of left front inferior servo.

      ls2: integer pngle of left back superior servo.

      li2: integer angle of left back inferior servo.

### `move_forward`
  Move robot forward.

### `move_backward`
  Move robot backward.

### `turn_left`
  Turn robot to the left direction.

### `turn_right`

  Turn robot to right direction.

### `bye_bye_left`
  Send bye with left front leg.

### `bye_bye_right`
  Send bye with right front leg.

### `set_current_state`
  Set the moviment state;

### `move_according_state`
  Given the current state, update the moviment.


## Copyright

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
