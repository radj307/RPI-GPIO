#include <iostream>
#include <unistd.h>
#include <RPI-GPIO/RPI-GPIO.h>

int main(int argc, char const *argv[]) {
    GPIO gpio{};
    try {
        gpio.connect();
    } catch (Exception e) {
        std::cout << e.what() << "\nError code : " << e.error() << std::endl;
        return 1;
    }

    const char readPin = 2;
    const char writePin = 27;

    gpio.reset();
    gpio.pinMode(readPin, PIN_MODE::INPUT);
    gpio.pinMode(writePin, PIN_MODE::OUTPUT);

    std::cout << gpio.digitalRead(readPin) << std::endl;
    gpio.digitalWrite(writePin, PIN_LEVEL::LOW);
    sleep(1);
    gpio.digitalWrite(writePin, PIN_LEVEL::HIGH);

    return 0;
}
