/**
 * @file strtools.hh
 * @author Ian Hylton
 * @brief String manipulation tools.
 * @version 1.0.1
 * @date 2024-07-30
 *
 * @copyright Copyright (c) zperk 2024
 *
 */

 // Copyright (c) zperk.
 // License: GNU General Public License v3.0

#pragma once

#include "strutil.hh"
#include "strutilhelper.hh"
#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include <string.h>

using std::string;

/**
 * @namespace strTools
 * @brief String manipulation tools.
 *
 * This namespace provides a set of functions for various string operations,
 * including length calculation, concatenation, substring extraction, insertion,
 * deletion, finding substrings, and replacement of substrings. These functions
 * use C-style strings and return results in `std::unique_ptr<char[]>` to ensure
 * proper memory management.
 */
namespace strTools {
	/**
	 * @brief Concatenates two C-strings into a new unique_ptr<char[]>.
	 *
	 * This function takes two C-strings and concatenates them into a new
	 * dynamically allocated string managed by `std::unique_ptr<char[]>`.
	 *
	 * @param s1 The first source C-string.
	 * @param s2 The second source C-string.
	 * @return A unique_ptr<char[]> containing the concatenated string.
	 *
	 * @note Example usage:
	 * @code
	 * const char* str1 = "Hello, ";
	 * const char* str2 = "World!";
	 * auto result = strTools::concatStr(str1, str2);
	 * // result will contain "Hello, World!"
	 * @endcode
	 */
	std::unique_ptr<char[]> concatStr(const char* s1, const char* s2) noexcept {
		// Calculate the length of the new concatenated string
		auto lenS1 = strlen(s1);
		auto lenS2 = strlen(s2);

		// Allocate memory for the concatenated string
		std::unique_ptr<char[]> r = std::make_unique<char[]>(
			static_cast<size_t>( lenS1 ) + lenS2 + 1
		);
		// Copy the first string into the result
		strcpy(r.get(), s1);
		// Concatenate the second string
		strcat(r.get(), s2);
		return r;
	}

	/**
	 * @brief Extracts a substring from a string.
	 *
	 * This function extracts a substring from a given C-string starting at position
	 * `i` and having `j` characters. The extracted substring is returned as a
	 * `std::unique_ptr<char[]>`.
	 *
	 * @param s The source C-string.
	 * @param i Position of the first character to include (index 0 = first character).
	 * @param j Number of characters to extract from i.
	 * @return A unique_ptr<char[]> containing the extracted substring.
	 * @throws std::out_of_range if indices are out of bounds.
	 *
	 * @note Example usage:
	 * @code
	 * const char* myString = "Hello, World!";
	 * auto sub = strTools::subStr(myString, 7, 5);
	 * // sub will contain "World"
	 * @endcode
	 */
	std::unique_ptr<char[]> subStr(const char* s, const uint64_t i, uint64_t j) {
		auto sLen = strlen(s);

		__StrUtilExtra.checkLogicErrors(
			i >= sLen || i + j > sLen,
			"The indices 'i' and 'j' must be non-negative and "
			"the length must not exceed the length of the original string.\n"
		);

		std::unique_ptr<char[]> r = std::make_unique<char[]>(
			static_cast<uint64_t>( j ) + 1
		);
		strncpy(r.get(), s + i, j);
		r[j] = '\0';
		return r;
	}

	/**
	 * @brief Inserts one string into another at the specified position.
	 *
	 * This function inserts the source string `s2` into the destination string `s1`
	 * at the specified position `i`. The resulting string is returned as a
	 * `std::unique_ptr<char[]>`.
	 *
	 * @param s1 The destination C-string.
	 * @param s2 The source C-string to be inserted.
	 * @param i The position at which to insert s2 into s1.
	 * @return A unique_ptr<char[]> containing the resulting string.
	 * @throws std::out_of_range if the position is out of bounds.
	 *
	 * @note Example usage:
	 * @code
	 * const char* str1 = "Hello, World!";
	 * const char* str2 = "Beautiful ";
	 * auto result = strTools::insertStr(str1, str2, 8);
	 * // result will contain "Hello, Beautiful World!"
	 * @endcode
	 */
	std::unique_ptr<char[]> insertStr(const char* s1, const char* s2, const uint64_t i) {
		__StrUtilExtra.checkLogicErrors(
			1 <= i || i <= strlen(s1) + 1,
			"The value of 'i' must be in the range of 1 to the length of s1 + 1"
		);

		auto p1 = subStr(s1, 0, i - 1);
		auto p2 = concatStr(p1.get(), s2);
		auto p3 = subStr(s1, i - 1, strlen(s1) - ( i - 1 ));

		return concatStr(p2.get(), p3.get());
	}

