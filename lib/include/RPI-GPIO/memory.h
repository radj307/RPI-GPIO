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

#include <stdint.h>

#pragma once


/* Constants */
constexpr uint32_t BCM_PERIPH_BASE = 0x20000000;
constexpr uint32_t BCM_GPIO_BASE = (BCM_PERIPH_BASE + 0x200000);
constexpr uint32_t PAGE_SIZE = (4 * 1024);

/**
 * This class handles access to a peripheral by mapping physical memory to the
 * process user memory space
 */

class Bcm2835Periph {
    private:
        const uint32_t addr;         // Physical base address
        int mem_fd;                 // /dev/mem file descriptor
        void* mapped;               // Pointer to mapped mémory in the iser space
        volatile uint32_t* base;    // Public pointer to mapped memory

        /**
         * Opens /dev/mem
         * @return tru on success, false on failure
         */
        bool openMem(void);

        /**
         * Closes /dev/mem
         */
        void closeMem(void);

    public:
        /**
         * Class constructor
         * @param addr_p Base address of the peripheral memory
         */
        Bcm2835Periph(uint32_t addr_p = 0);

        /**
         * Destructor
         */
        ~Bcm2835Periph();

        /**
         * Maps the peripheral memory into the user space memory
         * @return true on success, false on failure
         */
        bool map(void);

        /**
         * Unmaps the memory
         */
        void unmap(void);

        /**
         * Getter for the base pointer
         * @return pointer to the first 32-bit integer of the mapped memory
         */
        volatile uint32_t* getBase(void);
};