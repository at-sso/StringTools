/**
 * @file main.cpp
 * @author Zperk
 * @brief Logging tools.
 * @version 1.0.1
 * @date 2024-08-02
 *
 * @copyright Copyright (c) zperk 2024
 *
 */

#pragma once

#include <ctime>
#include <fstream>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <string>

using std::cout, std::cerr, std::endl;
using std::string;
using std::ofstream;

enum class __StrToolsLogLvl {
	INFO = 0,
	WARNING = 1,
	ERROR = 2,
};

class __StrLogger {
private:
	ofstream logFile;
	bool isFileOpen;
	bool isLoggerEnabled;

	/**
	 * @brief Gets the current timestamp.
	 *
	 * This function retrieves the current time and formats it
	 * as a string in the format "YYYY-MM-DD HH:MM:SS".
	 *
	 * @return A string containing the formatted timestamp.
	 */
	string getTimestamp() {
		time_t now = std::time(nullptr);
		char buf[20];
		std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
		return string(buf);
	}

	/**
	 * @brief Converts log level to string.
	 *
	 * This function converts the given log level to its corresponding
	 * string representation.
	 *
	 * @param level The log level to convert.
	 * @return A string representing the log level.
	 */
	string logLevelToString(__StrToolsLogLvl level) noexcept {
		switch( level ) {
		case __StrToolsLogLvl::INFO: return "INFO";
		case __StrToolsLogLvl::WARNING: return "WARNING";
		case __StrToolsLogLvl::ERROR: return "ERROR";
		default: return "UNKNOWN";
		} // switch( level )
	}

public:
	/**
	 * @brief Constructs the logger.
	 *
	 * This constructor initializes the logger with file closed and logger
	 * disabled.
	 */
	__StrLogger() : isFileOpen(false), isLoggerEnabled(false) {}

	/**
	 * @brief Destructs the logger.
	 *
	 * This destructor ensures that if the log file is open, it is properly
	 * flushed and closed.
	 */
	~__StrLogger() {
		if( isFileOpen ) {
			logFile.flush();
			logFile.close();
		}
	}

	/**
	 * @brief Toggles the logger state.
	 *
	 * This function enables or disables the logger.
	 */
	void toggleLogger() noexcept {
		isLoggerEnabled = !isLoggerEnabled;
	}

	/**
	 * @brief Gets the logger status.
	 *
	 * This function returns the current status of the logger.
	 *
	 * @return True if the logger is enabled, false otherwise.
	 */
	bool loggerStatus() const noexcept {
		return isLoggerEnabled;
	}

	/**
	 * @brief Sets the log file.
	 *
	 * This function sets the log file to the provided filename. If a log file
	 * is already open, it closes it before opening the new file.
	 *
	 * @param filename The name of the file to log to.
	 */
	void setLogFile(const string& filename) noexcept {
		if( !isLoggerEnabled ) return;
		// If the same filename is provided, close the file.
		if( isFileOpen )
			logFile.close();
		// Else, open the file and check if it's open.
		logFile.open(filename, std::ios::out | std::ios::trunc);
		if( logFile.is_open() ) {
			isFileOpen = true;
		} else { // If it failed, show an error in the terminal.
			cerr << "Failed to open log file: " << filename << endl;
			isFileOpen = false;
		}
	}

	/**
	 * @brief Logs a message.
	 *
	 * This function logs a message with the given log level. It formats the
	 * message with a timestamp and the log level, then writes it to the log
	 * file and the terminal.
	 *
	 * @param level The log level of the message.
	 * @param message The message to log.
	 */
	void log(__StrToolsLogLvl level, const string& message) {
		if( !isLoggerEnabled ) return;
		// Format the message
		string logMessage = getTimestamp() + " [" + logLevelToString(level) + "] " + message;
		// Show the log in the terminal.
		cout << logMessage << endl;
		// Then, dump the message into the file.
		if( isFileOpen ) logFile << logMessage << "\n";
	}
} __strToolsLogger;
