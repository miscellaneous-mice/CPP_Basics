#include <iostream>
#include <string>

class ConsoleUtils{
public:
    enum Colors{
        RED=91, GREEN, YELLOW
    };
private:
    Colors color;
    friend struct LoggerHelper;
public:
    ConsoleUtils() : color(GREEN) {};
    void SetColor(Colors color);
    void Log(const std::string& message);
};