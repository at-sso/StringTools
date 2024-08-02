/**
 * @file main.cpp
 * @author Zperk
 * @brief Examples on how to use the strtools.hh header.
 * @version 1.0.1
 * @date 2024-07-28
 *
 * @copyright Copyright (c) zperk 2024
 *
 */

#include "src/.hxx"
#include <array>
#include <cstdint>
#include <iostream>
#include <istream>
#include <memory>
#include <new>
#include <random>
#include <string>
#include <string.h>

 /// @brief String max input size
static constexpr int16_t _STRING_MAX_SIZE = 256;
/// @brief Reference to `__StrUtilExtra.log(...)`.
static void _logger(const std::string& s, __StrToolsLogLvl lvl = __StrToolsLogLvl::INFO) {
	return _strLogger("int main()", s, lvl);
}

using std::cout, std::cin, std::endl, std::flush;
using std::string;
using std::unique_ptr, std::make_unique;

/**
 * @brief Main function demonstrating examples on how to use the strtools.hh header.
 *
 * The main function provides a console menu to the user with various string manipulation options.
 * The user can choose to calculate the length of a string, concatenate strings, search for a
 * substring, or generate a substring from a string. The main loop continues until the user chooses
 * to exit.
 *
 * The main function works as follows:
 *
 * - Initialization:
 *   - `mainLoop`: A boolean variable to control the main loop.
 *   - `selector`: An integer to capture the user's menu choice.
 *   - `extraMsg`: A character pointer initialized with a smiley face.
 *
 * - Main Loop:
 *   The loop will continue to display the menu, handle user input, and perform the chosen operation
 *   until the user decides to exit.
 *
 *   @code
 *   do {
 *       strUtil::clearScr();
 *       cout <<
 *           "1. Calculate the length of a string.\n"
 *           "2. Concatenate three strings requested.\n"
 *           "3. Search for a character in a string.\n"
 *           "4. Generate a substring from a string.\n"
 *           "0. Exit.\n"
 *           << extraMsg << "\n\n> " << flush;
 *       cin >> selector;
 *   @endcode
 *
 * - Input Validation:
 *   - Invalid Input: If the input is invalid (non-numeric), an error message is shown.
 *   - Out-of-Bounds Input: If the input is not within the range [0, 4], an error message is shown.
 *
 *   @code
 *   if( strUtil::isCapturedValueInvalid() ) {
 *       extraMsg = "Value is invalid!";
 *       continue;
 *   }
 *   if( strUtil::isOutOfBounds(selector, 0, 4) ) {
 *       extraMsg = "Value is out of bounds!";
 *       continue;
 *   }
 *   @endcode
 *
 * - Menu Options:
 *   Depending on the user's choice, different cases in the switch statement are executed:
 *
 *   - Case 0: Exit the program by setting `mainLoop` to `false`.
 *   - Case 1: Calculate the length of a string.
 *   - Case 2: Concatenate three user-input strings.
 *   - Case 3: Search for a substring within a string.
 *   - Case 4: Generate a random substring from a user-input string.
 *
 *   @code
 *   switch( selector ) {
 *   case 0:
 *       mainLoop = false;
 *       break;
 *   case 1:
 *       // Code for calculating the length of a string
 *       break;
 *   case 2:
 *       // Code for concatenating three strings
 *       break;
 *   case 3:
 *       // Code for searching for a substring in a string
 *       break;
 *   case 4:
 *       // Code for generating a substring from a string
 *       break;
 *   }
 *   @endcode
 *
 * - Case Details:
 *   - Case 1: Calculate the Length of a String:
 *       Prompts the user to enter a string and calculates its length using `strTools::len`.
 *   - Case 2: Concatenate Three Strings:
 *       Prompts the user to enter three strings, concatenates them using `strTools::concatStr`, and
 *       displays the result.
 *   - Case 3: Search for a Character in a String:
 *       Prompts the user to enter a string and a substring, then searches for the substring using
 *       `strTools::findSubStr` and extracts it using `strTools::subStr`.
 *   - Case 4: Generate a Substring from a String:
 *       Prompts the user to enter a string, generates random start and end indices, and extracts a
 *       substring using `strTools::subStr`.
 *
 * - Ending the Program:
 *   After the loop exits, a farewell message is displayed, and the program terminates.
 *
 *   @code
 *   cout << "Bye bye!" << endl;
 *   return 0;
 *   @endcode
 *
 * Example Use:
 * 1. The user starts the program, and the main menu is displayed.
 * 2. The user selects an option by entering a number (0-4).
 * 3. The program performs the corresponding operation and displays the result or an error message
 *    if applicable.
 * 4. The menu is displayed again, allowing the user to make another selection.
 * 5. The loop continues until the user selects the exit option (0).
 *
 * Key Points:
 * - Input Handling: The program uses the `helpers` namespace to manage invalid inputs, out-of-bounds
 *   values, and user input for different operations.
 * - String Operations: The `strtools` namespace provides functions for string length calculation,
 *   concatenation, substring search, and substring extraction.
 * - Menu Loop: The main loop ensures the user can repeatedly perform operations until they choose to exit.
 */
