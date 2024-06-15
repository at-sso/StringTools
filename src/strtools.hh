// Copyright (c) zperk.
// License: GNU General Public License v3.0 

#pragma once

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstring>
#include <memory>
#include <stdexcept>
#include <string>
#include <string.h>


// Utility tools for the strTools namespace.
// If at any moment you need to use this ns, you are doing something wrong.
namespace __strToolsUtil {
	/***
	 * @brief Checks for invalid inputs and throws an exception if the rule is violated.
	 *
	 * @param rule The condition to be checked.
	 * @param msg The message to be included in the exception if the rule is violated.
	 * @throws std::out_of_range if the rule is false.
	 */
	static void checkErrors(bool rule, const char msg[]) {
		if( rule == true ) {
			throw std::out_of_range(msg);
		}
	}

	/***
	 * @brief Creates a std::unique_ptr<char[]> from a const char* source.
	 *
	 * @param src The source C-string.
	 * @return A unique_ptr<char[]> containing a copy of the source string.
	 */
	static std::unique_ptr<char[]> makeUniqueStr(const char* src) noexcept {
		uint64_t srcLen = strlen(src);
		std::unique_ptr<char[]> r = std::make_unique<char[]>(
			static_cast<uint64_t>( srcLen ) + 1
		);
		strcpy(r.get(), src);
		return r;
	}

	/***
	 * @brief Fixes the index of a number.
	 *
	 * @param x The number to be fixed.
	 */
	static void fixIndex(uint64_t& x) noexcept {
		if( x > UINT64_MAX ) {  // Check for values exceeding the maximum unsigned 64-bit value
			x = 0ULL;
		}
	}

	/***
	 * @brief Converts a string to lowercase.
	 *
	 * @param str The input string to be converted.
	 * @return The lowercase version of the input string.
	 */
	static std::string toUndercase(std::string str) noexcept {
		std::transform(
			str.begin(), str.end(), str.begin(),
			[](unsigned char c) { return std::tolower(c); }
		);
		return str;
	}
}

// String tools.
namespace strTools {
	/***
	 * @brief Returns the length of the C-string.
	 *
	 * @param n The source C-string.
	 * @return The length of the string.
	 */
	uint64_t len(const char* n) {
		return strlen(n);
	}

	/***
	 * @brief Concatenates two C-strings into a new unique_ptr<char[]>.
	 *
	 * @param s1 The first source C-string.
	 * @param s2 The second source C-string.
	 * @return A unique_ptr<char[]> containing the concatenated string.
	 */
	std::unique_ptr<char[]> concatStr(const char* s1, const char* s2) noexcept {
		// Calculate the length of the new concatenated string
		auto lenS1 = len(s1);
		auto lenS2 = len(s2);

		// Allocate memory for the concatenated string
		std::unique_ptr<char[]> r = std::make_unique<char[]>(
			static_cast<uint64_t>( lenS1 ) + lenS2 + 1
		);
		// Copy the first string into the result
		strcpy(r.get(), s1);
		// Concatenate the second string
		strcat(r.get(), s2);
		return r;
	}

