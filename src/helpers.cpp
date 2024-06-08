#pragma once

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string.h>

#define str_p std::unique_ptr<char[]>
#define str char*

// Check for invalid inputs.
static void checkErrors(bool rule, const char msg[]) {
	if( !rule ) 
		throw std::logic_error(msg);
}

// This function creates a unique_ptr<char[]> from a const char* source.
static str_p makeUniqueStr(const str src) {
	int32_t srcLen = strlen(src);
	str_p result = std::make_unique<char[]>(static_cast<size_t>( srcLen ) + 1);
	strcpy(result.get(), src);
	return result;
}
