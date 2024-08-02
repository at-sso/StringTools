/**
 * @file strutilhelper.hh
 * @author Ian Hylton
 * @brief Utilities for the strutil namespace.
 * @version 1.0.0
 * @date 2024-07-31
 *
 * @copyright Copyright (c) zperk 2024
 *
 */

#pragma once

#include "strlogger.h"
#include <cstring>
#include <iosfwd>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

using std::cin, std::cerr, std::endl, std::numeric_limits;
using std::string, std::to_string;

namespace fs = std::filesystem;

static void _strLogger(const string& from, const string& s, __StrToolsLogLvl lvl = __StrToolsLogLvl::INFO) {
	return __strToolsLogger.log(lvl, from + ": " + s);
}

class __StrUtilHelper {
private:
	string __strUtilLoggerFilePath;

public:
	/**
	 * @brief Ignores invalid input from standard input.
	 *
	 * This function clears the error flags from `cin` and ignores remaining invalid input
	 * up to the next newline. It is typically used after a failed input operation.
	 *
	 * @param s Character to ignore.
	 * @param doClear Clears the error state if `true`.
	 *
	 * @note Example usage:
	 * @code
	 * int value;
	 * std::cin >> value;
	 * __ignoreCapturedValue('\n');
	 * @endcode
	 */
	void ignoreCapturedValue(char s, bool doClear = true) {
		_strLogger("ignoreCapturedValue(char, bool)", to_string(s) + ", " + to_string(doClear));
		if( doClear ) cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), s);
	}

	/**
	 * @brief Checks for invalid inputs and throws an exception if the rule is violated.
	 *
	 * This function evaluates a given condition (rule) and throws a `std::out_of_range`
	 * exception with a specified message if the condition is true. It is commonly used
	 * to enforce constraints and validate inputs within other functions.
	 *
	 * @param rule The condition to be checked. If this condition evaluates to true, an exception is thrown.
	 * @param msg The message to be included in the exception if the rule is violated.
	 * @throws std::out_of_range if the rule is true.
	 *
	 * @note Example usage:
	 * @code
	 * __checkLogicErrors(index < arraySize, "Index out of range");
	 * @endcode
	 */
	void checkLogicErrors(bool rule, const string& msg) {
		_strLogger("checkLogicErrors(bool, string)", to_string(rule) + ", " + msg, __StrToolsLogLvl::WARNING);
		if( rule ) throw std::runtime_error(msg);
	}

	/**
	 * @brief Converts a string to something (in-place).
	 *
	 * This function modifies the input string by converting all characters
	 * into something.
	 *
	 * @param str The input string to be modified.
	 * @param f Function to do something with the string (e.g., `tolower` or `toupper`).
	 *
	 * @note Modifies the original string.
	 *
	 * @note Example usage:
	 * @code
	 * std::string myString = "Hello, World!";
	 * __toSomething(myString); // `myString` will be something, I don't know
	 * @endcode
	 */
	void toSomething(char* s, int ( *f )( int )) {
		_strLogger("toSomething(char*, *func)", to_string(*s) + ", func");
		for( int i = 0; s[i]; i++ ) {
			s[i] = f((unsigned char) s[i]);
		}
	}

	/**
	 * @brief Checks for a null character pointer and throws an exception if it is invalid.
	 *
	 * This function checks if the provided character pointer is `nullptr`. If it is, an
	 * `std::invalid_argument` exception is thrown with a specified message. It is useful
	 * for validating character pointers before performing operations on them.
	 *
	 * @param c The character pointer to be checked.
	 *
	 * @throws std::invalid_argument if the character pointer is `nullptr`.
	 *
	 * @note Example usage:
	 * @code
	 * char* myString = nullptr;
	 * __checkInvalidCharPtr(myString); // Throws an exception with the message.
	 * @endcode
	 */
	bool checkInvalidCharPtr(const char* s, const string& from) noexcept {
		if( s == nullptr || *s == '\0' ) {
			_strLogger(
				from,
				"Expected a valid character pointer but a nullptr was received.",
				__StrToolsLogLvl::WARNING
			);
			return true;
		}
		return false;
	}

	template <class T>
	T makeSmartPtr(const char* src) noexcept {
		_strLogger("makeSmartPtr()", src);
		// If invalid, return the T to a null terminator.
		if( this->checkInvalidCharPtr(src, "__makeSmartPtr(const char*)") ) {
			T empty(new char[1]);
			empty[0] = '\0'; // Set the null terminator
			return empty;
		}
		// Else, start conversion
		T s(new char[strlen(src) + 1]);
		strcpy(s.get(), src);
		return s;
	}
} __StrUtilExtra;
