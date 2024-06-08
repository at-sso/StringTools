#pragma once

#include <cstdint>
#include <iosfwd>
#include <iostream>
#include <limits>

namespace helpers {
	// Check if the captured value is invalid.
	bool isCapturedValueInvalid() {
		if( cin.fail() ) {
			// Clear the error flags so we can use `cin` again.
			cin.clear();
			// Ignore invalid input
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return true;
		}
		return false;
	}

	bool isOutOfBounds(const int32_t& value, const int32_t& x, const int32_t& y) {
		return ( value < x or value > y );
	}
}
