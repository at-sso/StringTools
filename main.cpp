#include <cstdint>
#include <iostream>

#include "src/helpers.hh"
#include "src/strtools.hh"


using std::cout, std::cin, std::endl;

int main() {
	// Value to be captured from the CLI.
	int32_t selector = 0;
	bool mainLoop = true;

	do{
		cout <<
			"1. Calculate the length of a string.\n"
			"2. Concatenate three strings requested.\n"
			"3. Search for a character in a string.\n"
			"4. Generate a substring from a string.\n"
			"0. Exit.\n"
			"> ";
		cin >> selector;

		// Check if the captured value is invalid.
		if( helpers::isCapturedValueInvalid() ) {
			cout << "Value is invalid!" << endl;
			continue;
		}

		// Check if the captured value is out of bounds.
		if( helpers::isOutOfBounds(selector, 0, 4) ) {
			cout << "Value is out of bounds!" << endl;
			continue;
		}

		// If everything is correct, flush the stream and continue.
		cout.flush();

		switch( selector ) {
		case 0: // Exit
			mainLoop = false;
			break;
		case 1: // Calculate the length of a string.
			break;
		case 2: // Concatenate three strings requested.
			break;
		case 3: // Search for a character in a string.
			break;
		case 4: // Generate a substring from a string.
			break;
		}
	} while( mainLoop );

	cout << "Bye bye!" << endl;
	return 0;
}
