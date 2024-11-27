#include "logger.h"

int main(){
    std::cout<<"*****LOGGING STARTED*****"<<std::endl;
    {
        std::shared_ptr<Logger> logger = std::make_shared<Logger>("Test");
        LoggerHelper::setLevel(logger, Configs::LogLevelInfo);
        LoggerHelper::setFormatter(logger, "date||level||message");
        logger->info("Hello world");
        auto consoleutils = logger->StreamHandler(Configs::LogLevelError, "%d-%m-%Y %H-%M-%S", "date::level::message");
        auto fileutils = logger->FileHandler(Configs::LogLevelWarning, "%d:%m:%Y %H:%M:%S", "date::level::message");
        logger->addHandler(consoleutils);
        LoggerHelper::setFormatter(fileutils, "date--level--message");
        logger->addHandler(fileutils);
        logger->GetInfo();
        logger->info("Hello world");
        logger->error("Gawdd damn");
        std::cout<<"*****Sample Print Statement*****"<<std::endl;
        logger->warning("It is working!!!");
        logger->info("Yeah Babyyy!!!");  
    }
    std::cout<<"*****LOGGING ENDED*****"<<std::endl;
}