/**
 * @file strutil.hh (former helpers.hh)
 * @author Ian Hylton
 * @brief Utilities for input handling and console management.
 * @version 1.0.2
 * @date 2024-07-30
 *
 * @copyright Copyright (c) zperk 2024
 *
 */

// This is (or must be) the first file to be linked after compilation.

#pragma once

#include <cctype>
#include <cstdint>
#include <iosfwd>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string.h>

/**
 * @brief Ignores invalid input from standard input.
 *
 * This function clears the error flags from `cin` and ignores remaining invalid input
 * up to the next newline. It is typically used after a failed input operation.
 *
 * @return `true` if the input was invalid, `false` otherwise.
 *
 * @note Example usage:
 * @code
 * int value;
 * std::cin >> value;
 * if (__ignoreCapturedValue('\n')) {
 *     std::cout << "Invalid input. Please enter a valid value.\n";
 * }
 * @endcode
 */
#define __ignoreCapturedValue(s) \
cin.ignore(std::numeric_limits<std::streamsize>::max(), s)

/**
 * @brief Checks for invalid inputs and throws an exception if the rule is violated.
 *
 * This function evaluates a given condition (rule) and throws a `std::out_of_range`
 * exception with a specified message if the condition is false. It is commonly used
 * to enforce constraints and validate inputs within other functions.
 *
 * @param rule The condition to be checked. If this condition evaluates to false, an exception is thrown.
 * @param msg The message to be included in the exception if the rule is violated.
 * @throws std::out_of_range if the rule is false.
 *
 * @note Example usage:
 * @code
 * __checkLogicErrors(index < arraySize, "Index out of range");
 * @endcode
 */
#define __checkLogicErrors(rule, msg) \
if( rule )                            \
throw std::out_of_range(msg)

/**
 * @brief Creates a smart pointer to a dynamically allocated array of characters.
 *
 * This macro defines a variable `smartStr` as a smart pointer to a dynamically allocated
 * array of characters with a specified length. The pointer is created using the provided
 * smart pointer creation function (e.g., `std::make_shared` or `std::make_unique`).
 * It is useful for managing the lifetime of dynamically allocated character arrays,
 * ensuring proper deallocation.
 *
 * @param len The length of the character array to be allocated.
 * @param _make The smart pointer creation function (e.g., `std::make_shared` or `std::make_unique`).
 *
 * @note Example usage:
 * @code
 * size_t size;
 * smart_ptr __makeSmartStringPtr(size, std::make_shared);
 * std::cout << smartStr.get();
 * @endcode
 */
#define __makeSmartStringPtr(len, _make) \
<char[]> smartStr = _make<char[]>(static_cast<size_t>( len ) + 1)

/**
 * @brief Converts a string to something (in-place).
 *
 * This function modifies the input string by converting all characters to something.
 * It iterates over each character and applies the `tolower` function.
 *
 * @param str The input string to be modified.
 *
 * @note Modifies the original string.
 *
 * @note Example usage:
 * @code
 * std::string myString = "Hello, World!";
 * __toSomething(myString); // `myString` will be something, I don't know
 * @endcode
 */
#define __toSomething(s, f) \
for( int i = 0; s[i]; i++ ) \
s[i] = f((unsigned char) s[i])

using std::cout, std::cin, std::cerr, std::endl, std::flush;
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
	void clearScr() {
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
	void toLower(char* str) {
		__toSomething(str, tolower);
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
	const char* toLower(const char* str) {
		char* s = "";
		strcpy(s, str);
		// This *will* call the `void` overload.
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
	void toUpper(char* str) {
		__toSomething(str, toupper);
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
	const char* toUpper(const char* str) {
		char* s = "";
		strcpy(s, str);
		// This *will* call the `void` overload.
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
	static unique_ptr<char[]> makeUniqueStr(const char* src) noexcept {
		unique_ptr __makeSmartStringPtr(strlen(src), make_unique);
		strcpy(smartStr.get(), src);
		return smartStr;
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
	static shared_ptr<char[]> makeSharedStr(const char* src) noexcept {
		shared_ptr __makeSmartStringPtr(strlen(src), make_shared);
		strcpy(smartStr.get(), src);
		return smartStr;
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
		if( cin.fail() ) {
			// Clear the error flags so we can use `cin` again.
			cin.clear();
			// Ignore invalid input.
			__ignoreCapturedValue(value);
			return true;
		}
		return false;
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
			__ignoreCapturedValue('\n');
			cerr << "Warning: Input truncated to " << size - 1 << " characters.\n";
		}

		return false;
	}
}
