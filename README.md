# simple_cpp_logger

This is a very straight forward CPP logger intended to reuse for basic projects to log messages on Console or determined file.

## Integration

Load Logger.hpp and Logger.cpp files into any of your directory. 

Include files to CMake source files list.

```cpp
set(LOGGER_SRC Logger.cpp Logger.hpp)
add_executable(application_binary app.cpp ${LOGGER_SRC})
```

You are good to go.

## How to use Logger.

This is a singleton design to keep File resources available through all objects and make sure single object can be accessiable by different objects at the same time using shared_ptr. 

For example, if you read logger configurations from a JSon file below could be a code snipped you can use.

```cpp

    auto logLevelStr = config["logger"]["log_level"].string_value();
    auto logLevel = logger->GetLogLevel(logLevelStr);

    auto logFile = config["logger"]["log_file"].string_value();

    auto logOutputStr = config["logger"]["log_output"].string_value();
    auto logOutput = logger->GetLogOutput(logOutputStr);

    logger->SetLogPreferences(logFile, logLevel, logOutput);
```

LogLevel, LogFile, LogOutput are configured with SetLogPreferences method.

When you need to call Log method below sample can be used:

```cpp
logger->Log(__FILE__, __LINE__, "Wrong Input Type Valid Values: A Z", LogLevel::ERROR);
```
