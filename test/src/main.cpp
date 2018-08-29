#include <iostream>
#include <RPI-GPIO/RPI-GPIO.h>

int main(int argc, char const *argv[]) {
    GPIO gpio{};
    try {
        gpio.connect();
    } catch (Exception e) {
        std::cout << e.what() << "\n";
    }
    return 0;
}