int main() {
	bool mainLoop = true;
	// __strToolsLogger.toggleLogger(); // Uncomment this for debbugging.
	__strToolsLogger.setLogFile("./src/_dump.log");
	// Value to be captured from the CLI.
	int32_t selector = 0;
	// Extra message.
	string extraMsg = ":D";

	do {
		_logger("main loop started");
		strUtil::clearScr();
		cout <<
			"1. Calculate the length of a string.\n"
			"2. Concatenate three strings requested.\n"
			"3. Search for a character in a string.\n"
			"4. Generate a random substring from a string.\n"
			"0. Exit.\n"
			<< extraMsg << "\n\n> " << flush;
		cin >> selector;

		// Check if the captured value is invalid.
		if( strUtil::isCapturedValueInvalid() ) {
			extraMsg = "Value is invalid!";
			_logger(extraMsg, __StrToolsLogLvl::WARNING);
			continue;
		}

		cout.flush();

		switch( selector ) {
		default: extraMsg = "Value is out of bounds!"; _logger(extraMsg, __StrToolsLogLvl::WARNING); break;
		case -1: __strToolsLogger.toggleLogger(); break;
		case 0: mainLoop = false; break;
		case 1: // Calculate the length of a string.
		{
			_logger("case 1 started.");
			// Initialize a smart pointer to handle the string lenght.
			uniqueStr strLen(new char[_STRING_MAX_SIZE]);

			cout << "Enter a string (type '/exit' to quit).\n" << flush;
			cin.ignore();

			// Start the operation.
			while( true ) {
				cout << "> ";
				// Call the user input handler.
				if( strUtil::userInputHandler(strLen.get(), _STRING_MAX_SIZE) )
					break;

				// Show the results.
				cout <<
					"The length of '" << strLen.get() << "' is: "
					<< strlen(strLen.get()) << "\n";
			};

			// Flush the stream.
			cout.flush();
			_logger("case 1 ended.");
			break;
		} // case 1
		case 2: // Concatenate three strings requested.
		{
			_logger("case 2 started.");
			// Array values to be modified by the user.
			std::array<uniqueStr, 3> stringVals = {
				strUtil::makeSmartPtrArray<uniqueStr>(_STRING_MAX_SIZE),
				strUtil::makeSmartPtrArray<uniqueStr>(_STRING_MAX_SIZE),
				strUtil::makeSmartPtrArray<uniqueStr>(_STRING_MAX_SIZE),
			};

			// This helper allows the array values to be modified easily.
			uniqueStr strHelper(new char[_STRING_MAX_SIZE]);
			bool exitWasCaptured = false;

			cout <<
				"Enter 3 strings (type '/exit' at any moment to quit).\n"
				<< flush;
			cin.ignore();

			// Start the operation.
			for( int16_t i = 0; i < 3; ++i ) {
				cout << "> ";
				if( strUtil::userInputHandler(strHelper.get(), _STRING_MAX_SIZE) ) {
					exitWasCaptured = true;
					break;
				}
				strcpy(stringVals[i].get(), strHelper.get());
			}

			if( exitWasCaptured ) {
				extraMsg = "Operation was cancelled.";
				_logger(extraMsg + "at case 2.");
				break;
			}

			// Combine (concat) all the strings into one string.
			auto r = strTools::concatStr(stringVals[0].get(), stringVals[1].get());
			r = strTools::concatStr(r.get(), stringVals[2].get());
			// Combine the final string with some extra output.
			r = strTools::concatStr("Concatenated string: ", r.get());
			extraMsg = r.get();

			// Flush the stream.
			cout.flush();
			_logger("case 2 ended.");
			break;
		} // case 2
		case 3: // Search for a character in a string.
		{
			_logger("case 3 started.");
			std::array<uniqueStr, 2> stringVals = {
				strUtil::makeSmartPtrArray<uniqueStr>(_STRING_MAX_SIZE),
				strUtil::makeSmartPtrArray<uniqueStr>(_STRING_MAX_SIZE),
			};

			// This will return true if the input is '/exit'.
			auto getNextLine = [&stringVals](const uint64_t& i) {
				cout << "> ";
				return strUtil::userInputHandler(stringVals[i].get(), _STRING_MAX_SIZE);
				};

			// Start position of the string.
			int64_t startPos = 0;
			bool exitWasCaptured = false;

			cout <<
				"Enter a string and then a substring you want to find\n"
				"(type '/exit' at any moment to quit).\n"
				"The result will be shown after this operation ends.\n\n"
				<< flush;
			cin.ignore();

			// Capture the first string. Since this can be anything,
			// there's no need to handle the input.
			if( getNextLine(0) ) {
				break;
			}

			// Capture the second string. Since this input must be handled,
			// start a 'while' loop.
			while( true ) {
				// Exit the loop if user used the /exit command.
				if( getNextLine(1) ) {
					exitWasCaptured = true;
					break;
				}

				// Get the start position (i) by finding the first index.
				startPos = strTools::findSubStr(stringVals[0].get(), stringVals[1].get());
				if( startPos == -1 ) {
					cout << "Substring not found in the original string!\n";
					continue;
				}
				break;
			};

			// This exits the switch case.
			if( exitWasCaptured ) {
				break;
			}

			// Get the number of characters to extract after `startPos` (j).
			uint64_t finalPos = strlen(stringVals[1].get());
			// Extract the characters.
			auto finalString = strTools::subStr(stringVals[0].get(), startPos, finalPos);

			// Copy the final string to the extra message in the main menu.
			auto r = strTools::concatStr("Extracted string: ", finalString.get());
			extraMsg = r.get();

			// Flush the stream.
			cout.flush();
			_logger("case 3 ended.");
			break;
		} // case 3
		case 4: // Generate a substring from a string.
		{
			_logger("case 4 started.");
			// Seed the random number engine with the current time.
			std::random_device rd;
			std::mt19937_64 gen(rd());
			// Define a lambda for random number generation within a specified range.
			auto getRand = [&gen](int64_t lower, int64_t upper) {
				std::uniform_int_distribution<uint64_t> distr(lower, upper);
				return distr(gen);
				};

			uniqueStr originalString(new char[_STRING_MAX_SIZE]);
			uniqueStr subStrFromOriginal(new char[_STRING_MAX_SIZE]);
			uint64_t strLen = 0ull, strLowIndex = 0ull, strUppIndex = 0ull;

			cout <<
				"Enter a string (type '/exit' at any moment to quit).\n"
				"The substring will be generated randomly.\n"
				<< flush;
			cin.ignore();

			while( true ) {
				cout << "> ";
				if( !strUtil::userInputHandler(originalString.get(), _STRING_MAX_SIZE) ) {
					strLen = strlen(originalString.get());

					// Ensure valid indices.
					// This will never stop until there are valid indices.
					do {
						strLowIndex = getRand(0, strLen);
						strUppIndex = getRand(strLowIndex + 1, strLen + 1);
					} while( strLowIndex >= strUppIndex || strUppIndex > strLen );

					// Once the values are valid, get the substring.
					subStrFromOriginal = strTools::subStr(
						originalString.get(), strLowIndex, strUppIndex - strLowIndex
					);
					cout <<
						"Extracted substring: '" << subStrFromOriginal.get() << "'\n"
						<< flush;
				} else break;
			};

			// Flush the stream (just in case).
			cout.flush();
			_logger("case 4 ended.");
			break;
		} // case 4
		}; // switch ( selector )
	} while( mainLoop );

	cout << "Bye bye!" << endl;
	_logger("main loop ended.");
	return 0;
}