	/**
	 * @brief Removes a substring from a string.
	 *
	 * This function removes a substring from the source string `s` starting at
	 * position `i` and having length `j`. The resulting string is returned as a
	 * `std::unique_ptr<char[]>`.
	 *
	 * @param s The source C-string.
	 * @param i The starting position of the substring to be removed.
	 * @param j The length of the substring to be removed.
	 * @return A unique_ptr<char[]> containing the resulting string.
	 * @throws std::out_of_range if indices are out of bounds.
	 *
	 * @note Example usage:
	 * @code
	 * const char* myString = "Hello, World!";
	 * auto result = strTools::delSubStr(myString, 7, 6);
	 * // result will contain "Hello, !"
	 * @endcode
	 */
	std::unique_ptr<char[]> delSubStr(const char* s, const uint64_t i, const uint64_t j) {
		__StrUtilExtra.checkLogicErrors(
			0 <= i && i < strlen(s),
			"Position of `i` must be between 0 and the length of the string."
		);
		__StrUtilExtra.checkLogicErrors(
			0 <= j && j < strlen(s),
			"Length `j` must be between 0 and the length of the string."
		);
		__StrUtilExtra.checkLogicErrors(
			0 <= i + j - 1 && i + j - 1 < strlen(s),
			"Position i+j-1 must be between 0 and the length of the string."
		);

		auto p1 = subStr(s, 0, i - 1);
		auto p2 = subStr(s, i + j - 1, strlen(s) - ( i + j - 1 ));

		return concatStr(p1.get(), p2.get());
	}

	/**
	 * @brief Finds the first occurrence of a substring within a string.
	 *
	 * This function searches for the first occurrence of the substring `find`
	 * within the source string `s`. It returns the index of the first occurrence,
	 * or `INT64_MAX` if the substring is not found.
	 *
	 * @param s The source C-string.
	 * @param find The substring to find.
	 * @return The index of the first occurrence of the substring, or INT64_MAX if not found.
	 *
	 * @note Example usage:
	 * @code
	 * const char* myString = "Hello, World!";
	 * int64_t index = strTools::findSubStr(myString, "World");
	 * // index will be 7
	 * @endcode
	 */
	int64_t findSubStr(const char* s, const char* find) {
		auto lenS = strlen(s);
		auto lenFind = strlen(find);

		// Fix the strings because we don't really care about specifics.
		const auto& lowS = strUtil::toLower(s);
		const auto& lowFind = strUtil::toLower(find);

		// The original string is empty or,
		// If `find` is longer than `s`, it can't be found.
		if( lenS == 0 || lenFind > lenS ) {
			return INT64_MAX;
		}

		if( lenFind == 0 ) {
			return 0; // Empty substring is always found at the start.
		}

		// Get the index using bubble sorting (kind of)
		for( uint64_t i = 0; i <= lenS - lenFind; ++i ) {
			bool found = true;
			for( uint64_t j = 0; j < lenFind; ++j ) {
				if( lowS[i + j] != lowFind[j] ) {
					found = false;
					break;
				}
			}
			if( found ) {
				return static_cast<uint64_t>( i );
			}
		}

		return INT64_MAX;
	}

	/**
	 * @brief Replaces the first occurrence of a substring with another substring.
	 *
	 * This function replaces the first occurrence of the substring `sub1` in the
	 * source string `s` with the substring `sub2`. The resulting string is returned
	 * as a `std::unique_ptr<char[]>`.
	 *
	 * @param s The source C-string.
	 * @param sub1 The substring to be replaced.
	 * @param sub2 The substring to replace with.
	 * @return A unique_ptr<char[]> containing the resulting string.
	 *
	 * @note Example usage:
	 * @code
	 * const char* myString = "Hello, World!";
	 * const char* sub1 = "World";
	 * const char* sub2 = "Universe";
	 * auto result = strTools::replaceStr(myString, sub1, sub2);
	 * // result will contain "Hello, Universe!"
	 * @endcode
	 */
	std::unique_ptr<char[]> replaceStr(const char* s, const char* sub1, const char* sub2) {
		auto getSubStr = [&](const char* s, const char* sub) {
			const char* pos = strstr(s, sub);
			if( pos ) {
				return (uint64_t) pos - (uint64_t) s;
			}
			return (uint64_t) 0;
			};

		uint64_t pos = getSubStr(s, sub1);
		// Fix the index of `pos` JUST IN CASE.
		// If the index is out of bounds this will simply return 0 (the first position).
		if( pos > UINT64_MAX ) {
			pos = 0ull;
		}

		auto lenS = strlen(s);
		auto lenSub1 = strlen(sub1);
		auto lenSub2 = strlen(sub2);

		// Calculate the length of the new string
		auto newLen = lenS - lenSub1 + lenSub2;

		// Allocate memory for the new string
		std::unique_ptr<char[]> r = std::make_unique<char[]>(
			static_cast<size_t>( newLen ) + 1
		);

		// Copy the part before sub1
		strncpy(r.get(), s, pos);
		r[pos] = '\0';

		// Append sub2
		strcat(r.get(), sub2);

		// Append the part after sub1
		strcat(r.get(), s + pos + lenSub1);

		return r;
	}
}
