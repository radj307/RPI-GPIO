#include <iostream>
#include <unistd.h>
#include <RPI-GPIO/RPI-GPIO.h>

int main(int argc, char const *argv[]) {
    GPIO gpio{};
    try {
        gpio.connect();
    } catch (Exception e) {
        std::cout << e.what() << "\nError code : " << e.error() << "\n";
        return 1;
    }

    const char pin = 2;

    gpio.pinMode(pin, PIN_MODE::OUTPUT);
    for (int i = 0; i < 5; i++) {
        gpio.pinDown(pin);
        sleep(1);
        gpio.pinUp(pin);
        sleep(1);
    }
    return 0;
}
