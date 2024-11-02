#include "logger.h"

int main(){
    Logger* logger = new Logger("Test");
    LoggerHelper::setLevel(logger, Configs::LogLevelInfo);
    // logger->info("Hello world");
    BaseUtils* consoleutils = logger->StreamHandler(Configs::LogLevelInfo, "%d-%m-%Y %H-%M-%S", "date::level::message");
    BaseUtils* fileutils = logger->FileHandler(Configs::LogLevelInfo, "%d-%m-%Y %H-%M-%S", "date::level::message");
    logger->addHandler(consoleutils);
    logger->addHandler(fileutils);
    logger->GetInfo();
    logger->info("Hello world");
    delete logger;
}