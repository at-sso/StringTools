#include <cstdint>
#include <iostream>
#include <memory>

#include "src/helpers.hh"
#include "src/strtools.hh"

constexpr int16_t STRING_MAX_SIZE = 100;

using std::cout, std::cin, std::endl;

int main() {
	bool mainLoop = true;
	// Value to be captured from the CLI.
	int32_t selector = 0;
	// Extra message.
	char* extraMsg = ( char[] )":D";

	while( mainLoop ) {
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
		case 0: // Exit
			mainLoop = false;
			break;
		case 1: // Calculate the length of a string.
			cout << "Enter a string (type '/exit' to quit).\n";
			while( true ) {
				// Captured user input values.
				str_p strLen(new char[STRING_MAX_SIZE]);
				if( helpers::captureAndCheck(strLen, STRING_MAX_SIZE) == 0 ) {
					break;
				}
				// Show the results.
				cout << "The lenght of '" << strLen.get() << "' is: "
					<< strTools::len(strLen.get()) << " > ";
				cout.flush();
			}
			break;
		case 2: // Concatenate three strings requested.
			break;
		case 3: // Search for a character in a string.
			break;
		case 4: // Generate a substring from a string.
			break;
		}
	};

	cout << "Bye bye!" << endl;
	return 0;
}
