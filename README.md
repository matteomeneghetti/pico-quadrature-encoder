# RP2040 Quadrature Encoder Interface

This repository contains a C++ implementation of a Quadrature Encoder interface for the Raspberry Pi Pico microcontroller. The Quadrature Encoder interface allows you to read incremental rotary encoders, which are commonly used for measuring the position, velocity, and direction of rotating devices.

## Features

- Calculate position, velocity, and direction based on encoder input.
- PIO instance based processing with automatic free state machine selection

## Example

```c++
#include <QuadratureEncoder.hpp>

uint8_t A_pin = 10; // pin where the A channel is attached, the B channel needs to be connected to the following pin (in this case pin 11)
float ppr = 1024.0; // pulses per revolution of the encoder
auto encoder(A_pin, ppr);

float sampling_time = 1e-3;

while (true) {
    // ...
    encoder.update(sampling_time);
    auto position = encoder.get_position();
    auto velocity = encoder.get_velocity();
    // ...
}
```

## License

This project is licensed under the MIT License.