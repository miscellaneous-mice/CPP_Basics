#ifndef _LOGGER_H
#define _LOGGER_H

#include "utils.h"

template <typename T>
T* castHandler(void* handler);

class Logger : public BaseUtils, protected Handlers {
private:
    Level m_Level;
    const std::string logger_name;
    friend struct LoggerHelper;
public:
    Logger(const std::string& filename) : logger_name(filename), m_Level(LogLevelDefault) {};
    void addHandler(void* handler);
    static std::string PrepareLog(void* Handler, std::string message);
    void GetInfo() override;
    BaseUtils* StreamHandler(Level loglevel,const char* datefmt, std::string formatter="date::level::message");
    BaseUtils* FileHandler(Level loglevel, const char* datefmt, std::string formatter="date::level::message");

    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);
    ~Logger() = default;
};

struct LoggerHelper {
private:
    LoggerHelper() = default;
public:
    static Configs::Level getLevel(void* handler);
    static void setLevel(void* handler, Configs::Level level);
    static const std::string getLoggerName(const Logger* logger);
    static void setFormatter(void* handler, const std::string& format);
};

#endif