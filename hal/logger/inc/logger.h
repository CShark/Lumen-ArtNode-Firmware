#pragma once

#include <source_location>

namespace logger {
    void init();
    void writeLog(const char *logLevel, const char *msg, const std::source_location source = std::source_location::current());

    void trace(const char *msg, const std::source_location source = std::source_location::current());
    void debug(const char *msg, const std::source_location source = std::source_location::current());
    void info(const char *msg, const std::source_location source = std::source_location::current());
    void warn(const char *msg, const std::source_location source = std::source_location::current());
    void error(const char *msg, const std::source_location source = std::source_location::current());
}