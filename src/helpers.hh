#pragma once

#include <cstdint>
#include <iosfwd>
#include <iostream>
#include <limits>
#include <string.h>

#include "strtools.hh"
#include <stdexcept>

using std::cout, std::cin, std::endl;

namespace helpers {
	/***
	 * @brief Checks if the captured value from standard input is invalid.
	 *
	 * This function checks if the last input operation on `cin` failed
	 * (e.g., due to non-numeric input). If it fails, it performs the following:
	 *   - Clears the error flags from `cin` to allow further input.
	 *   - Ignores the remaining invalid input in the stream up to the next newline.
	 *
	 * @return `true` if the captured value was invalid, `false` otherwise.
	 */
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

	/***
	 * @brief Checks if a value is outside the specified bounds.
	 *
	 * This function determines if the given `value` is less than `x`
	 * or greater than `y`.
	 *
	 * @param value The value to check.
	 * @param x The lower bound.
	 * @param y The upper bound.
	 *
	 * @return `true` if the value is outside the bounds, `false` otherwise.
	 */
	bool isOutOfBounds(const int32_t& value, const int32_t& x, const int32_t& y) {
		return ( value < x or value > y );
	}

	/***
	 * @brief Clears the console screen.
	 *
	 * This function sends escape sequences to the console to clear the screen
	 * and move the cursor to the top-left corner. This functionality is platform-specific
	 * and might not work on all terminals.
	 */
	void clearScr() {
		cout << "\x1B[2J\x1B[H";
		cout.flush();
	}

	/***
	 * @brief Checks captured user input and handles potential errors.
	 *
	 * This function first calls `isCapturedValueInvalid` to check if there were any errors
	 * during the input process. If `isCapturedValueInvalid` returns `true`, it throws a
	 * `std::runtime_error` with a descriptive message. Otherwise, it checks if the captured
	 * string is equal to "/exit".
	 *
	 * @param s A pointer to a `char` object to store the captured input.
	 *
	 * @return  - 0 if the captured string is "/exit".
	 *          - 1 if the captured string is not "/exit" and there were no errors during input.
	 *
	 * @throws std::runtime_error if there was an error while capturing the input or if the
	 * captured string exceeds the maximum size.
	 */
	int32_t checkCapturedValue(const char* s) {
		if( isCapturedValueInvalid() ) {
			throw std::runtime_error("There was an error while handling the string.");
		}
		// Check if the user wants to exit.
		return ( strcmp(s, "/exit") == 0 ) ? 0 : 1;
	}
}
