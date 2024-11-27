#ifndef _LOGGER_H
#define _LOGGER_H

#include "utils.h"

template <typename T>
std::shared_ptr<T> castHandler(std::shared_ptr<BaseUtils> handler);

class Logger : public BaseUtils, protected Handlers {
private:
    Level m_Level;
    const std::string logger_name;
    friend struct LoggerHelper;
public:
    Logger(const std::string& filename) : logger_name(filename), m_Level(LogLevelDefault) {};
    void addHandler(std::shared_ptr<BaseUtils> handler);
    static std::string PrepareLog(std::shared_ptr<BaseUtils> Handler, Level level, std::string message);
    void GetInfo() override;
    std::shared_ptr<BaseUtils> StreamHandler(Level loglevel,const char* datefmt, std::string formatter="date::level::message");
    std::shared_ptr<BaseUtils> FileHandler(Level loglevel, const char* datefmt, std::string formatter="date::level::message");

    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);
    ~Logger() = default;
};

struct LoggerHelper {
private:
    LoggerHelper() = default;
public:
    static Configs::Level getLevel(std::shared_ptr<BaseUtils> handler);
    static void setLevel(std::shared_ptr<BaseUtils> handler, Configs::Level level);
    static const std::string getLoggerName(const std::shared_ptr<Logger> logger);
    static void setFormatter(std::shared_ptr<BaseUtils> handler, const std::string& format);
};

#endif