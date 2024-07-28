/**
 * @file helpers.hh
 * @author Ian Hylton
 * @brief Utilities for input handling and console management.
 * @version 1.0.1
 * @date 2024-07-28
 *
 * @copyright Copyright (c) zperk 2024
 *
 */

#pragma once

#include <cstdint>
#include <iosfwd>
#include <iostream>
#include <limits>
#include <string.h>

using std::cout, std::cin, std::cerr, std::endl;

/**
 * @namespace helpers
 * @brief Utility functions for input handling and console management.
 *
 * This namespace provides a set of utility functions for handling standard input
 * errors, checking bounds of values, clearing the console screen, and managing user
 * input with overflow and exit command handling.
 */
namespace helpers {
	/**
	 * @brief Checks if the captured value from standard input is invalid.
	 *
	 * This function checks if the last input operation on `cin` failed
	 * (e.g., due to non-numeric input). If it fails, it performs the following:
	 *   - Clears the error flags from `cin` to allow further input.
	 *   - Ignores the remaining invalid input in the stream up to the next newline.
	 *
	 * @return `true` if the captured value was invalid, `false` otherwise.
	 *
	 * @note Example usage:
	 * @code
	 * int value;
	 * std::cin >> value;
	 * if (helpers::isCapturedValueInvalid()) {
	 *     std::cout << "Invalid input. Please enter a numeric value.\n";
	 * }
	 * @endcode
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

	/**
	 * @brief "Clears" the console screen.
	 *
	 * This function sends escape sequences to the console to clear the screen
	 * and move the cursor to the top-left corner. This functionality is platform-specific
	 * and might not work on all terminals.
	 *
	 * @note Example usage:
	 * @code
	 * helpers::clearScr();
	 * std::cout << "Screen cleared.\n";
	 * @endcode
	 */
	void clearScr() {
		cout << "\x1B[2J\x1B[H";
		cout.flush();
	}

	/**
	 * @brief Handles user input, checks for exit command, and handles overflow.
	 *
	 * This function reads user input from the standard input stream until a newline
	 * character is encountered or the buffer is full. It checks if the user input
	 * is the exit command "/exit". If the input exceeds the buffer size, it truncates
	 * the input and clears the remaining characters in the input stream.
	 *
	 * @param input Pointer to the character array where the input will be stored.
	 * @param size The size of the input buffer.
	 * @return `true` if the input is the exit command "/exit".
	 * @return `false` otherwise.
	 *
	 * @note Example usage:
	 * @code
	 * const int32_t bufferSize = 100;
	 * char input[bufferSize];
	 * bool exit = helpers::userInputHandler(input, bufferSize);
	 * if (exit) {
	 *     std::cout << "Exit command received.\n";
	 * } else {
	 *     std::cout << "You entered: " << input << "\n";
	 * }
	 * @endcode
	 */
	bool userInputHandler(char* input, int32_t size) {
		char ch = 0;
		int32_t chCount = 0;

		// Check the input of the user one by one.
		while( ( ch = cin.get() ) != '\n' && chCount < size - 1 ) {
			input[chCount++] = ch;
		}
		input[chCount] = '\0';  // Null-terminate the string

		// Check if the user wants to exit.
		if( strcmp(input, "/exit") == 0 ) {
			return true;
		}

		// Handle overflow if input exceeds maximum length.
		if( chCount == size - 1 ) {
			// Clear remaining input.
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cerr << "Warning: Input truncated to " << size - 1 << " characters.\n";
		}

		return false;
	}
}
