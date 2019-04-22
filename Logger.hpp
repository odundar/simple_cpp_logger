/*
// Copyright (c) 2019 Onur Dundar
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
*/

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <memory>
#include <iostream>
#include <fstream>

enum class LogLevel {
	NONE = 0,
	ERROR = 1,
	WARN = 2,
	INFO = 3,
	DEBUG = 4
};

enum class LogOutput {
	CONSOLE,
	FILE
};

/**
* Logger Class Used to Output Details of Current Application Flow
*/
class Logger {
public:

	/**
	* Initial Setup for Logger
	* @param logFile
	* @param level
	* @param output
	*/
	void SetLogPreferences(std::string logFile = "",
		LogLevel level = LogLevel::ERROR,
		LogOutput output = LogOutput::CONSOLE) {
		logLevel = level;
		logOutput = output;

		if (logOutput == LogOutput::FILE && !logFile.empty()) {
			file.open(logFile);
			if (!file.good()) {
				std::cerr << "Can't Open Log File" << std::endl;
				logOutput = LogOutput::CONSOLE;
			}
		}
	}

	/**
	* Get Single Instance of Performance Monitor
	* @return
	*/
	static std::shared_ptr<Logger> GetInstance() {
		if (loggerInstance == nullptr) {
			loggerInstance = std::shared_ptr<Logger>(new Logger());
		}

		return loggerInstance;
	}

	/**
	* Log message, set its level
	* @param message
	* @param messageLevel
	*/
	void Log(std::string code_file, int code_line, std::string message, LogLevel messageLevel = LogLevel::DEBUG) {
		if (messageLevel <= logLevel) {
			std::string logType;
			//Set Log Level Name
			switch (messageLevel) {
			case LogLevel::DEBUG:
				logType = "DEBUG: ";
				break;
			case LogLevel::INFO:
				logType = "INFO: ";
				break;
			case LogLevel::WARN:
				logType = "WARN: ";
				break;
			case LogLevel::ERROR:
				logType = "ERROR: ";
				break;
			default:
				logType = "NONE: ";
				break;
			}
			code_file += " : " + std::to_string(code_line) + " : ";
			message = logType + code_file + message;

			LogMessage(message);
		}
	}

	/**
	* Convert String Representation of Log Level to LogLevel Type
	* @param logLevel : String log level
	* @return LogLevel
	*/
	LogLevel GetLogLevel(const std::string& logLevel) {
		if (logLevel == "DEBUG") {
			return LogLevel::DEBUG;
		}
		else if (logLevel == "INFO") {
			return LogLevel::INFO;
		}
		else if (logLevel == "WARN") {
			return LogLevel::ERROR;
		}
		else if (logLevel == "ERROR") {
			return LogLevel::ERROR;
		}
		return LogLevel::NONE;
	}

	/**
	* Convert String Representation of Log Output to LogOutput Type
	* @param logOutput : String log output
	* @return LogOutput
	*/
	LogOutput GetLogOutput(const std::string& logOutput) {
		if (logOutput == "FILE") {
			return LogOutput::FILE;
		}

		return LogOutput::CONSOLE;
	}

private:
	LogLevel logLevel;
	LogOutput logOutput;
	std::ofstream file;

	static std::shared_ptr<Logger> loggerInstance;

	Logger() {}

	void LogMessage(const std::string& message) {
		if (logOutput == LogOutput::FILE) {
			file << message << std::endl;
		}
		else {
			std::cout << message << std::endl;
		}
	}
};
#endif
