#include "rsc/version.h"

#include <ParamsAPI2.hpp>
#include <TermAPI.hpp>

#include <RPI-GPIO.h>

#define PROGRAM_NAME "gpiocli"

struct Help {

	friend std::ostream& operator<<(std::ostream& os, const Help& h)
	{
		return os
			<< "USAGE:\n"
			<< "  " << PROGRAM_NAME << " <OPTIONS>" << '\n'
			<< '\n'
			<< "  The default action when a pin number is specified without any options\n"
			<< "   is to query its current state, which is printed as either a 1 or a 0.\n"
			<< '\n'
			<< "OPTIONS:\n"
			<< "  -h, --help                  Show this help display, then exit." << '\n'
			<< "  -v, --version               Show the current version number, then exit." << '\n'
			<< "  -q, --quiet                 Minimize the amount of console output for scripts." << '\n'
			<< "  -I, --on, --high '<#>'      Set the specified pin to HIGH (ON)." << '\n'
			<< "  -O, --off, --low '<#>'      Set the specified pin to LOW (OFF)." << '\n'
			<< "  -Q, -G, --get '<#>'         Get the current state of the specified pin." << '\n'
			<< "  -R, -r, --reset             Resets all GPIO pins to default before processing other options, if present." << '\n'
			<< "  -s, --set '<<#>:<MODE>>'    Sets the mode of pin '<#>' to '<MODE>', which can be any of the following values:" << '\n'
			<< "                               |  Mode  | Description |" << '\n'
			<< "                               |--------|-------------|" << '\n'
			<< "                               | INPUT  | GPIO Input  |" << '\n'
			<< "                               | OUTPUT | GPIO Output |" << '\n'
			<< "                               | ALT0   | ?           |" << '\n'
			<< "                               | ALT1   | ?           |" << '\n'
			<< "                               | ALT2   | ?           |" << '\n'
			<< "                               | ALT3   | ?           |" << '\n'
			<< "                               | ALT4   | ?           |" << '\n'
			<< "                               | ALT5   | ?           |" << '\n'
			<< '\n'
			<< "ORDER OF OPERATIONS:\n"
			<< "  Steps are only executed if the associated operation was specified." << '\n'
			<< "   1.  Reset GPIO state" << '\n'
			<< "   2.  Set specified pin mode(s)" << '\n'
			<< "   3.  Set specified pin(s) to high" << '\n'
			<< "   4.  Set specified pin(s) to low" << '\n'
			<< "   5.  Query specified pin state(s)" << '\n'
			;
	}
};

using pin_t = unsigned int;

inline std::optional<rpigpio::PIN_MODE> StringToPinMode(const std::string& mode)
{
	std::string modestr{ str::strip(str::tolower(mode), " \t\r\n\v") };

	if (str::equalsAny(modestr, "i", "in", "input"))
		return rpigpio::PIN_MODE::INPUT;
	else if (str::equalsAny(modestr, "o", "out", "output"))
		return rpigpio::PIN_MODE::OUTPUT;
	else if (str::equalsAny(modestr, "0", "alt0"))
		return rpigpio::PIN_MODE::ALT0;
	else if (str::equalsAny(modestr, "1", "alt1"))
		return rpigpio::PIN_MODE::ALT1;
	else if (str::equalsAny(modestr, "2", "alt2"))
		return rpigpio::PIN_MODE::ALT2;
	else if (str::equalsAny(modestr, "3", "alt3"))
		return rpigpio::PIN_MODE::ALT3;
	else if (str::equalsAny(modestr, "4", "alt4"))
		return rpigpio::PIN_MODE::ALT4;
	else if (str::equalsAny(modestr, "5", "alt5"))
		return rpigpio::PIN_MODE::ALT5;
	return std::nullopt;
}

