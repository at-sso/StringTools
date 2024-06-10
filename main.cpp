#include <array>
#include <cstdint>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string.h>

#include "src/helpers.hh"
#include "src/strtools.hh"

constexpr int16_t STRING_MAX_SIZE = 100;

using std::cout, std::cin, std::endl;
using strTools::str, strTools::strptr;

int main() {
	bool mainLoop = true;
	// Value to be captured from the CLI.
	int32_t selector = 0;
	// Extra message.
	str extraMsg = ( char[] ) ":D";

	do {
		helpers::clearScr();
		cout <<
			"1. Calculate the length of a string.\n"
			"2. Concatenate three strings requested.\n"
			"3. Search for a character in a string.\n"
			"4. Generate a substring from a string.\n"
			"0. Exit.\n"
			<< extraMsg << "\n\n> ";
		cin >> selector;

		// Check if the captured value is invalid.
		if( helpers::isCapturedValueInvalid() ) {
			extraMsg = ( char[] ) "Value is invalid!";
			continue;
		}

		// Check if the captured value is out of bounds.
		if( helpers::isOutOfBounds(selector, 0, 4) ) {
			extraMsg = ( char[] ) "Value is out of bounds!";
			continue;
		}

		// If everything is correct, flush the stream and continue.
		cout.flush();

		switch( selector ) {
		case 0: { // Exit
			mainLoop = false;
			break;
		}
		case 1: { // Calculate the length of a string.
			strptr strLen(new char[STRING_MAX_SIZE]);

			cout << "Enter a string (type '/exit' to quit).\n";
			cin.ignore();

			// Start the operation.
			while( true ) {
				cout << "> ";
				// Captured user input values.
				cin.getline(strLen.get(), STRING_MAX_SIZE);
				if( helpers::checkCapturedValue(strLen.get()) == 0 ) {
					break;
				}
				// Show the results.
				cout << "The lenght of '" << strLen.get() << "' is: "
					<< strTools::len(strLen.get()) << "\n";
			}

			// Flush the stream.
			cout.flush();
			break;
		}
		case 2: { // Concatenate three strings requested.
			std::array<str, 3> stringVals = { ( char[] ) "", ( char[] ) "", ( char[] ) "" };
			str strHelper = ( char[] ) "";
			bool exitWasCaptured = false;

			cout << "Enter 3 strings (type '/exit' at any moment to quit).\n"
				"The result will be shown after this operation ends.\n\n";
			cin.ignore();

			// Start the operation.
			for( int16_t i = 0; i < 3; ++i ) {
				cout << "> ";
				cin.getline(strHelper, STRING_MAX_SIZE);
				try {
					if( helpers::checkCapturedValue(strHelper) == 0 ) {
						exitWasCaptured = true;
						break;
					}
				} catch( const std::runtime_error& e ) {
					std::cerr << e.what() << endl;
					--i; // Retry the same iteration
					continue;
				}
				strcpy(stringVals[i], strHelper);
			}

			// Combine (concat) all the strings into one string.
			if( !exitWasCaptured ) {
				strptr r = strTools::concatStr(stringVals[0], stringVals[1]);
				r = strTools::concatStr(r.get(), stringVals[2]);
				r = strTools::concatStr(( char[] ) "Concatenated string: ", r.get());
				strcpy(extraMsg, r.get());
			} else {
				extraMsg = ( char[] ) "Operation was cancelled.";
			}

			// Flush the stream.
			cout.flush();
			break;
		}
		case 3: { // Search for a character in a string.
			std::array<str, 2> stringVals = { ( char[] ) "", ( char[] ) "" };

			auto getNextLine = [&](const char s[], const uint64_t& i) {
				cout << s;
				cin.ignore();
				cin.getline(stringVals[i], STRING_MAX_SIZE);
				return helpers::checkCapturedValue(stringVals[i]);
				};

			int64_t startPos = 0;

			cout << "Enter a string and then a substring you want to find\n"
				"(type '/exit' at any moment to quit).\n"
				"The result will be shown after this operation ends.\n\n";

			// Capture the first string.
			getNextLine("> ", 0);

			while( true ) {
				// Capture the second string.
				getNextLine("> ", 1);

				// Get the start position (i) by finding the first index.
				startPos = strTools::findSubStr(stringVals[0], stringVals[1]);
				if( startPos == -1 ) {
					cout << "Substring not found.";
					continue;
				}
				break;
			}
			//if( !secondStringExit ) {
			//	break; // The switch case.
			//}

			// Get the number of characters to extract after `startPos` (j).
			uint64_t finalPos = strTools::len(stringVals[1]);

			/* To avoid undefined behavior, first check if the arithmetic
			 * values of the string are not equal to the maximum number of 64bits.*/
			if( startPos - 1 == INT64_MAX ) {
				startPos++;
			}

			// Extract the chracters.
			strptr finalString = strTools::subStr(stringVals[0], startPos - 1, finalPos + 1);

			// Copy the final string to the extra message in the main menu.
			strptr r = strTools::concatStr(( char[] ) "Extracted string: ", finalString.get());
			strcpy(extraMsg, r.get());

			// Flush the stream.
			cout.flush();
			break;
		}
		case 4: { // Generate a substring from a string.
			break;
		}
		}; // switch ( selector )
	} while( mainLoop );
	cout << "Bye bye!" << endl;
	return 0;
}
