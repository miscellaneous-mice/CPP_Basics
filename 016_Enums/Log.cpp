// #include <iostream>

// class Log {
// public:
//     enum Level
//     {
//         LevelError = 0, LevelWarning, LevelInfo
//     };
// private:
//     Level m_level;
// public:
//     Log() : m_level(LevelInfo) {}

//     void Set_Level(Level level) {
//         m_level = level;
//     }

//     void Error(const char* message) {
//         if (m_level >= LevelError)
//             std::cout << message << std::endl;
//     }

//     void Warn(const char* message) {
//         if (m_level >= LevelWarning)
//             std::cout << message << std::endl;
//     }

//     void Info(const char* message) {
//         if (m_level >= LevelInfo)
//             std::cout << message << std::endl;
//     }
// };

// int main() {
//     Log log;
//     log.Set_Level(Log::LevelWarning);

//     std::cout << "\nDebugging using LogLevel" << std::endl;
//     log.Error("Hello Error");
//     log.Warn("Hello Warn");
//     log.Info("Hello Info");

//     return 0;
// }
