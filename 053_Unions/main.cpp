#include <iostream>
#include <format>

// Forward declaration of the access struct
struct LoggerAccessor;

class Vec {
private:
    int x, y;
public:
    Vec(int a, int b) : x(a), y(b) {};
    int get_x() const { return x; }
    int get_y() const { return y; }
};

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

    template<typename... Args>
    void Info(Args&&... args) {
        std::string message = std::format(std::forward<Args>(args)...);
        std::cout << logger_name << "[INFO]: " << message << std::endl;
    }

    template<typename... Args>
    void Warning(Args&&... args) {
        std::string message = std::format(std::forward<Args>(args)...);
        std::cout << logger_name << "[WARNING]: " << message << std::endl;
    }

    template<typename... Args>
    void Error(Args&&... args) {
        std::string message = std::format(std::forward<Args>(args)...);
        std::cout << logger_name << "[ERROR]: " << message << std::endl;
    }
};

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

template <>
struct std::formatter<Vec> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin(); // no custom format options
    }
    auto format(const Vec& v, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "x : {}, y : {}", v.get_x(), v.get_y());
    }
};

struct Union {
    union {
        float a;
        int b;
    };
};

int main() {
    Union u;
    u.a = 10;
    
}