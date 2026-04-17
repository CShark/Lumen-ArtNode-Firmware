#include "logger.h"
#include "hal/systick.h"
#include "segger_rtt.h"
#include <cstdio>
#include <ctime>
#include <source_location>

namespace logger {
    enum class LogLevel {
        Trace = 0,
        Debug,
        Info,
        Warn,
        Error,
        None,
    };

#if defined(LEVEL_TRACE)
    static const constexpr LogLevel logLevel = LogLevel::Trace;
#elif defined(LEVEL_DEBUG)
    static const constexpr LogLevel logLevel = LogLevel::Debug;
#elif defined(LEVEL_INFO)
    static const constexpr LogLevel logLevel = LogLevel::Info;
#elif defined(LEVEL_WARN)
    static const constexpr LogLevel logLevel = LogLevel::Warn;
#elif defined(LEVEL_ERR)
    static const constexpr LogLevel logLevel = LogLevel::Error;
#else
    static const constexpr LogLevel logLevel = LogLevel::None;
#endif

    static void getTimestamp(char buffer[15]) {
        time_t seconds = static_cast<time_t>(hal::systick::sys_now() / 1000);
        uint32_t ms = static_cast<uint32_t>(hal::systick::sys_now() % 1000);

        struct tm tm_utc;
        gmtime_r(&seconds, &tm_utc);

        snprintf(buffer, 15, "%02d:%02d:%02d.%03u: ",
                 tm_utc.tm_hour,
                 tm_utc.tm_min,
                 tm_utc.tm_sec,
                 ms);
    }

    void init() {
        if constexpr (logLevel < LogLevel::None) {
            SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_NO_BLOCK_SKIP);
            SEGGER_RTT_WriteString(0, "\033[90m\n\033[0mDebug session started\033[90m\n");
        }
    }

    void writeLog(const char *logLevel, const char *msg, const std::source_location source) {
        char timestamp[15]{0};
        char linenumber[5]{0};

        snprintf(linenumber, sizeof(linenumber), "%d", source.line());

        getTimestamp(timestamp);

        SEGGER_RTT_WriteString(0, timestamp);
        SEGGER_RTT_WriteString(0, logLevel);
        SEGGER_RTT_WriteString(0, msg);

        SEGGER_RTT_WriteString(0, " \033[90m(");
        SEGGER_RTT_WriteString(0, source.file_name());
        SEGGER_RTT_WriteString(0, " > ");
        SEGGER_RTT_WriteString(0, source.function_name());
        SEGGER_RTT_WriteString(0, ": ");
        SEGGER_RTT_WriteString(0, linenumber);
        SEGGER_RTT_WriteString(0, ")\033[90m\n");
    }

    void trace(const char *msg, const std::source_location source) {
        if constexpr (logLevel <= LogLevel::Trace) {
            writeLog("[TRACE] ", msg, source);
        }
    }

    void debug(const char *msg, const std::source_location source) {
        if constexpr (logLevel <= LogLevel::Debug) {
            logger::writeLog("\033[97m[DEBUG]\033[0m ", msg, source);
        }
    }

    void info(const char *msg, const std::source_location source) {
        if constexpr (logLevel <= LogLevel::Info) {
            writeLog("\033[34m[INFO]\033[0m  ", msg, source);
        }
    }

    void warn(const char *msg, const std::source_location source) {
        if constexpr (logLevel <= LogLevel::Warn) {
            writeLog("\033[33m[WARN]\033[0m  ", msg, source);
        }
    }

    void error(const char *msg, const std::source_location source) {
        if constexpr (logLevel <= LogLevel::Error) {
            writeLog("\033[31m[ERROR]\033[0m ", msg, source);
        }
    }
}