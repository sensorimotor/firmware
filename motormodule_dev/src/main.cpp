#include <mbed.h>
#include <Serial.h>

#include <brushless_dc.h>
#include <trapezoid.h>

namespace supreme {

/* voltage + current sensors */
// AnalogIn u_us(A0);
// AnalogIn u_is(A1);
// AnalogIn v_us(A2);
// AnalogIn v_is(A3);
// AnalogIn w_us(A4);
// AnalogIn w_is(A5);

class main_app {

    Serial msg;
    motor_ctrl::trapezoid ctrl;

public:
    main_app()
    : msg(USBTX, USBRX)
    , ctrl(msg)
    {
        msg.baud(115200);
        ctrl.set_velocity(0.60);
    }

    void step() {
        //ctrl.step(); //TODO how to prevent collisions

        wait(0.1); // 10ms

        // float u = u_us.read(); //TODO use voltage of currently floating h-bridge as speed signal

        motor_ctrl::HallSensor3Elements::bin_state_t st = ctrl.sensor.get_binary_state();
        unsigned pos = ctrl.sensor.get_state();
        msg.printf("%u %u %u | %u | % d % d % d\n", st.h1, st.h2, st.h3, pos
                                                  , motor_ctrl::lut::ctrl[pos][0]
                                                  , motor_ctrl::lut::ctrl[pos][1]
                                                  , motor_ctrl::lut::ctrl[pos][2]);
    } // step

}; // class main_app

} // namspace supreme

int main() {
    supreme::main_app app;
    while(1)
        app.step();
}
