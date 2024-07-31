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

#include <iosfwd>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

namespace strUtil {
	// Shows the current status of the `strUtil` namespace. This is not a logger.
	static std::string strUtilStatus = "";
}

/**
 * @brief Ignores invalid input from standard input.
 *
 * This function clears the error flags from `cin` and ignores remaining invalid input
 * up to the next newline. It is typically used after a failed input operation.
 *
 * @note Example usage:
 * @code
 * int value;
 * std::cin >> value;
 * __ignoreCapturedValue('\n');
 * @endcode
 */
static void __ignoreCapturedValue(char s) {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), s);
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
static void __checkLogicErrors(bool rule, const std::string& msg) {
	if( rule ) throw std::out_of_range(msg);
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
static void __toSomething(char* s, int ( *f )( int )) {
	for( int i = 0; s[i]; i++ )
		s[i] = f((unsigned char) s[i]);
}

/**
 * @brief Formats a status message string.
 *
 * This function creates a formatted status message by combining the provided function name
 * and message into a single string. The resulting string follows the format:
 * "`<function_name>() <message>`" and assigns it to the `strUtilStatus` variable.
 *
 * @param from The name of the function as a string.
 * @param msg The message to be included in the status.
 *
 * @note Example usage:
 * @code
 * __statusFormatter("myFunction", "Operation successful");
 * // strUtilStatus will be "`myFunction() Operation successful`"
 * @endcode
 */
static void __statusFormatter(const std::string& from, const std::string& msg) {
	strUtil::strUtilStatus = "- `" + from + "`: " + msg;
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
static bool __checkInvalidCharPtr(const char* s, const std::string& from) {
	if( s == nullptr || *s == '\0' ) {
		__statusFormatter(
			from, "Expected a valid character pointer (`char*`) but NULL (`nullptr`) was received."
		);
		return true;
	}
	return false;
}
