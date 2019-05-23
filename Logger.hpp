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

#include <string>
#include <iostream>
#include <memory>
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
	static std::shared_ptr<Logger> GetInstance();

	void SetLogPreferences(std::string logFileName,
						   LogLevel level,
						   LogOutput output);

	void Log(std::string codeFile, int codeLine, std::string message, LogLevel messageLevel);

	LogOutput GetLogOutput(const std::string& logOutput);
	LogLevel GetLogLevel(const std::string& logLevel);

private:
	LogLevel logLevel;
	LogOutput logOutput;
	std::ofstream logFile;

	static std::shared_ptr<Logger> loggerInstance;

	void LogMessage(const std::string& message);

};

#endif
