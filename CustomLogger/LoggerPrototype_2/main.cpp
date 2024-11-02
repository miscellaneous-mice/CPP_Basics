#include "logger.h"

int main(){
    Logger* logger = new Logger("Test");
    LoggerHelper::setLevel(logger, Configs::LogLevelWarning);
    LoggerHelper::setFormatter(logger, "date||level||message");
    logger->info("Hello world");
    BaseUtils* consoleutils = logger->StreamHandler(Configs::LogLevelWarning, "%d-%m-%Y %H-%M-%S", "date::level::message");
    BaseUtils* fileutils = logger->FileHandler(Configs::LogLevelError, "%d:%m:%Y %H:%M:%S", "date::level::message");
    logger->addHandler(consoleutils);
    LoggerHelper::setFormatter(fileutils, "date--level--message");
    logger->addHandler(fileutils);
    logger->GetInfo();
    logger->info("Hello world");
    logger->error("Gawdd damn");
    logger->warning("It is working!!!");
    logger->info("Yeah Babyyy!!!");
    delete logger;
}