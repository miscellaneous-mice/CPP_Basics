#ifndef _UTILS_H
#define _UTILS_H

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>   // For getcwd and access
#include <sys/stat.h> // For mkdir
#include <map> // Hashmaps
#include <variant>
#include <any>
#include <typeinfo>

#define FILE "file"
#define CONSOLE "console"
#define BASE "base"

std::string getCurrentDateTime(const char* date_format);

struct LoggerHelper;

struct Configs{
    enum Level{
        LogLevelDefault=0, LogLevelInfo, LogLevelWarning, LogLevelError
    };
    enum Colors{
        RED=91, GREEN, YELLOW
    };
    const char* dateformat = "%d-%m-%Y %H-%M-%S";
    std::string format = "date::level::message";
};

class Handlers{
protected:
    Handlers() = default;
    std::map<std::string, std::any> handlers;

    template<typename T>
    bool add_element(const std::string& key, T value);

    template<typename T>
    T* get_element(const std::string& key);

    bool remove_element(const std::string& key);

    ~Handlers();
};

class BaseUtils : public Configs{
private:
    Level m_Level;
    friend struct LoggerHelper;
public:
    BaseUtils() = default;
    static void LogConsole(const std::string& message);
    virtual void GetInfo();
    virtual ~BaseUtils() = default;
};

class ConsoleUtils : virtual public BaseUtils{
private:
    Level m_Level;
    Colors color;
    friend struct LoggerHelper;
public:
    ConsoleUtils() : color(GREEN),  m_Level(LogLevelInfo) {};
    void SetColor(Colors color);
    void GetInfo() override;
    ~ConsoleUtils();
};

class FileUtils : virtual public BaseUtils{
private:
    Level m_Level;
    std::string filename;
    std::fstream MyFile;
    bool ensureDirectoryExists(const std::string& directory);
    friend struct LoggerHelper;

public:
    FileUtils(const std::string& filename);
    void GetInfo() override;
    std::string Reader();
    bool Writer(const char* message);
    ~FileUtils();
};

#endif