/**
 * @file strutil.hh (former helpers.hh)
 * @author Ian Hylton
 * @brief Utilities for input handling and console management.
 * @version 1.0.4
 * @date 2024-08-02
 *
 * @copyright Copyright (c) zperk 2024
 *
 */


#pragma once

#include "strlogger.hh"
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

#define uniqueStr std::unique_ptr<char[]>
#define sharedStr std::shared_ptr<char[]>

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
		if( !__strToolsLogger.loggerStatus() ) {
			_strLogger("clearScr()", "Clear screen");
			cout << "\x1B[2J\x1B[H" << flush;
		}
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
		_strLogger("toLower()", src);
		__StrUtilExtra.toSomething(src, tolower);
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
		_strLogger("toUpper()", src);
		__StrUtilExtra.toSomething(src, toupper);
	}

	/**
	 * @brief Creates a smart pointer to an array of the specified size.
	 *
	 * This template function takes a size and creates a smart pointer of the specified type,
	 * managing the memory allocation for an array of the given size.
	 *
	 * @tparam T The type of the smart pointer to create.
	 * @param size The size of the array to allocate.
	 * @return A smart pointer of type T containing the allocated array.
	 *
	 * @note Example usage:
	 * @code
	 * auto result = strUtil::makeSmartPtrArray<unique_ptr<char[]>>(10);
	 * // result will point to an array of 10 characters
	 * @endcode
	 */
	template<class T>
	static T makeSmartPtrArray(uint64_t size) noexcept {
		_strLogger("makeSmartPtrArray()", "creating smart string with size: " + to_string(size));
		if( size == 0 ) size = 1;
		return T(new char[size]);
	}

	/**
	 * @brief Creates a smart pointer from a C-string.
	 *
	 * This template function takes a C-string and creates a smart pointer of the specified type,
	 * managing the memory allocation and copying of the string.
	 *
	 * @tparam T The type of the smart pointer to create.
	 * @param src The source C-string to copy.
	 * @return A smart pointer of type T containing the copied string.
	 *
	 * @note Example usage:
	 * @code
	 * const char* source = "Example";
	 * auto result = strUtil::makeSmartStr<unique_ptr<char[]>>(source);
	 * // result will contain "Example"
	 * @endcode
	 */
	template<class T>
	static T makeSmartStr(const char* src) noexcept {
		_strLogger("makeSmartStr()", "creating smart string using: " + to_string(*src));
		// If the pointer is a nullptr, return an empty string.
		if( __StrUtilExtra.checkInvalidCharPtr(src, "makeSmartStr()") ) {
			return strUtil::makeSmartPtrArray<T>(1);
		}
		return __StrUtilExtra.makeSmartPtr<T>(src);
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
	 * auto lowerString = toLower(myString); // lowerString will be "hello, world!"
	 * @endcode
	 */
	uniqueStr toLower(const char* src) {
		if( __StrUtilExtra.checkInvalidCharPtr(src, "toLower(const char*)") ) {
			return strUtil::makeSmartPtrArray<uniqueStr>(1);
		}
		uniqueStr s(new char[sizeof(src)]);
		strcpy(s.get(), src);
		toLower(s.get());
		return s;
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
	 * auto upperString = toUpper(myString); // upperString will be "HELLO, WORLD!"
	 * @endcode
	 */
	uniqueStr toUpper(const char* src) {
		if( __StrUtilExtra.checkInvalidCharPtr(src, "toUpper(const char*)") ) {
			return strUtil::makeSmartPtrArray<uniqueStr>(1);
		}
		uniqueStr s(new char[sizeof(src)]);
		strcpy(s.get(), src);
		toUpper(s.get());
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
	static uniqueStr makeUniqueStr(const char* src) {
		return makeSmartStr<uniqueStr>(src);
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
	static sharedStr makeSharedStr(const char* src) {
		return makeSmartStr<sharedStr>(src);
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
			__strToolsLogger.log(__StrToolsLogLvl::INFO,
				"isCapturedValueInvalid(..., bool): Invalid input: " + value
			);
			__StrUtilExtra.ignoreCapturedValue(value);
			return true;
		}

		if( cin.fail() ) {
			__strToolsLogger.log(
				__StrToolsLogLvl::INFO, "isCapturedValueInvalid(char, ...): The stream failed."
			);
			// Clear the error flags so we can use `cin` again.
			cin.clear();
			// Ignore invalid input.
			__StrUtilExtra.ignoreCapturedValue(value);
			return true;
		}

		__strToolsLogger.log(__StrToolsLogLvl::INFO, "isCapturedValueInvalid(...): No errors.");
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
	bool userInputHandler(char* input, const uint64_t size) {
		strcpy(input, ""); // Reset the input.
		cin.clear();
		cin.sync();

		while( true ) {
			// Avoids errors by ignoring invalid characters in the stream.
			if( !cin.getline(input, size) ) {
				// Clear the error state and siscard invalid input
				__StrUtilExtra.ignoreCapturedValue('\n');
				cerr << "An invalid value was captured!\n";
				return false;
			}

			// Check if the user wants to exit
			if( strcmp(input, "/exit") == 0 ) {
				return true;
			}

			// Input is valid and the user does not want to exit
			return false;
		}
	}
}