int main(const int argc, char** argv)
{
	enum class Color : char {
		PIN,
		VALUE,
	};
	color::palette<Color> colors{
		std::make_pair(Color::PIN, color::setcolor::cyan),
		std::make_pair(Color::VALUE, color::setcolor::yellow)
	};

	try {
		opt::ParamsAPI2 args{ argc, argv, 'I', "on", "high", 'O', "off", "low", 'Q', 'G', "get", 's', "set" };

		const bool quiet{ args.check_any<opt::Flag, opt::Option>('q', "quiet") };
		colors.setEnabled(!quiet);


		if (const bool empty{ args.empty() }; empty || args.check_any<opt::Flag, opt::Option>('h', "help")) {
			std::cout << Help();
			if (empty)
				throw make_exception("No arguments specified! ( Nothing to do. )");
			return 0;
		}
		else if (args.check_any<opt::Flag, opt::Option>('v', "version")) {
			if (!quiet)
				std::cout << PROGRAM_NAME << "  v";
			std::cout << gpiocli_VERSION_EXTENDED << std::endl;
			return 0;
		}

		rpigpio::GPIO gpio;
		if (!gpio.connect())
			throw make_exception("Failed to connect to the GPIO peripheral!");

		// -R, -r, --reset
		if (args.check_any<opt::Flag, opt::Option>('R', 'r', "reset"))
			gpio.reset();

		// -s, --set
		for (const auto& arg : args.typegetv_all<opt::Flag, opt::Option>('s', "set")) {
			const auto& [pinstr, modestr] { str::split(arg, ':') };

			const auto& pinopt{ str::optional::stoui(pinstr) };
			const auto& modeopt{ StringToPinMode(modestr) };

			if (!pinopt.has_value()) {
				std::cerr << colors.get_warn() << "Invalid Pin Number: '" << pinstr << "'" << std::endl;
				continue;
			}
			else if (!modeopt.has_value()) {
				std::cerr << colors.get_warn() << "Invalid Mode: '" << modestr << "'" << std::endl;
				continue;
			}

			gpio.pinMode(pinopt.value(), modeopt.value());
		}

		// -I, --on, --high
		for (const auto& pinstr : args.typegetv_all<opt::Flag, opt::Option>('I', "on", "high")) {
			const auto& pinopt{ str::optional::stoui(pinstr) };

			if (pinopt.has_value())
				gpio.digitalWrite(pinopt.value(), true);
			else
				std::cerr << colors.get_warn() << "Invalid Pin Number: '" << pinstr << "'" << std::endl;
		}

		// -O, --off, --low
		for (const auto& pinstr : args.typegetv_all<opt::Flag, opt::Option>('O', "off", "low")) {
			const auto& pinopt{ str::optional::stoui(pinstr) };

			if (pinopt.has_value())
				gpio.digitalWrite(pinopt.value(), false);
			else
				std::cerr << colors.get_warn() << "Invalid Pin Number: '" << pinstr << "'" << std::endl;
		}

		// -Q, -G, --get
		const auto& queryPins{ args.typegetv_all<opt::Flag, opt::Option>('Q', 'G', "get") };
		const auto& longest{ str::longestLength(queryPins) };
		for (const auto& pinstr : queryPins) {
			const auto& pinopt{ str::optional::stoui(pinstr) };

			if (pinopt.has_value()) {
				if (!quiet)
					std::cout << colors(Color::PIN) << pinstr << colors() << indent(longest - pinstr.size()) << " = ";
				std::cout << colors(Color::VALUE) << gpio.pinLev(pinopt.value()) << colors() << '\n';
			}
			else
				std::cerr << colors.get_warn() << "Invalid Pin Number: '" << pinstr << "'" << std::endl;
		}

		return 0;
	} catch (const std::exception& ex) {
		std::cerr << colors.get_fatal() << ex.what() << std::endl;
		return 1;
	} catch (...) {
		std::cerr << colors.get_fatal() << "An undefined exception occurred!" << std::endl;
		return 1;
	}
}
