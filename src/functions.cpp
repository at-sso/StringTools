#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <string.h>

#include "helpers.cpp"

static int32_t len(const str n) {
	return strlen(n);
}

static str_p concatStr(const str S1, const str S2) {
	auto s1 = makeUniqueStr(S1);
	auto s2 = makeUniqueStr(S2);

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

/**
 * This allows you to extract a substring from a string. It works by specifying 
 * the starting index `i` and the length ofthe substring `j`.
 *
 * @param i Position of the first character to include (index 0 = first character).
 * @param j Number of characters to extract from i. 
 */
static str_p subStr(str S, int32_t i, int32_t j) {
	auto s = makeUniqueStr(S);

	checkErrors(
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


/**
 * A string or part of a string can be inserted into another string.
 * This procedure consists of inserting the string “s1” into the string “s1” such that
 * the first character of `s2` is the i-th character of the result.
 */
static str_p insertStr(str s1, str s2, int32_t i) {
	checkErrors(
		1 <= i <= len(s1) + 1,
		"The value of 'i' must be in the range of 1 to the length of C1 + 1"
	);
	return concatStr(
		concatStr(subStr(s1, 1, i - 1).get(), s1).get(), 
		subStr(s1, i, len(s1) - ( i - 1 )).get()
	);
}

/**
 * Allows you to remove substrings from a string.
 * Removes from string `s` the substring of length `j` that starts at position `i`.
 */
static str_p delSubStr(str s, int32_t i, int32_t j) {
	checkErrors(
		1 <= i <= len(s),
		"Position of `i` must be between 1 and the length of the string."
	);
	checkErrors(
		0 <= j <= len(s),
		"Length `j` must be between 0 and the length of the string."
	);
	checkErrors(
		0 <= i + j - 1 <= len(s),
		"Position i+j-1 must be between 0 and the length of the string."
	);

	return concatStr(
		subStr(s, 1, i - 1).get(), 
		subStr(s, i + j, len(s) - ( i + j - 1 )).get()
	);
}

// TODO
static int32_t findSubStr() { }
