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

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>

#include "RPI-GPIO/memory.h"


/* Public methods */

Bcm2835Periph::Bcm2835Periph(uint32_t addr_p) : addr{addr_p} {
}

Bcm2835Periph::~Bcm2835Periph() {
    if (mapped != nullptr) {
        unmap();
    }

    if (mem_fd != 0) {
        closeMem();
    }
}

bool Bcm2835Periph::map() {
    if (!openMem()) return false;

    mapped = mmap(
        nullptr,
        PAGE_SIZE,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        mem_fd,
        addr
    );

    if (mapped == nullptr) return false;
    else base = reinterpret_cast<volatile uint32_t*> (mapped);

    return true;
}

void Bcm2835Periph::unmap() {
    munmap(mapped, PAGE_SIZE);
    mapped = nullptr;
    base = nullptr;
    closeMem();
}

volatile uint32_t* Bcm2835Periph::getBase() {
    if (base) return base;
    else return nullptr;
}





/* Private methods */
bool Bcm2835Periph::openMem() {
    return ((mem_fd = open("/dev/mem", O_RDWR | O_SYNC)) >= 0);
}

void Bcm2835Periph::closeMem() {
    close(mem_fd);
    mem_fd = 0;
}