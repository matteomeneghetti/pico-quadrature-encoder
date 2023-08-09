#include "hardware/pio.h"
#include <cmath>
#include <stdexcept>

#include "quadrature_encoder.pio.h"

class QuadratureEncoder
{
public:
    /** @brief Implementation of a QuadratureEncoder which uses a PIO instance to count each pulse
     *
     * @param degrees: the A channel pin, the B channel should be connected to the following pin
     * @param ppr: pulses per revolution of the encoder
     * @param gear_ratio: if the encoder is attached to some kind of reduction, specify it here.
     *  This is particularly useful when the encoder is attacahed to an actuator with any kind of gearbox.
     */
    QuadratureEncoder(uint8_t pin, float ppr, float gear_ratio = 1.0f);

    /** @brief Updates the internal encoder state. To be called at each sampling time
     *
     * @param the current sampling time, aka the time between each update method call
     */
    void update(float dt);

    /** @brief Returns the internal counter value of the encoder
     *
     * @return return the signed integer value of the current counter
     */
    int32_t get_count();

    /** @brief Returns the current angle of the encoder
     *
     * @param degrees: returns the value in deg
     * @return return the angle in rad
     */
    float get_position(bool degrees = false);

    /** @brief Returns the current velocity of the encoder
     *
     * @param degrees: returns the value in deg/s
     * @return return the velocity in rad/s
     */
    float get_velocity(bool degrees = false);

    /** @brief Returns the current direction of the encoder
     *
     * @return 1 for positive increment or -1 for negative increment
     */
    bool get_direction();

    /** @brief Returns the current sign of the encoder
     *
     * @return 1 for positive sign or -1 for negative sign
     */
    int8_t get_sign();

    void reset();

private:
    PIO pio_instance;
    int8_t sm;

    float ppr;
    float gear_ratio;

    int32_t _count = 0;
    int32_t _last_count = 0;
    float _dt = 1.0f;
};