#include "hardware/pio.h"
#include <cmath>

#include "quadrature_encoder.pio.h"

class QuadratureEncoder
{
public:
    QuadratureEncoder(uint8_t pin, float ppr, float gear_ratio = 1.0f);
    int32_t get_count();
    float get_angle(bool degrees = false);

private:
    PIO pio_instance;
    int8_t sm;

    float ppr;
    float gear_ratio;
};