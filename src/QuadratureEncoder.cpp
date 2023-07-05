#include "QuadratureEncoder.hpp"

QuadratureEncoder::QuadratureEncoder(uint8_t pin, float ppr, float gear_ratio) : ppr(ppr * 4.0f), gear_ratio(gear_ratio)
{
    pio_instance = pio0;
    sm = pio_claim_unused_sm(pio_instance, true);
    if (sm == -1)
        pio_instance = pio1;
    sm = pio_claim_unused_sm(pio_instance, true);
    uint offset = pio_add_program(pio_instance, &quadrature_encoder_program);
    quadrature_encoder_program_init(pio_instance, sm, pin, 0);
}

int32_t QuadratureEncoder::get_count()
{
    return quadrature_encoder_get_count(pio_instance, sm);
}

float QuadratureEncoder::get_angle(bool degrees)
{
    if (degrees)
        return 360.0f * this->get_count() / (ppr * gear_ratio);
    else
        return 2 * M_PI * this->get_count() / (ppr * gear_ratio);
}
