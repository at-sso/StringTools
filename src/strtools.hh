// Copyright (c) zperk.
// License: GNU General Public License v3.0 

#pragma once

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <string.h>

namespace strTools {
	// Equals to: `std::unique_ptr<char[]>`.
	typedef std::unique_ptr<char[]> strptr;

	// Equals to: `char*`.
	typedef char* str;
}

// Utility tools for the strTools namespace.
// If at any moment you need to use this ns, you are doing something wrong.
namespace __strToolsUtil {
	/***
	 * @brief Checks for invalid inputs and throws an exception if the rule is violated.
	 *
	 * @param rule The condition to be checked.
	 * @param msg The message to be included in the exception if the rule is violated.
	 * @throws std::logic_error if the rule is false.
	 */
	static void checkErrors(bool rule, const char msg[]) {
		if( rule == true ) {
			throw std::logic_error(msg);
		}
	}

	/***
	 * @brief Creates a std::unique_ptr<char[]> from a const char* source.
	 *
	 * @param src The source C-string.
	 * @return A unique_ptr<char[]> containing a copy of the source string.
	 */
	static strTools::strptr makeUniqueStr(const strTools::str src) {
		uint64_t srcLen = strlen(src);
		strTools::strptr r = std::make_unique<char[]>(
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
	static void fixIndex(uint64_t& x) {
		if( x >= INT64_MAX or x == UINT64_MAX ) {
			x = 0ULL;
		}
	}

	/***
	 * @brief Converts a string to lowercase.
	 *
	 * @param str The input string to be converted.
	 * @return The lowercase version of the input string.
	 */
	static std::string toUndercase(const std::string& str) {
		std::string lowerStr = str;
		std::transform(
			lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
			[](unsigned char c) { return std::tolower(c); }
		);
		return lowerStr;
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
	uint64_t len(const str n) {
		return strlen(n);
	}

	/***
	 * @brief Concatenates two C-strings into a new unique_ptr<char[]>.
	 *
	 * @param S1 The first source C-string.
	 * @param S2 The second source C-string.
	 * @return A unique_ptr<char[]> containing the concatenated string.
	 */
	strptr concatStr(const str S1, const str S2) {
		auto s1 = __strToolsUtil::makeUniqueStr(S1);
		auto s2 = __strToolsUtil::makeUniqueStr(S2);

		if( !s1 || !s2 ) {
			return nullptr;
		}

		// Calculate the length of the new concatenated string
		auto lenS1 = len(S1);
		auto lenS2 = len(S2);

		// Allocate memory for the concatenated string
		strptr r = std::make_unique<char[]>(
			static_cast<uint64_t>( lenS1 ) + lenS2 + 1
		);
		// Copy the first string into the result
		strcpy(r.get(), s1.get());
		// Concatenate the second string
		strcat(r.get(), s2.get());
		return r;
	}

	/***
	 * @brief Extracts a substring from a string.
	 *
	 * @param S The source C-string.
	 * @param i Position of the first character to include (index 0 = first character).
	 * @param j Number of characters to extract from i.
	 * @return A unique_ptr<char[]> containing the extracted substring.
	 * @throws std::logic_error if indices are out of bounds.
	 */
	strptr subStr(const str S, const uint64_t i, uint64_t j) {
		auto s = __strToolsUtil::makeUniqueStr(S);
		auto sLen = len(s.get());

		__strToolsUtil::checkErrors(
			i >= sLen || i + j > sLen,
			"The indices 'i' and 'j' must be non-negative and "
			"the length must not exceed the length of the original string.\n"
		);

		strptr r = std::make_unique<char[]>(static_cast<uint64_t>( j ) + 1);
		strncpy(r.get(), s.get() + i, j);
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
	 * @throws std::logic_error if the position is out of bounds.
	 */
	strptr insertStr(const str s1, const str s2, const uint64_t i) {
		__strToolsUtil::checkErrors(
			1 <= i || i <= len(s1) + 1,
			"The value of 'i' must be in the range of 1 to the length of C1 + 1"
		);
		return concatStr(
			concatStr(subStr(s1, 1, i - 1).get(), s1).get(),
			subStr(s1, i, len(s1) - ( i - 1 )).get()
		);
	}

	/***
	 * @brief Removes a substring from a string.
	 *
	 * @param s The source C-string.
	 * @param i The starting position of the substring to be removed.
	 * @param j The length of the substring to be removed.
	 * @return A unique_ptr<char[]> containing the resulting string.
	 * @throws std::logic_error if indices are out of bounds.
	 */
	strptr delSubStr(const str s, const uint64_t i, const uint64_t j) {
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

		return concatStr(
			subStr(s, 1, i - 1).get(),
			subStr(s, i + j, len(s) - ( i + j - 1 )).get()
		);
	}

	/***
	 * @brief Finds the first occurrence of a substring within a string.
	 *
	 * @param s The source C-string.
	 * @param find The substring to find.
	 * @return The index of the first occurrence of the substring, or -1 if not found.
	 */
	int64_t findSubStr(const str s, const str find) {
		// Check for invalid pointers.
		if( s == nullptr || find == nullptr ) {
			return -1;
		}

		auto lenS = len(s);
		auto lenFind = len(find);

		// Fix the strings because we don't really care about specifics.
		const auto& underS = __strToolsUtil::toUndercase(s);
		const auto& underFind = __strToolsUtil::toUndercase(find);
		
		// The original string is empty or,
		// If `find` is longer than `s`, it can't be found.
		if( lenS == 0 or lenFind > lenS ) {
			return -1;
		}

		if( lenFind == 0 ) {
			return 0; // Empty substring is always found at the start.
		}

		for( uint64_t i = 0; i <= lenS - lenFind; ++i ) {
			bool found = true;
			for( uint64_t j = 0; j < lenFind; ++j ) {
				if( underS[i + j] != underFind[j] ) {
					found = false;
					break;
				}
			}
			if( found ) {
				return static_cast<uint64_t>( i );
			}
		}

		return -1;
	}

	/***
	 * @brief Replaces the first occurrence of a substring with another substring.
	 *
	 * @param s The source C-string.
	 * @param sub1 The substring to be replaced.
	 * @param sub2 The substring to replace with.
	 * @return A unique_ptr<char[]> containing the resulting string.
	 * @throws std::logic_error if any of the input pointers are invalid.
	 */
	strptr replaceStr(const str s, const str sub1, const str sub2) {
		if( !s || !sub1 || !sub2 ) {
			throw std::logic_error("Pointer value is invalid.");
		}

		auto getSubStr = [&](const str s, const str sub) {
			const str pos = strstr(s, sub);
			if( pos ) {
				return (uint64_t) pos - (uint64_t) s;
			}
			return 0ULL;
			};

		uint64_t pos = getSubStr(s, sub1);
		if( pos == -1 ) {
			return __strToolsUtil::makeUniqueStr(s);
		}

		auto lenS = len(s);
		auto lenSub1 = len(sub1);
		auto lenSub2 = len(sub2);

		// Calculate the length of the new string
		uint64_t newLen = lenS - lenSub1 + lenSub2;

		// Allocate memory for the new string
		strptr r = std::make_unique<char[]>(static_cast<uint64_t>( newLen ) + 1);

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
