#include <iostream>
#include <RPI-GPIO/RPI-GPIO.h>

int main(int argc, char const *argv[]) {
    GPIO gpio{};
    if (!gpio.connect()) {
        std::cout << "Couldn't connect to GPIO\n";
    }
    return 0;
}
