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

#include <cstdint>
#include "RPI-GPIO/memory.h"

#pragma once


/**  GPIO register adress offsets **/
constexpr uint32_t GPFSEL0 = 0x0;
constexpr uint32_t GPFSEL1 = 0x4;
constexpr uint32_t GPFSEL2 = 0x8;
constexpr uint32_t GPFSEL3 = 0xc;
constexpr uint32_t GPFSEL4 = 0x10;
constexpr uint32_t GPFSEL5 = 0x14;

constexpr uint32_t GPSET0 = 0x1c;
constexpr uint32_t GPSET1 = 0x20;

constexpr uint32_t GPCLR0 = 0x28;
constexpr uint32_t GPCLR1 = 0x2c;

constexpr uint32_t GPLEV0 = 0x34;
constexpr uint32_t GPLEV1 = 0x38;


/** Types **/
enum class PIN_MODE : unsigned int {
    INPUT = 0x000,
    OUTPUT = 0x001,
    ALT0 = 0x100,
    ALT1 = 0x101,
    ALT2 = 0x110,
    ALT3 = 0x111,
    ALT4 = 0x011,
    ALT5 = 0x010
};

enum class PIN_LEVEL : unsigned int {
    LOW = 0x0,
    HIGH = 0x1
};


/**
 * Library main class.
 * Handles GPIO manipulations
 */
class GPIO {
    private:
        Bcm2835Periph peripheral{BCM_GPIO_BASE};   // Peripheral handler
        volatile uint32_t* p_base{nullptr};  // Peripheral memory base pointer;

        /**
         * Used to access a certain registry
         * @param off offset in memory of the registry
         * @retrun a reference to the registry
         */
        constexpr volatile uint32_t& r(uint32_t off) const;

        /**
         * Type conversion from PIN_MODE to unsigned integer
         * @param mode pin mode
         * @return the corresponding integer
         */
        constexpr unsigned int pinModeToInt(PIN_MODE mode) const;

        /**
         * Type conversion from PIN_MODE to unsigned integer
         * @param lev pin level
         * @return the corresponding integer
         */
        constexpr unsigned int pinLevelToInt(PIN_LEVEL lev) const;

    public:
        /**
         * Constructors and operators
         */
        GPIO() = default;
        ~GPIO() = default;
        GPIO(GPIO&) = delete;
        GPIO(const GPIO&) = delete;
        GPIO operator=(GPIO&) = delete;
        GPIO operator=(const GPIO&) = delete;
        GPIO(GPIO&&) = default;
        GPIO& operator=(GPIO&&) = default;

        /**
         * Opens the GPIO peripheral
         * @retrun true on success, false on failure
         */
        bool connect(void);

        /**
         * Closes the GPIO peripheral
         * @return true on success, false on failure
         */
        bool disconnect(void);

        /**
         * Changes the function of a pin
         * @param pin pin number
         * @param mode pin mode
         */
        void pinMode(unsigned int pin, PIN_MODE mode) const;

        /**
         * Sets a pin to HIGH
         * @param pin pin number
         */
        void pinUp(unsigned int pin) const;

        /**
         * Sets a pin to LOW
         * @param pin pin number
         */
        void pinDown(unsigned int pin) const;

        /**
         * Read the value of a pin
         * @param pin pin number
         * @return pin value
         */
        unsigned int pinLev(unsigned int pin) const;

        /**
         * Write a value to a pin
         * @param pin pin number
         * @param lev value
         */
        void digitalWrite(unsigned int pin, PIN_LEVEL lev) const;

        /**
         * Read a value from a pin
         * @param pin pin number
         * @return pin value
         */
        unsigned int digitalRead(unsigned int pin) const;
};