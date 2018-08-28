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

#include "RPI-GPIO/gpio.h"
#include "RPI-GPIO/memory.h"

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

void GPIO::pinMode(char pin, PIN_MODE mode) {
    unsigned int rnum = pin / 10;
    unsigned int offset = (pin % 10) * 3;
    r(GPFSEL0 + (rnum * 4)) &= ~(0b111 << offset);
    r(GPFSEL0 + (rnum * 4)) |= (pinModeToInt(mode) << offset);
}

void GPIO::pinUp(char pin) {
    if (pin < 32) {
        r(GPSET0) |= 1 << pin;
    } else if (pin >= 32) {
        r(GPSET1) |= 1 << (pin - 32);
    }
}

void GPIO::pinDown(char pin) {
    if (pin < 32) {
        r(GPCLR0) |= 1 << pin;
    } else if (pin >= 32) {
        r(GPCLR1) |= 1 << (pin - 32);
    }
}

char GPIO::pinLev(char pin) {
    if (pin < 32) {
        return (r(GPLEV0) & 1 << pin) == 1;
    } else if (pin >= 32) {
        return (r(GPLEV1) & 1 << (pin - 32)) == 1;
    } else {
        return 0;
    }
}





/** Private methods **/
constexpr volatile uint32_t& GPIO::r(uint32_t off) const {
    return *(p_base + off);
}

constexpr unsigned int GPIO::pinModeToInt(PIN_MODE mode) const {
    return static_cast<unsigned int> (mode);
}