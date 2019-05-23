# simple_cpp_logger

This is a very straight forward CPP logger intended to reuse for basic projects to log messages on Console or determined file with determined message level including file name and line number. 

## Integration

Load Logger.hpp files into any of your directory. 

Include files to CMake source files list.

```cpp
set(LOGGER_SRC Logger.hpp Logger.cpp)
add_executable(application_binary app.cpp ${LOGGER_SRC})
```

You are good to go.

## How to use Logger.

This is a singleton design to keep File resources available through all objects and make sure single object can be accessiable by different objects at the same time using shared_ptr. 

For example, if you read logger configurations from a JSon file below could be a code snipped you can use.

```cpp
    #include "Logger.hpp"

    auto logger = Logger::GetInstance();
    
    auto logLevelStr = "ERROR"; // or WARN, DEBUG, INFO
    auto logLevel = logger->GetLogLevel(logLevelStr);

    auto logFile = "/home/user/logs/applog.txt";

    auto logOutputStr = "FILE"; // or CONSOLE
    auto logOutput = logger->GetLogOutput(logOutputStr);

    // One time log preferences
    logger->SetLogPreferences(logFile, logLevel, logOutput);
    
```

LogLevel, LogFile, LogOutput are configured with SetLogPreferences method.

When you need to call Log method below sample can be used:

```cpp
auto logger = Logger:GetInstance();

logger->Log(__FILE__, __LINE__, "Wrong Input Type Valid Values: A Z", LogLevel::ERROR);
```
