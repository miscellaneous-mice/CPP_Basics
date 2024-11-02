#include <iostream>
#include <string>

// Forward declaration of the access struct
struct LoggerAccessor;

class Logger {
public:
    enum Level {
        LogLevelInfo = 0, LogLevelWarning, LogLevelError
    };

private:
    const char* logger_name;
    Level m_Level;

    // Declare LoggerAccessor as a friend struct to allow access to private members
    friend struct LoggerAccessor;

public:
    static std::string decorator;

    // Constructor with logger name
    Logger(const char* logger_name) : m_Level(LogLevelInfo), logger_name(logger_name) {
        std::cout << "Initialized Logger: " << logger_name << std::endl;
    }

    static void setLogLevel(Logger& logger, Level level) {
        logger.m_Level = level;
    }

    virtual void GetInfo() {
        std::cout << "Logger: " << logger_name << std::endl;
    }

    void Info(const std::string& message) {
        std::cout << decorator << "[INFO]: " << message << std::endl;
    }

    void Warning(const std::string& message) {
        std::cout << decorator << "[WARNING]: " << message << std::endl;
    }

    void Error(const std::string& message) {
        std::cout << decorator << "[ERROR]: " << message << std::endl;
    }
};

// Static member initialization
std::string Logger::decorator;

// Struct that can access Logger's private members
struct LoggerAccessor {
    static Logger::Level getLevel(const Logger& logger) {
        return logger.m_Level;  // Access private member m_Level
    }

    static void setLevel(Logger& logger, Logger::Level level) {
        logger.m_Level = level;  // Modify private member m_Level
    }

    static const char* getLoggerName(const Logger& logger) {
        return logger.logger_name;  // Access private member logger_name
    }
};

class Printer : public Logger {
public:
    static std::string message;

    // Constructor that explicitly calls the Logger constructor
    Printer(const std::string& decorator)
        : Logger("Printer Logger") {  // Explicitly call Logger constructor with a name
        Logger::decorator = decorator;
    }

    void GetInfo() override {
        std::cout << "Printer: GetInfo" << std::endl;
    }

    // Printer does not access Logger's private members directly
};

// Static member initialization
std::string Printer::message;

int main() {
    Printer printer("CustomDecorator: ");
    printer.Info("This is an info message from Printer.");

    // Access the m_Level from Logger using LoggerAccessor
    std::cout << "Accessing Logger's m_Level using LoggerAccessor: "
              << LoggerAccessor::getLevel(printer) << std::endl;

    // Set a new level using LoggerAccessor
    LoggerAccessor::setLevel(printer, Logger::LogLevelError);

    std::cout << "New level after setting with LoggerAccessor: "
              << LoggerAccessor::getLevel(printer) << std::endl;

    return 0;
}