	/***
	 * @brief Extracts a substring from a string.
	 *
	 * @param s The source C-string.
	 * @param i Position of the first character to include (index 0 = first character).
	 * @param j Number of characters to extract from i.
	 * @return A unique_ptr<char[]> containing the extracted substring.
	 * @throws std::out_of_range if indices are out of bounds.
	 */
	std::unique_ptr<char[]> subStr(const char* s, const uint64_t i, uint64_t j) {
		auto sLen = len(s);

		__strToolsUtil::checkErrors(
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

	/***
	 * @brief Inserts one string into another at the specified position.
	 *
	 * @param s1 The destination C-string.
	 * @param s2 The source C-string to be inserted.
	 * @param i The position at which to insert s2 into s1.
	 * @return A unique_ptr<char[]> containing the resulting string.
	 * @throws std::out_of_range if the position is out of bounds.
	 */
	std::unique_ptr<char[]> insertStr(const char* s1, const char* s2, const uint64_t i) {
		__strToolsUtil::checkErrors(
			1 <= i || i <= len(s1) + 1,
			"The value of 'i' must be in the range of 1 to the length of s1 + 1"
		);

		auto p1 = subStr(s1, 0, i - 1);
		auto p2 = concatStr(p1.get(), s2);
		auto p3 = subStr(s1, i - 1, len(s1) - ( i - 1 ));

		return concatStr(p2.get(), p3.get());
	}

	/***
	 * @brief Removes a substring from a string.
	 *
	 * @param s The source C-string.
	 * @param i The starting position of the substring to be removed.
	 * @param j The length of the substring to be removed.
	 * @return A unique_ptr<char[]> containing the resulting string.
	 * @throws std::out_of_range if indices are out of bounds.
	 */
	std::unique_ptr<char[]> delSubStr(const char* s, const uint64_t i, const uint64_t j) {
		__strToolsUtil::checkErrors(
			0 <= i && i < len(s),
			"Position of `i` must be between 0 and the length of the string."
		);
		__strToolsUtil::checkErrors(
			0 <= j && j < len(s),
			"Length `j` must be between 0 and the length of the string."
		);
		__strToolsUtil::checkErrors(
			0 <= i + j - 1 && i + j - 1 < len(s),
			"Position i+j-1 must be between 0 and the length of the string."
		);

		auto p1 = subStr(s, 0, i - 1);
		auto p2 = subStr(s, i + j - 1, len(s) - ( i + j - 1 ));

		return concatStr(p1.get(), p2.get());
	}

	/***
	 * @brief Finds the first occurrence of a substring within a string.
	 *
	 * @param s The source C-string.
	 * @param find The substring to find.
	 * @return The index of the first occurrence of the substring, or INT64_MAX if not found.
	 */
	int64_t findSubStr(const char* s, const char* find) {
		auto lenS = len(s);
		auto lenFind = len(find);

		// Fix the strings because we don't really care about specifics.
		const auto& undcS = __strToolsUtil::toUndercase(s);
		const auto& undcFind = __strToolsUtil::toUndercase(find);

		// The original string is empty or,
		// If `find` is longer than `s`, it can't be found.
		if( lenS == 0 or lenFind > lenS ) {
			return INT64_MAX;
		}

		if( lenFind == 0 ) {
			return 0; // Empty substring is always found at the start.
		}

		// Get the index using bubble sorting (kind of)
		for( uint64_t i = 0; i <= lenS - lenFind; ++i ) {
			bool found = true;
			for( uint64_t j = 0; j < lenFind; ++j ) {
				if( undcS[i + j] != undcFind[j] ) {
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

	/***
	 * @brief Replaces the first occurrence of a substring with another substring.
	 *
	 * @param s The source C-string.
	 * @param sub1 The substring to be replaced.
	 * @param sub2 The substring to replace with.
	 * @return A unique_ptr<char[]> containing the resulting string.
	 */
	std::unique_ptr<char[]> replaceStr(const char* s, const char* sub1, const char* sub2) {
		auto getSubStr = [&](const char* s, const char* sub) {
			const char* pos = strstr(s, sub);
			if( pos ) {
				return (uint64_t) pos - (uint64_t) s;
			}
			return 0ULL;
			};

		uint64_t pos = getSubStr(s, sub1);
		// Fix the index of pos JUST IN CASE.
		// If the index is out of bounds this will simply return 0 (the first position).
		__strToolsUtil::fixIndex(pos);

		auto lenS = len(s);
		auto lenSub1 = len(sub1);
		auto lenSub2 = len(sub2);

		// Calculate the length of the new string
		uint64_t newLen = lenS - lenSub1 + lenSub2;

		// Allocate memory for the new string
		std::unique_ptr<char[]> r = std::make_unique<char[]>(
			static_cast<uint64_t>( newLen ) + 1
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
