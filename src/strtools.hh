#pragma once

#include <array>
#include <cstdint>
#include <cstring>
#include <memory>
#include <stdexcept>
#include <string.h>

#include "strfunc.hh"

namespace strTools {
	static int32_t len(const str n) {
		return strlen(n);
	}

	static str_p concatStr(const str S1, const str S2) {
		auto s1 = strFunc::makeUniqueStr(S1);
		auto s2 = strFunc::makeUniqueStr(S2);

		if( !s1 or !s2 ) {
			return nullptr;
		}

		// Calculate the length of the new concatenated string
		std::array<int32_t, 2> lenVals {
			len(S1), len(S2)
		};

		// Allocate memory for the concatenated string
		str_p r = std::make_unique<char[]>(static_cast<size_t>( lenVals[0] ) + lenVals[1] + 1);
		// Copy the first string into the result
		strcpy(r.get(), s1.get());
		// Concatenate the second string
		std::strcat(r.get(), s2.get());
		return r;
	}

	/***
	 * This allows you to extract a substring from a string. It works by specifying
	 * the starting index `i` and the length ofthe substring `j`.
	 *
	 * @param i Position of the first character to include (index 0 = first character).
	 * @param j Number of characters to extract from i.
	 */
	static str_p subStr(const str S, int32_t i, int32_t j) {
		auto s = strFunc::makeUniqueStr(S);

		strFunc::checkErrors(
			( i < 0 ) or ( j < 0 ) or ( i + j > len(s.get()) ),
			"The indices 'i' and 'j' must be non-negative and "
			"the length must not exceed the length of the original string.\n"
		);

		str_p r = std::make_unique<char[]>(
			( static_cast<size_t>( j ) + 1 ) * sizeof(char)
		);
		strncpy(r.get(), s.get() + i, j);
		r[j] = '\0';
		return r;
	}


	/***
	 * A string or part of a string can be inserted into another string.
	 * This procedure consists of inserting the string “s1” into the string “s1” such that
	 * the first character of `s2` is the i-th character of the result.
	 */
	static str_p insertStr(const str s1, const str s2, int32_t i) {
		strFunc::checkErrors(
			1 <= i <= len(s1) + 1,
			"The value of 'i' must be in the range of 1 to the length of C1 + 1"
		);
		return concatStr(
			concatStr(subStr(s1, 1, i - 1).get(), s1).get(),
			subStr(s1, i, len(s1) - ( i - 1 )).get()
		);
	}

	/***
	 * Allows you to remove substrings from a string.
	 * Removes from string `s` the substring of length `j` that starts at position `i`.
	 */
	static str_p delSubStr(const str s, int32_t i, int32_t j) {
		strFunc::checkErrors(
			1 <= i <= len(s),
			"Position of `i` must be between 1 and the length of the string."
		);
		strFunc::checkErrors(
			0 <= j <= len(s),
			"Length `j` must be between 0 and the length of the string."
		);
		strFunc::checkErrors(
			0 <= i + j - 1 <= len(s),
			"Position i+j-1 must be between 0 and the length of the string."
		);

		return concatStr(
			subStr(s, 1, i - 1).get(),
			subStr(s, i + j, len(s) - ( i + j - 1 )).get()
		);
	}

	/***
	 * Locates a sequence of characters within a string, by determining the
	 * position where a sequence of characters `find` first appears in a string
	 * `s`. Returns an integer.
	 * NOTE: If `find` is not found in `s`, returns - 1.
	 */
	static int32_t findSubStr(const str s, const str find) {
		// Check for invalid pointers.
		if( s == nullptr or find == nullptr )
			return -1;

		std::array<int32_t, 2> lenVals {
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
	 * Replaces the first occurrence of substring `sub1` with another substring `sub2`, in
	 * string `s`.
	 * NOTE: If `sub1` is not found in `s`, return the original string.
	 */
	static str_p replaceStr(const str s, const str sub1, const str sub2) {
		if( !s or !sub1 or !sub2 )
			throw std::logic_error("Pointer value is invalid.");

		auto getSubStr = [](const str s, const str sub) {
			const str pos = std::strstr(s, sub);
			if( pos )
				return (size_t) pos - (size_t) s;
			return -1ULL;
			};

		int32_t pos = getSubStr(s, sub1);
		if( pos == -1 )
			return strFunc::makeUniqueStr(s);

		std::array<int32_t, 3> lenVals {
			len(s), len(sub1), len(sub2)
		};

		// Calculate the length of the new string
		int32_t newLen = lenVals[0] - lenVals[1] + lenVals[2];

		// Allocate memory for the new string
		str_p r = std::make_unique<char[]>(static_cast<size_t>( newLen ) + 1);

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