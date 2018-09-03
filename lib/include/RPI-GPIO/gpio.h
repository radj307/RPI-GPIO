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
constexpr uint32_t GPFSEL[] = { 0x0, 0x4, 0x8, 0xc, 0x10, 0x14 };

constexpr uint32_t GPSET0 = 0x1c;
constexpr uint32_t GPSET1 = 0x20;

constexpr uint32_t GPCLR0 = 0x28;
constexpr uint32_t GPCLR1 = 0x2c;

constexpr uint32_t GPLEV0 = 0x34;
constexpr uint32_t GPLEV1 = 0x38;

constexpr uint32_t GPEDS0 = 0x40;
constexpr uint32_t GPEDS1 = 0x44;

constexpr uint32_t GPREN0 = 0x4c;
constexpr uint32_t GPREN1 = 0x50;

constexpr uint32_t GPFEN0 = 0x54;
constexpr uint32_t GPFEN1 = 0x5c;

constexpr uint32_t GPHEN0 = 0x64;
constexpr uint32_t GPHEN1 = 0x68;

constexpr uint32_t GPLEN0 = 0x70;
constexpr uint32_t GPLEN1 = 0x74;

constexpr uint32_t GPAREN0 = 0x7c;
constexpr uint32_t GPAREN1 = 0x80;

constexpr uint32_t GPAFEN0 = 0x88;
constexpr uint32_t GPAFEN1 = 0x8c;

constexpr uint32_t GPPUD = 0x94;
constexpr uint32_t GPPUDCLK0 = 0x98;
constexpr uint32_t GPPUDCLK1 = 0x9c;


/** Types **/
enum class PIN_MODE : unsigned int {
    INPUT = 0b000,
    OUTPUT = 0b001,
    ALT0 = 0b100,
    ALT1 = 0b101,
    ALT2 = 0b110,
    ALT3 = 0b111,
    ALT4 = 0b011,
    ALT5 = 0b010
};

enum class PIN_LEVEL : unsigned int {
    LOW = 0b0,
    HIGH = 0b1
};


enum class PUD : unsigned int {
    OFF = 0b00,
    PD = 0b01,
    PU = 0b10
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
        volatile uint32_t& r(const uint32_t off) const;

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

        /**
         * Type conversion from PUD to unsigned integer
         * param pud Pull up/down state
         * @return the corresponding value
         */
        constexpr unsigned int pudToInt(PUD pud) const;

        /**
         * Enables the PUD Clock on a pin
         * @param pin pin number
         */
        void enablePudClock(unsigned int pin) const;

        /**
         * Disables the PU Clock on a pin
         * @param pin pin number
         */
        void disablePudClock(unsigned int pin) const;

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

        /**
         * Enables or disables internal pull-up/down resistors on a pin
         * @param pin pin number
         * @pud State : Off, Pull-up or Pull down
         */
        void pullUpDown(unsigned int pin, PUD pud) const;

        /**
         * resets the pull up/down resistors on all GPIO pins
         */
        void resetPullUpDown() const;

        /**
         * Resets all GPIO parameters
         */
        void reset(void) const;
};