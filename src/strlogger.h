/**
 * @file main.cpp
 * @author Zperk
 * @brief Logging tools.
 * @version 1.0.0
 * @date 2024-08-02
 *
 * @copyright Copyright (c) zperk 2024
 *
 */

#pragma once

#include <corecrt.h>
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
	INFO,
	WARNING,
	ERROR
};

class __StrLogger {
private:
	ofstream logFile;
	bool isFileOpen;
	bool isLoggerEnabled;

	string getTimestamp() {
		time_t now = std::time(nullptr);
		char buf[20];
		std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
		return string(buf);
	}

	string logLevelToString(__StrToolsLogLvl level) noexcept {
		switch( level ) {
		case __StrToolsLogLvl::INFO: return "INFO";
		case __StrToolsLogLvl::WARNING: return "WARNING";
		case __StrToolsLogLvl::ERROR: return "ERROR";
		default: return "UNKNOWN";
		} // switch( level )
	}

public:
	__StrLogger() : isFileOpen(false), isLoggerEnabled(false) {}
	~__StrLogger() {
		if( isFileOpen ) {
			logFile.flush();
			logFile.close();
		}
	}

	// If called, the logger will be enabled or disabled.
	void toggleLogger() noexcept {
		isLoggerEnabled = !isLoggerEnabled;
	}

	bool loggerStatus() const noexcept {
		return isLoggerEnabled;
	}

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
