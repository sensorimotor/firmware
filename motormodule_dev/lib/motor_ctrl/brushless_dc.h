#ifndef SUPREME_MOTOR_CTRL_BRUSHLESS_DC_H
#define SUPREME_MOTOR_CTRL_BRUSHLESS_DC_H

#include <mbed.h>
#include <halfbridge.h>

namespace supreme { namespace motor_ctrl {

const unsigned default_period_us = 1000; /*TODO define */

class BrushlessDC {

    halfbridge u, v, w;

public:
    void set_mode(output_t m_u, output_t m_v, output_t m_w) {
        u.set_mode(m_u);
        v.set_mode(m_v);
        w.set_mode(m_w);
    }

    void set_duty_cycle(float dc) {
        u.set_duty_cycle(dc);
        v.set_duty_cycle(dc);
        w.set_duty_cycle(dc);
    }

    BrushlessDC(unsigned period_us = default_period_us) // TODO configurable frequency, not period
    : u(D2, D3, period_us) /* TODO make µC pins configurable */
    , v(D4, D5, period_us)
    , w(D6, D7, period_us)
    { /* TODO trace */ }

};

}} // namespace supreme::motor_ctrl

#endif // SUPREME_MOTOR_CTRL_BRUSHLESS_DC_H
