# StringTools

The `strTools` namespace provides a set of tools for manipulating C-style strings. These functions are designed to simplify common string operations, such as concatenation, substring extraction, insertion, deletion, searching, and replacement. The library ensures proper memory management using `std::unique_ptr<char[]>`.

## Index

- [StringTools](#stringtools)
  - [Index](#index)
  - [Overview](#overview)
  - [Namespace features](#namespace-features)
  - [Main function features](#main-function-features)
  - [Installation](#installation)
  - [Namespace Usage](#namespace-usage)
    - [Length Calculation](#length-calculation)
    - [Concatenation](#concatenation)
    - [Substring Extraction](#substring-extraction)
    - [Insertion](#insertion)
    - [Deletion](#deletion)
    - [Searching](#searching)
    - [Replacement](#replacement)
  - [Main function Usage](#main-function-usage)
    - [Menu Options](#menu-options)
    - [Example Usage](#example-usage)
    - [Input Handling](#input-handling)
    - [String Operations](#string-operations)
  - [Full Documentation](#full-documentation)
  - [License](#license)

## Overview

This project provides a string manipulation library to easily handle strings. It includes functions for calculating the length of a string, concatenating strings, searching for a substring, and generating substrings. The `main.cpp` file demonstrates examples of how to use this library through a simple console menu.

## Namespace features

- **Length Calculation:** Calculate the length of a C-string.
- **Concatenation:** Concatenate two C-strings into a new dynamically allocated string.
- **Substring Extraction:** Extract a substring from a C-string.
- **Insertion:** Insert one C-string into another at a specified position.
- **Deletion:** Remove a substring from a C-string.
- **Searching:** Find the first occurrence of a substring within a C-string.
- **Replacement:** Replace the first occurrence of a substring with another substring.

## Main function features

- **Calculate the Length of a String:** Enter a string and get its length.
- **Concatenate Strings:** Enter three strings and concatenate them.
- **Search for a Substring:** Enter a string and a substring to find its position within the string.
- **Generate a Substring:** Enter a string and generate a random substring from it.
- **Exit:** Exit the program.

## Installation

To use the `strTools` library, include the `strtools.hh` header in your C++ project:

```cpp
#include "src/strtools.hh"
// or
#include "strtools.hh"
```

Ensure that your project is set up to find the header file in its include path.

## Namespace Usage

### Length Calculation

Calculate the length of a C-string.

```cpp
const char* myString = "Hello, World!";
uint64_t length = strTools::len(myString);  // length will be 13
```

### Concatenation

Concatenate two C-strings into a new unique_ptr<char[]>.

```cpp
const char* str1 = "Hello, ";
const char* str2 = "World!";
auto result = strTools::concatStr(str1, str2);
// result will contain "Hello, World!"
```

### Substring Extraction

Extract a substring from a C-string.

```cpp
const char* myString = "Hello, World!";
auto sub = strTools::subStr(myString, 7, 5);
// sub will contain "World"
```

### Insertion

Insert one C-string into another at a specified position.

```cpp
const char* str1 = "Hello, World!";
const char* str2 = "Beautiful ";
auto result = strTools::insertStr(str1, str2, 8);
// result will contain "Hello, Beautiful World!"
```

### Deletion

Remove a substring from a C-string.

```cpp
const char* myString = "Hello, World!";
auto result = strTools::delSubStr(myString, 7, 6);
// result will contain "Hello, !"
```

### Searching

Find the first occurrence of a substring within a C-string.

```cpp
const char* myString = "Hello, World!";
int64_t index = strTools::findSubStr(myString, "World");
// index will be 7
```

### Replacement

Replace the first occurrence of a substring with another substring.

```cpp
const char* myString = "Hello, World!";
const char* sub1 = "World";
const char* sub2 = "Universe";
auto result = strTools::replaceStr(myString, sub1, sub2);
// result will contain "Hello, Universe!"
```

## Main function Usage

### Menu Options

1. **Calculate the Length of a String:**

   - Prompts the user to enter a string.
   - Calculates the length using `strTools::len`.

2. **Concatenate Three Strings:**

   - Prompts the user to enter three strings.
   - Concatenates them using `strTools::concatStr`.
   - Displays the concatenated result.

3. **Search for a Substring:**

   - Prompts the user to enter a string and a substring.
   - Searches for the substring using `strTools::findSubStr`.
   - Extracts the substring using `strTools::subStr`.
   - Displays the result or an error message if the substring is not found.

4. **Generate a Substring from a String:**

   - Prompts the user to enter a string.
   - Generates random start and end indices.
   - Extracts a substring using `strTools::subStr`.
   - Displays the extracted substring.

5. **Exit:**
   - Exits the program.

### Example Usage

1. Run the program.
2. Select an option by entering a number (0-4).
3. Follow the prompts to perform the desired operation.
4. View the result or error message.
5. Repeat until you choose to exit (option 0).

### Input Handling

The program uses the `helpers` namespace to manage invalid inputs, out-of-bounds values, and user input for different operations:

- **Invalid Input:** If the input is invalid (non-numeric), an error message is shown.
- **Out-of-Bounds Input:** If the input is not within the range [0, 4], an error message is shown.
- **User Input Handling:** Manages input from the user, including handling exit commands and input overflow.

### String Operations

The `strtools` namespace provides the following functions for string manipulation:

- **Length Calculation (`strTools::len`):** Calculates the length of a string.
- **Concatenation (`strTools::concatStr`):** Concatenates multiple strings.
- **Substring Search (`strTools::findSubStr`):** Finds the position of a substring within a string.
- **Substring Extraction (`strTools::subStr`):** Extracts a substring from a string based on start and end indices.

## Full Documentation

For more detailed documentation on the code, including function descriptions and usage, refer to the Doxygen documentation available [`here`](https://github.com/at-sso/StringTools/blob/master/docs/latex/refman.pdf).

## License

The `strTools` library is licensed under the GNU General Public License v3.0. For more details, see the GNU General Public License v3.0 file.
