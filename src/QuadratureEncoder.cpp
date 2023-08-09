#include "QuadratureEncoder.hpp"

QuadratureEncoder::QuadratureEncoder(uint8_t pin, float ppr, float gear_ratio) : ppr(ppr * 4.0f), gear_ratio(gear_ratio)
{
    pio_instance = pio0;
    sm = pio_claim_unused_sm(pio_instance, true);
    if (sm == -1)
        pio_instance = pio1;
    sm = pio_claim_unused_sm(pio_instance, true);
    if (sm == -1)
        throw std::runtime_error("No free state machine found!");
    uint offset = pio_add_program(pio_instance, &quadrature_encoder_program);
    quadrature_encoder_program_init(pio_instance, sm, pin, 0);
}

void QuadratureEncoder::update(float dt)
{
    _last_count = _count;
    _count = quadrature_encoder_get_count(pio_instance, sm);
    _dt = dt;
}

int32_t QuadratureEncoder::get_count()
{
    return _count;
}

float QuadratureEncoder::get_position(bool degrees)
{
    if (degrees)
        return 360.0f * _count / (ppr * gear_ratio); // deg
    else
        return 2 * M_PI * _count / (ppr * gear_ratio); // rad
}

float QuadratureEncoder::get_velocity(bool degrees)
{
    float velocity = ((_count - _last_count) / (ppr * gear_ratio)) / _dt;

    if (degrees)
        return 360.0f * velocity; // deg/s
    else
        return 2 * M_PI * velocity; // rad/s
}

bool QuadratureEncoder::get_direction()
{
    return _count > _last_count ? 1 : -1;
}

int8_t QuadratureEncoder::get_sign()
{
    return (_count > 0) - (_count < 0);
}
