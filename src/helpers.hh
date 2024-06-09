#pragma once

#include <cstdint>
#include <iosfwd>
#include <iostream>
#include <limits>
#include <string.h>

#include "strtools.hh"

using std::cout, std::cin, std::endl;

namespace helpers {
	// Check if the captured value is invalid.
	bool isCapturedValueInvalid() {
		if( cin.fail() ) {
			// Clear the error flags so we can use `cin` again.
			cin.clear();
			// Ignore invalid input.
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return true;
		}
		return false;
	}

	// Check if the value is out of bounds.
	bool isOutOfBounds(const int32_t& value, const int32_t& x, const int32_t& y) {
		return ( value < x or value > y );
	}

	// "Clear" the console.
	void clearScr() {
		cout << "\x1B[2J\x1B[H";
		cout.flush();
	}

	// Captures the value from the console, if the value is '/exit' returns 0
	int32_t captureAndCheck(str_p& s, const uint64_t& size) {
		// Capture the next user input.
		cin.getline(s.get(), size);
		// Check if the user wants to exit.
		return strcmp(s.get(), "/exit");
	}
}
