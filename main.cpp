#include <array>
#include <cstdint>
#include <iostream>
#include <istream>
#include <memory>
#include <new>
#include <random>
#include <string.h>

#include "src/helpers.hh"
#include "src/strtools.hh"

// String max input size.
#define STRING_MAX_SIZE 256
// Array of characters.
#define CHARARR (char[])
// Array of characters with an empty array.
#define EMPTY_CHARARR (char[]) ""

using std::cout, std::cin, std::endl, std::flush;

int main() {
	bool mainLoop = true;
	// Value to be captured from the CLI.
	int32_t selector = 0;
	// Extra message.
	char* extraMsg = CHARARR ":D";

	do {
		helpers::clearScr();
		cout << CHARARR
			"1. Calculate the length of a string.\n"
			"2. Concatenate three strings requested.\n"
			"3. Search for a character in a string.\n"
			"4. Generate a substring from a string.\n"
			"0. Exit.\n"
			<< extraMsg << "\n\n> " << flush;
		cin >> selector;

		// Check if the captured value is invalid.
		if( helpers::isCapturedValueInvalid() ) {
			extraMsg = CHARARR "Value is invalid!";
			continue;
		}

		// Check if the captured value is out of bounds.
		if( helpers::isOutOfBounds(selector, 0, 4) ) {
			extraMsg = CHARARR "Value is out of bounds!";
			continue;
		}

		// If everything is correct, flush the stream and continue.
		cout.flush();

		switch( selector ) {
		case 0: // Exit
		{
			mainLoop = false;
			break;
		} // case 0
		case 1: // Calculate the length of a string.
		{
			std::unique_ptr<char[]> strLen(new char[STRING_MAX_SIZE]);

			cout << CHARARR "Enter a string (type '/exit' to quit).\n" << flush;
			cin.ignore();

			// Start the operation.
			do {
				cout << CHARARR "> ";
				// Call the user input handler.
				if( helpers::userInputHandler(strLen.get(), STRING_MAX_SIZE) ) {
					break;
				}
				// Show the results.
				cout << CHARARR
					"The length of '" << strLen.get() << "' is: "
					<< strTools::len(strLen.get()) << "\n";
			} while( true );

			// Flush the stream.
			cout.flush();
			break;
		} // case 1
		case 2: // Concatenate three strings requested.
		{
			// Array values to be modified by the user.
			std::array<char*, 3> stringVals = { EMPTY_CHARARR, EMPTY_CHARARR, EMPTY_CHARARR };
			// This helper allows the array values to be modified easily.
			char* strHelper = EMPTY_CHARARR;
			bool exitWasCaptured = false;

			cout << CHARARR
				"Enter 3 strings (type '/exit' at any moment to quit).\n"
				"The result will be shown after this operation ends.\n\n" << flush;
			cin.ignore();

			// Start the operation.
			for( int16_t i = 0; i < 3; ++i ) {
				cout << "> ";
				if( helpers::userInputHandler(strHelper, STRING_MAX_SIZE) ) {
					exitWasCaptured = true;
					break;
				}
				strcpy(stringVals[i], strHelper);
			}

			if( exitWasCaptured ) {
				extraMsg = CHARARR "Operation was cancelled.";
				break;
			}

			// Combine (concat) all the strings into one string.
			auto r = strTools::concatStr(stringVals[0], stringVals[1]);
			r = strTools::concatStr(r.get(), stringVals[2]);
			// Combine the final string with some extra output.
			r = strTools::concatStr(CHARARR "Concatenated string: ", r.get());
			strcpy(extraMsg, r.get());

			// Flush the stream.
			cout.flush();
			break;
		} // case 2
		case 3: // Search for a character in a string.
		{
			std::array<char*, 2> stringVals = { EMPTY_CHARARR, EMPTY_CHARARR };

			// This will return true if the input is '/exit'.
			auto getNextLine = [&stringVals](const uint64_t& i) {
				cout << CHARARR "> ";
				return helpers::userInputHandler(stringVals[i], STRING_MAX_SIZE);
				};

			// Start position of the string.
			int64_t startPos = 0;
			bool exitWasCaptured = false;

			cout << CHARARR
				"Enter a string and then a substring you want to find\n"
				"(type '/exit' at any moment to quit).\n"
				"The result will be shown after this operation ends.\n\n" << flush;
			cin.ignore();

			// Capture the first string. Since this can be anything,
			// there's no need to handle the input.
			if( getNextLine(0) ) {
				break;
			}

			// Capture the second string. Since this input must be handled,
			// start a 'do while' loop.
			do {
				// Exit the loop if user used the /exit command.
				if( getNextLine(1) ) {
					exitWasCaptured = true;
					break;
				}

				// Get the start position (i) by finding the first index.
				startPos = strTools::findSubStr(stringVals[0], stringVals[1]);
				if( startPos == -1 ) {
					cout << CHARARR "Substring not found in the original string!\n";
					continue;
				}
				break;
			} while( true );

			// This exits the switch case.
			if( exitWasCaptured ) {
				break;
			}

			// Get the number of characters to extract after `startPos` (j).
			uint64_t finalPos = strTools::len(stringVals[1]);
			// Extract the characters.
			auto finalString = strTools::subStr(stringVals[0], startPos, finalPos);

			// Copy the final string to the extra message in the main menu.
			auto r = strTools::concatStr(CHARARR "Extracted string: ", finalString.get());
			strcpy(extraMsg, r.get());

			// Flush the stream.
			cout.flush();
			break;
		} // case 3
		case 4: // Generate a substring from a string.
		{
			// Seed the random number engine with the current time.
			std::random_device rd;
			std::mt19937_64 gen(rd());
			// Define a lambda for random number generation within a specified range.
			auto getRand = [&gen](int64_t lower, int64_t upper) {
				std::uniform_int_distribution<uint64_t> distro(lower, upper);
				return distro(gen);
				};

			char* originalString = EMPTY_CHARARR;
			std::unique_ptr<char[]> subStrFromOriginal(new char[STRING_MAX_SIZE]);
			uint64_t strLen = 0ull, strLowIndex = 0ull, strUppIndex = 0ull;

			cout << CHARARR
				"Enter a string (type '/exit' at any moment to quit).\n"
				"The substring will be generated randomly.\n" << flush;
			cin.ignore();

			do {
				cout << CHARARR "> ";
				if( !helpers::userInputHandler(originalString, STRING_MAX_SIZE) ) {
					strLen = strTools::len(originalString);

					// Ensure valid indices.
					// This will never stop until there are valid indices.
					do {
						strLowIndex = getRand(0, strLen);
						strUppIndex = getRand(strLowIndex + 1, strLen + 1);
					} while( strLowIndex >= strUppIndex || strUppIndex > strLen );

					// Once the values are valid, get the substring.
					subStrFromOriginal = strTools::subStr(
						originalString, strLowIndex, strUppIndex - strLowIndex
					);
					cout << CHARARR
						"Extracted substring: '" << subStrFromOriginal.get() << "'\n" << flush;
				} else {
					break;
				}
			} while( true );

			// Flush the stream (just in case).
			cout.flush();
			break;
		} // case 4
		}; // switch ( selector )
	} while( mainLoop );

	cout << "Bye bye!" << endl;
	return 0;
}
