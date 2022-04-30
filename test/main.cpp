#include <iostream>
#include <thread>

#include <RPI-GPIO.h>

using namespace rpigpio;
using namespace std::chrono_literals;

int main(const int argc, char** argv)
{
	try {
		GPIO gpio{};
		try {
			gpio.connect();
		} catch (const std::exception e) {
			std::cout << e.what() << "\nError code : " << e.what() << std::endl;
			return 1;
		}

		const char readPin = 2;
		const char writePin = 27;

		gpio.reset();
		gpio.pinMode(readPin, PIN_MODE::INPUT);
		gpio.pinMode(writePin, PIN_MODE::OUTPUT);

		std::cout << gpio.digitalRead(readPin) << std::endl;

		gpio.digitalWrite(writePin, false);

		std::this_thread::sleep_for(1s);

		gpio.digitalWrite(writePin, true);

		return 0;
	} catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;
		return 1;
	} catch (...) {
		std::cerr << "An undefined exception occurred!" << std::endl;
		return 1;
	}
}
