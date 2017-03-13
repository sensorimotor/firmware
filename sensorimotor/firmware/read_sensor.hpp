/* read_sensor.hpp */
#include <xpcc/architecture/platform.hpp>

namespace supreme {

class read_sensor { //TODO: find better name
    typedef xpcc::avr::SystemClock clock;

    uint16_t value;
public:
    read_sensor()
    : value()
    {
        /* initialize ADC */
        A0::setInput();
        Adc::initialize<clock, 115000>();
        Adc::setReference(Adc::Reference::InternalVcc);
        value = Adc::readChannel(7);
        Adc::setChannel(7);
        Adc::startConversion();
    }

    void step() {
        if (Adc::isConversionFinished()){
            value = Adc::getValue();
            // restart the conversion
            Adc::setChannel(7);
            Adc::startConversion();
        }
    }

    uint16_t get_value() const { return value; }
};

} /* namespace supreme */