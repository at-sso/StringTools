// Copyright (c) zperk.
// License: GNU General Public License v3.0 

#pragma once

#include <array>
#include <cstdint>
#include <cstring>
#include <memory>
#include <stdexcept>
#include <string.h>

// Equals to: `std::unique_ptr<char[]>`.
typedef std::unique_ptr<char[]> str_p;

// Equals to: `char*`.
typedef char* str_raw_p;

// Utility tools for the strTools namespace.
namespace __strToolsUtil {
	/***
	 * @brief Checks for invalid inputs and throws an exception if the rule is violated.
	 *
	 * @param rule The condition to be checked.
	 * @param msg The message to be included in the exception if the rule is violated.
	 * @throws std::logic_error if the rule is false.
	 */
	static void checkErrors(bool rule, const char msg[]) {
		if( !rule ) {
			throw std::logic_error(msg);
		}
	}

	/***
	 * @brief Creates a std::unique_ptr<char[]> from a const char* source.
	 *
	 * @param src The source C-string.
	 * @return A unique_ptr<char[]> containing a copy of the source string.
	 */
	static str_p makeUniqueStr(const str_raw_p src) {
		uint64_t srcLen = strlen(src);
		str_p r = std::make_unique<char[]>(static_cast<uint64_t>( srcLen ) + 1);
		strcpy(r.get(), src);
		return r;
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
	static uint64_t len(const str_raw_p n) {
		return strlen(n);
	}

	/***
	 * @brief Concatenates two C-strings into a new unique_ptr<char[]>.
	 *
	 * @param S1 The first source C-string.
	 * @param S2 The second source C-string.
	 * @return A unique_ptr<char[]> containing the concatenated string.
	 */
	static str_p concatStr(const str_raw_p S1, const str_raw_p S2) {
		auto s1 = __strToolsUtil::makeUniqueStr(S1);
		auto s2 = __strToolsUtil::makeUniqueStr(S2);

		if( !s1 || !s2 ) {
			return nullptr;
		}

		// Calculate the length of the new concatenated string
		std::array<uint64_t, 2> lenVals {
			len(S1), len(S2)
		};

		// Allocate memory for the concatenated string
		str_p r = std::make_unique<char[]>(
			static_cast<uint64_t>( lenVals[0] ) + lenVals[1] + 1
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
	static str_p subStr(const str_raw_p S, uint64_t i, uint64_t j) {
		auto s = __strToolsUtil::makeUniqueStr(S);

		__strToolsUtil::checkErrors(
			( i < 0 ) || ( j < 0 ) || ( i + j > len(s.get()) ),
			"The indices 'i' and 'j' must be non-negative and "
			"the length must not exceed the length of the original string.\n"
		);

		str_p r = std::make_unique<char[]>(
			( static_cast<uint64_t>( j ) + 1 ) * sizeof(char)
		);
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
	static str_p insertStr(const str_raw_p s1, const str_raw_p s2, uint64_t i) {
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
	static str_p delSubStr(const str_raw_p s, uint64_t i, uint64_t j) {
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
	static uint64_t findSubStr(const str_raw_p s, const str_raw_p find) {
		// Check for invalid pointers.
		if( s == nullptr || find == nullptr )
			return -1;

		std::array<uint64_t, 2> lenVals {
			len(s), len(find)
		};

		if( lenVals[0] == 0 )
			return 0;

		for( int i = 0; i <= lenVals[0] - lenVals[1]; ++i ) {
			// Check if `find` matches the substring starting at index i of `s`
			bool found = true;
			for( int j = 0; j < lenVals[1]; ++j ) {
				if( s[i + j] != find[j] ) {
					found = false;
					break;
				}
			}
			if( found ) {
				return i;
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
	static str_p replaceStr(const str_raw_p s, const str_raw_p sub1, const str_raw_p sub2) {
		if( !s || !sub1 || !sub2 )
			throw std::logic_error("Pointer value is invalid.");

		auto getSubStr = [](const str_raw_p s, const str_raw_p sub) {
			const str_raw_p pos = std::strstr(s, sub);
			if( pos )
				return (uint64_t) pos - (uint64_t) s;
			return UINT64_MAX;
			};

		uint64_t pos = getSubStr(s, sub1);
		if( pos == -1 )
			return __strToolsUtil::makeUniqueStr(s);

		std::array<uint64_t, 3> lenVals {
			len(s), len(sub1), len(sub2)
		};

		// Calculate the length of the new string
		uint64_t newLen = lenVals[0] - lenVals[1] + lenVals[2];

		// Allocate memory for the new string
		str_p r = std::make_unique<char[]>(static_cast<uint64_t>( newLen ) + 1);

		// Copy the part before sub1
		strncpy(r.get(), s, pos);
		r[pos] = '\0';

		// Append sub2
		strcat(r.get(), sub2);

		// Append the part after sub1
		strcat(r.get(), s + pos + lenVals[1]);

		return r;
	}
}
