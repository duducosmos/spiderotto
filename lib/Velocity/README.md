# HC-SR04 Velocity estimator

Used to measure distance, in cm, and estimate relative mean velocity of
objects in front of the HC-SR04 ultrassonic sensor, in cm per seconds.

## Usage

```C
#include <Arduino.h>
#include <Velocity.h>

Velocity velocity(5, 4);

void setup() {
    Serial.begin(9600);
}

void loop() {
  Serial.print("Average measured distance: ");
  Serial.println(velocity.average_distance_cm());

  Serial.print("Relative mean velocity: ")
  Serial.println(velocity.velocity_cm_per_s());

  if(velocity.velocity_cm_per_s() <= velocity.get_error_vel()){
    Serial.println("Object in relative rest.")
  }
}
```

Two options for constructor:

### `Velocity(int trigger_pin, int echo_pin)`

Constructor.
Used to measure distance, in cm, and estimate relative mean velocity of
objects in front of the HC-SR04 ultrassonic sensor.

Parameters:

  trigger_pin: integer. trigger  pin.

  echo_pin: integet. echo pin.

### `Velocity()`

  Constructor.
  Used to measure distance, in cm, and estimate relative mean velocity of
  objects in front of the HC-SR04 ultrassonic sensor.
  No parameters.

## Public methods

### `set_pins`:

Used to set trigger and echo pin after to create the Velocity object.

Parameters:

  trigger_pin: integer. trigger  pin.

  echo_pin: integet. echo pin.

### `measure_distance_cm`

Return the  distance obtained from HC-SR04 ultrassonic sensor.
Default timeout of the return pulse from trigger is 10000 microseconds.
No parameters.

### `measure_distance_cm`

Return the  distance obtained from HC-SR04 ultrassonic sensor.

Parameters:

  timeout: integer - The timeout, in microseconds to wait for the return pulse
                     from trigger, used by pulseIn function.

### `average_distance_cm`

Return the average distance calculated from data of  HC-SR04.

### `velocity_cm_per_s`

Return the relative mean velocity, in cm per seconds, of objetc in front of
HC-SR04. If the HC-SR04 is moving, the velocity represent the relative
velocity of the sensor.

### `get_error_dist`

Return the estimated distance error.

### `get_error_vel`

Return the estimated relative velocity error.
