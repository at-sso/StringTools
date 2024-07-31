/**
 * @file strutil.hh (former helpers.hh)
 * @author Ian Hylton
 * @brief Utilities for input handling and console management.
 * @version 1.0.3
 * @date 2024-07-30
 *
 * @copyright Copyright (c) zperk 2024
 *
 */


#pragma once

#include "strutilhelper.hh"
#include <cctype>
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <string.h>


using std::cout, std::cin, std::cerr, std::endl, std::flush;
using std::string, std::to_string;
using std::unique_ptr, std::shared_ptr;
using std::make_unique, std::make_shared;

/**
 * @namespace strUtil (former name: helpers)
 * @brief Utility functions for input handling and console management.
 *
 * This namespace provides a set of utility functions for handling standard input
 * errors, checking bounds of values, clearing the console screen, and managing user
 * input with overflow and exit command handling.
 */
namespace strUtil {
	/**
	 * @brief "Clears" the console screen.
	 *
	 * This function sends escape sequences to the console to clear the screen
	 * and move the cursor to the top-left corner. This functionality is platform-specific
	 * and might not work on all terminals.
	 *
	 * @note Example usage:
	 * @code
	 * strUtil::clearScr();
	 * cout << "Screen 'cleared'.\n";
	 * @endcode
	 */
	void clearScr() noexcept {
		cout << "\x1B[2J\x1B[H" << flush;
	}

	/**
	 * @brief Converts a string to lowercase (in-place).
	 *
	 * This function modifies the input string by converting all uppercase characters
	 * to lowercase. It iterates over each character and applies the `tolower` function.
	 *
	 * @param str The input string to be modified.
	 *
	 * @note Modifies the original string.
	 *
	 * @note Example usage:
	 * @code
	 * char myString[] = "Hello, World!";
	 * toLower(myString); // myString will be "hello, world!"
	 * @endcode
	 */
	void toLower(char* src) {
		if( __StrUtilExtra.checkInvalidCharPtr(src, "toLower(char*)") ) return;
		__StrUtilExtra.toSomething(src, tolower);
	}

	/**
	 * @brief Converts a string to lowercase.
	 *
	 * This function creates a new string that is a lowercase version of the input string.
	 * It uses the `tolower` function to convert each character to lowercase.
	 *
	 * @param str The input string to be converted.
	 * @return A new string with all characters converted to lowercase.
	 *
	 * @note Example usage:
	 * @code
	 * const char* myString = "Hello, World!";
	 * const char* lowerString = toLower(myString); // lowerString will be "hello, world!"
	 * @endcode
	 */
	const char* toLower(const char* src) {
		if( __StrUtilExtra.checkInvalidCharPtr(src, "toLower(const char*)") ) return "";
		char* s = (char*) "";
		strcpy(s, src);
		toLower(s);
		return s;
	}

	/**
	 * @brief Converts a string to uppercase (in-place).
	 *
	 * This function modifies the input string by converting all lowercase characters
	 * to uppercase. It iterates over each character and applies the `toupper` function.
	 *
	 * @param str The input string to be modified.
	 *
	 * @note Modifies the original string.
	 *
	 * @note Example usage:
	 * @code
	 * char myString[] = "Hello, World!";
	 * toUpper(myString); // myString will be "HELLO, WORLD!"
	 * @endcode
	 */
	void toUpper(char* src) {
		if( __StrUtilExtra.checkInvalidCharPtr(src, "toUpper(char*)") ) return;
		__StrUtilExtra.toSomething(src, toupper);
	}

	/**
	 * @brief Converts a string to uppercase.
	 *
	 * This function creates a new string that is an uppercase version of the input string.
	 * It uses the `toupper` function to convert each character to uppercase.
	 *
	 * @param str The input string to be converted.
	 * @return A new string with all characters converted to uppercase.
	 *
	 * @note Example usage:
	 * @code
	 * const char* myString = "Hello, World!";
	 * const char* upperString = toUpper(myString); // upperString will be "HELLO, WORLD!"
	 * @endcode
	 */
	const char* toUpper(const char* src) {
		if( __StrUtilExtra.checkInvalidCharPtr(src, "toUpper(const char*)") ) return "";
		char* s = (char*) "";
		strcpy(s, src);
		toUpper(s);
		return s;
	}

	/**
	 * @brief Creates a `std::unique_ptr<char[]>` from a const char* source.
	 *
	 * This function takes a C-style string (`const char*`) and creates a copy of it
	 * in a `std::unique_ptr<char[]>`. This is useful for managing dynamic C-strings
	 * with automatic memory management, preventing memory leaks.
	 *
	 * @param src The source C-string to be copied.
	 * @return A `unique_ptr<char[]>` containing a copy of the source string.
	 *
	 * @note The returned unique_ptr will own the dynamically allocated memory
	 * and will automatically release it when it goes out of scope.
	 *
	 * @note Example usage:
	 * @code
	 * auto myString = makeUniqueStr("Hello, World!");
	 * @endcode
	 */
	unique_ptr<char[]> makeUniqueStr(const char* src) {
		return __StrUtilExtra.makeSmartPtr<unique_ptr<char[]>>(src);
	}

