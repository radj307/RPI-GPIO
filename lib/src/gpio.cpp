/*

MIT License

Copyright (c) 2018 Guillaume Bauer

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
#include "gpio.h"

using namespace rpigpio;

/** Public methods **/

bool GPIO::connect() {
    if (!peripheral.map()) return false;
    p_base = peripheral.getBase();
    return true;
}

bool GPIO::disconnect() {
    if (p_base) {
        peripheral.unmap();
        p_base = nullptr;
    }

    return true;
}

void GPIO::pinMode(unsigned int pin, PIN_MODE mode) const {
    unsigned int rnum = pin / 10;
    unsigned int offset = (pin % 10) * 3;
    r(GPFSEL[rnum]) &= ~(0b111 << offset);
    r(GPFSEL[rnum]) |= (pinModeToInt(mode) << offset);
}

void GPIO::pinUp(unsigned int pin) const {
    if (pin < 32) {
        r(GPSET0) |= 1 << pin;
    } else if (pin >= 32) {
        r(GPSET1) |= 1 << (pin - 32);
    }
}

void GPIO::pinDown(unsigned int pin) const {
    if (pin < 32) {
        r(GPCLR0) |= 1 << pin;
    } else if (pin >= 32) {
        r(GPCLR1) |= 1 << (pin - 32);
    }
}

unsigned int GPIO::pinLev(unsigned int pin) const {
    if (pin < 32) {
        return (r(GPLEV0) & 1 << pin) != 0;
    } else if (pin >= 32) {
        return (r(GPLEV1) & 1 << (pin - 32)) != 0;
    } else {
        return 0;
    }
}

void GPIO::digitalWrite(unsigned int pin, PIN_LEVEL lev) const {
    switch(lev) {
        case PIN_LEVEL::LOW:
            pinDown(pin);
            break;
        case PIN_LEVEL::HIGH:
            pinUp(pin);
    }
}

unsigned int GPIO::digitalRead(unsigned int pin) const {
    return pinLev(pin);
}

void GPIO::reset() const {
    r(GPFSEL[0]) &= ~(0xFFFFFFC0); 
    r(GPFSEL[1]) = 0;
    r(GPFSEL[2]) &= ~(0xFFFFFF);
    r(GPCLR0) = 0xFFFFFFC;
}




/** Private methods **/

volatile uint32_t& GPIO::r(const uint32_t off) const {
    return *(p_base + (off / 4));
}

constexpr unsigned int GPIO::pinModeToInt(PIN_MODE mode) const {
    return static_cast<unsigned int> (mode);
}

constexpr unsigned int GPIO::pinLevelToInt(PIN_LEVEL lev) const {
    return static_cast<unsigned int> (lev);
}