	/**
	 * @brief Creates a `std::shared_ptr<char[]>` from a const char* source.
	 *
	 * This function takes a C-style string (`const char*`) and creates a copy of it
	 * in a `std::shared_ptr<char[]>`. This is useful for managing dynamic C-strings
	 * with automatic memory management, preventing memory leaks.
	 *
	 * @param src The source C-string to be copied.
	 * @return A `shared_ptr<char[]>` containing a copy of the source string.
	 *
	 * @note The returned shared_ptr will own the dynamically allocated memory
	 * and will automatically release it when it goes out of scope.
	 *
	 * @note Example usage:
	 * @code
	 * auto myString = makeUniqueStr("Hello, World!");
	 * @endcode
	 */
	shared_ptr<char[]> makeSharedStr(const char* src) {
		return __StrUtilExtra.makeSmartPtr<shared_ptr<char[]>>(src);
	}

	unique_ptr<char[]> makeUniqueStrArray(uint64_t size) {
		return unique_ptr<char[]>(new char[size]);
	}

	shared_ptr<char[]> makeSharedStrArray(uint64_t size) {
		return shared_ptr<char[]>(new char[size]);
	}

	/**
	 * @brief Checks if the captured value from standard input is invalid.
	 *
	 * This function checks if the last input operation on `cin` failed
	 * (e.g., due to non-numeric input). If it fails, it performs the following:
	 *   - Clears the error flags from `cin` to allow further input.
	 *   - Ignores the remaining invalid input in the stream up to the next newline.
	 *
	 * @param value An optional character to ignore. Default is an escape character (`\n`).
	 * @param force Force ignoring input (discards valid input).
	 * @return `true` if the captured value was invalid, `false` otherwise.
	 *
	 * @note Example usage:
	 * @code
	 * int value;
	 * std::cin >> value;
	 * if (strUtil::isCapturedValueInvalid()) {
	 *     std::cout << "Invalid input. Please enter a numeric value.\n";
	 * }
	 * @endcode
	 */
	bool isCapturedValueInvalid(char value = '\n', bool force = false) {
		// If `force` is enabled, ignore the captured value.
		if( force ) {
			__StrUtilExtra.log(
				"isCapturedValueInvalid(..., bool)", "Invalid input: " + value
			);
			__StrUtilExtra.ignoreCapturedValue(value);
			return true;
		}

		if( cin.fail() ) {
			__StrUtilExtra.log("isCapturedValueInvalid(char, ...)", "The stream failed.");
			// Clear the error flags so we can use `cin` again.
			cin.clear();
			// Ignore invalid input.
			__StrUtilExtra.ignoreCapturedValue(value);
			return true;
		}

		__StrUtilExtra.log("isCapturedValueInvalid(...)", "No errors.");
		return false;
	}

	static bool isCapturedValueInvalid(bool force) {
		return isCapturedValueInvalid('\n', force);
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
	 * bool exit = strUtil::userInputHandler(input, bufferSize);
	 * if (exit) {
	 *     cout << "Exit command received.\n";
	 * } else {
	 *     cout << "You entered: " << input << "\n";
	 * }
	 * @endcode
	 */
	bool userInputHandler(char* input, uint64_t size) {
		if( input == nullptr || size == 0 ) {
			__StrUtilExtra.log(
				"userInputHandler(...)",
				"Either a null `input` value (nullptr) was passed or the `size` is zero (0)."
			);
			return false;
		}

		char inputCharacter = 0;
		uint64_t inputCharacterCount = 0ull;

		// Avoids errors by ignoring escape characters in the stream.
		isCapturedValueInvalid(true);

		// Check the input of the user one by one.
		while( ( inputCharacter = cin.get() ) != '\n' && inputCharacterCount < size - 1 ) {
			input[inputCharacterCount++] = inputCharacter;
		}

		// Null-terminate the string
		if( inputCharacterCount < size )
			input[inputCharacterCount] = '\0';
		else input[size - 1] = '\0';

		// Check if the user wants to exit.
		if( strcmp(input, "/exit") == 0 ) {
			return true;
		}

		// Handle overflow if input exceeds maximum length.
		if( inputCharacterCount == size - 1 ) {
			// Clear remaining input.
			__StrUtilExtra.ignoreCapturedValue('\n');
			cerr << "Warning: Input truncated to " << size - 1 << " characters.\n";
		}

		return false;
	}
}
