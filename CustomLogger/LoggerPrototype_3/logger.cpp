#include "logger.h"

template std::shared_ptr<FileUtils> castHandler<FileUtils>(std::shared_ptr<BaseUtils>);
template std::shared_ptr<ConsoleUtils> castHandler<ConsoleUtils>(std::shared_ptr<BaseUtils>);
template std::shared_ptr<BaseUtils> castHandler<BaseUtils>(std::shared_ptr<BaseUtils>);
template std::shared_ptr<Logger> castHandler<Logger>(std::shared_ptr<BaseUtils>);

template <typename T>
std::shared_ptr<T> castHandler(std::shared_ptr<BaseUtils> handler){
    return std::dynamic_pointer_cast<T>(handler);
}

Configs::Level LoggerHelper::getLevel(std::shared_ptr<BaseUtils> handler){
    if (auto file = castHandler<FileUtils>(handler)) {
        return file->m_Level;
    } else if (auto console = castHandler<ConsoleUtils>(handler)) {
        return console->m_Level;
    } else if (auto logger = castHandler<Logger>(handler)) {
        return logger->m_Level;
    } else if (auto basic = castHandler<BaseUtils>(handler)) {
        return basic->m_Level;
    }
    return Configs::LogLevelDefault;
}

void LoggerHelper::setLevel(std::shared_ptr<BaseUtils> handler, Configs::Level level){
    if (auto file = castHandler<FileUtils>(handler)) {
        file->m_Level = level;
    } else if (auto console = castHandler<ConsoleUtils>(handler)){
        console->m_Level = level;
    } else if (auto logger = castHandler<Logger>(handler)){
        logger->m_Level = level;
    } else if (auto basic = castHandler<BaseUtils>(handler)){
        basic->m_Level = level;
    }
}

const std::string LoggerHelper::getLoggerName(const std::shared_ptr<Logger> logger) {
    return logger->logger_name;
}

void LoggerHelper::setFormatter(std::shared_ptr<BaseUtils> handler, const std::string& format) {
    if (auto file = castHandler<FileUtils>(handler)) {
        file->format = format;
    } else if (auto console = castHandler<ConsoleUtils>(handler)) {
        console->format = format;
    } else if (auto logger = castHandler<Logger>(handler)) {
        logger->format = format;
    } else if (auto basic = castHandler<BaseUtils>(handler)) {
        basic->format = format;
    }
}

std::string Logger::PrepareLog(std::shared_ptr<BaseUtils> handler, Level level, std::string message) {
    std::string format;
    const char* dateformat;

    if (auto file = castHandler<FileUtils>(handler)) {
        format = file->format;
        dateformat = file->dateformat;
    } else if (auto console = castHandler<ConsoleUtils>(handler)){
        format = console->format;
        dateformat = console->dateformat;
    } else if (auto basic = castHandler<BaseUtils>(handler)) {
        format = basic->format;
        dateformat = basic->dateformat;
    }
    std::string result;
    std::transform(format.begin(), format.end(), result.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    std::string now = getCurrentDateTime(dateformat);
    std::string target1 = "date";
    std::string target2 = "level";
    std::string target3 = "message";

    result = format;

    size_t pos = result.find(target1);
    if (pos != std::string::npos) {
        result.replace(pos, target1.length(), now);
    }

    pos = result.find(target2);
    if (pos != std::string::npos) {
        switch(level) {
            case LogLevelDefault :
                result.replace(pos, target2.length(), "LOG");
                break;
            case LogLevelInfo :
                result.replace(pos, target2.length(), "INFO");
                break;
            case LogLevelWarning : 
                result.replace(pos, target2.length(), "WARNING");
                break;
            case LogLevelError :
                result.replace(pos, target2.length(), "ERROR");
                break;
        }
    }

    pos = result.find(target3);
    if (pos != std::string::npos) {
        result.replace(pos, target3.length(), message);
    }
    return result;
}

std::shared_ptr<BaseUtils> Logger::StreamHandler(Level loglevel, const char* datefmt, std::string formatter){
    std::shared_ptr<BaseUtils> consoleutils = std::make_shared<ConsoleUtils>();
    LoggerHelper::setLevel(consoleutils, loglevel);
    consoleutils->dateformat = datefmt;
    consoleutils->format = formatter;
    return consoleutils;
}

std::shared_ptr<BaseUtils> Logger::FileHandler(Level loglevel, const char* datefmt, std::string formatter) {
    std::shared_ptr<BaseUtils> fileutils = std::make_shared<FileUtils>(logger_name);
    LoggerHelper::setLevel(fileutils, loglevel);
    fileutils->dateformat = datefmt;
    fileutils->format = formatter;
    return fileutils;
}

void Logger::addHandler(std::shared_ptr<BaseUtils> handler){
    bool status = false;
    std::string handler_name;
    if (auto file = castHandler<FileUtils>(handler)) {
        status = this->add_element(FILE, file);
        // file->GetInfo();
        handler_name = "file handler";
    } else if (auto console = castHandler<ConsoleUtils>(handler)){
        status = this->add_element(CONSOLE, console);
        // console->GetInfo();
        handler_name = "console handler";
    } else if (auto base = castHandler<BaseUtils>(handler)){
        status = this->add_element(BASE, base);
        // base->GetInfo();
        handler_name = "base handler";
    }
    std::string result = status ? handler_name + " : Handler inserted successfully" : handler_name + " : Handler already exists";
    std::cout<<result<<std::endl;
}

void Logger::GetInfo() {
    for (const auto& pair : this->handlers){
        if (auto entity = this->get_element<FileUtils>(pair.first)) {
            entity->GetInfo();
        } else if (auto entity = this->get_element<ConsoleUtils>(pair.first)){
            entity->GetInfo();
        } else if (auto entity = this->get_element<BaseUtils>(pair.first)){
            entity->GetInfo();
        }
    } 
}


void Logger::info(const std::string& message){
    bool consoleWrite = true;
    std::string formatted_text;
    std::shared_ptr<BaseUtils> basicLogger = std::make_shared<BaseUtils>();
    LoggerHelper::setLevel(basicLogger, m_Level);
    LoggerHelper::setFormatter(basicLogger, format);
    if (this->handlers.size() == 0) {
        this->add_element(BASE, basicLogger);
    }
    for (const auto& pair: handlers) {
        if(const auto& handler = this->get_element<FileUtils>(pair.first)){
            formatted_text = Logger::PrepareLog(handler, LogLevelInfo, message);
            if (LoggerHelper::getLevel(handler) >= LogLevelInfo){
                handler->Writer(formatted_text.c_str());
            }
        }
        else if(const auto& handler = this->get_element<ConsoleUtils>(pair.first)){
            formatted_text = Logger::PrepareLog(handler, LogLevelInfo, message);
            if (LoggerHelper::getLevel(handler) >= LogLevelInfo){
                handler->SetColor(GREEN);
                std::cout<<formatted_text<<std::endl;
                ConsoleUtils::ResetColor();
                consoleWrite = false;
            }
        }
        else if(const auto& handler = this->get_element<BaseUtils>(pair.first)){
            formatted_text = Logger::PrepareLog(handler, LogLevelInfo, message);
            if (LoggerHelper::getLevel(handler) >= LogLevelInfo){
                handler->LogConsole(formatted_text);
                consoleWrite = false;
            }
        }
    }
    if (consoleWrite and m_Level >= LogLevelInfo) {
        formatted_text = Logger::PrepareLog(basicLogger, LogLevelInfo, message);
        basicLogger->LogConsole(formatted_text);
    }
    this->remove_element(BASE);
}

void Logger::warning(const std::string& message){
    bool consoleWrite = true;
    std::string formatted_text;
    std::shared_ptr<BaseUtils> basicLogger = std::make_shared<BaseUtils>();
    LoggerHelper::setLevel(basicLogger, m_Level);
    LoggerHelper::setFormatter(basicLogger, format);
    if (this->handlers.size() == 0) {
        this->add_element(BASE, basicLogger);
    }
    for (const auto& pair: handlers) {
        if(const auto& handler = this->get_element<FileUtils>(pair.first)){
            formatted_text = Logger::PrepareLog(handler, LogLevelWarning, message);
            if (LoggerHelper::getLevel(handler) >= LogLevelWarning){
                handler->Writer(formatted_text.c_str());
            }
        }
        else if(const auto& handler = this->get_element<ConsoleUtils>(pair.first)){
            formatted_text = Logger::PrepareLog(handler, LogLevelWarning, message);
            if (LoggerHelper::getLevel(handler) >= LogLevelWarning){
                handler->SetColor(YELLOW);
                std::cout<<formatted_text<<std::endl;
                ConsoleUtils::ResetColor();
                consoleWrite = false;
            }
        }
        else if(const auto& handler = this->get_element<BaseUtils>(pair.first)){
            formatted_text = Logger::PrepareLog(handler, LogLevelWarning, message);
            if (LoggerHelper::getLevel(handler) >= LogLevelWarning){
                handler->LogConsole(formatted_text);
                consoleWrite = false;
            }
        }
    }
    if (consoleWrite and m_Level >= LogLevelWarning) {
        formatted_text = Logger::PrepareLog(basicLogger, LogLevelWarning, message);
        basicLogger->LogConsole(formatted_text);
    }
    this->remove_element(BASE);
}

void Logger::error(const std::string& message){
    bool consoleWrite = true;
    std::string formatted_text;
    std::shared_ptr<BaseUtils> basicLogger = std::make_shared<BaseUtils>();
    LoggerHelper::setLevel(basicLogger, m_Level);
    LoggerHelper::setFormatter(basicLogger, format);
    if (this->handlers.size() == 0) {
        this->add_element(BASE, basicLogger);
    }
    for (const auto& pair: handlers) {
        if(const auto& handler = this->get_element<FileUtils>(pair.first)){
            formatted_text = Logger::PrepareLog(handler, LogLevelError, message);
            if (LoggerHelper::getLevel(handler) >= LogLevelError){
                handler->Writer(formatted_text.c_str());
            }
        }
        else if(const auto& handler = this->get_element<ConsoleUtils>(pair.first)){
            formatted_text = Logger::PrepareLog(handler, LogLevelError, message);
            if (LoggerHelper::getLevel(handler) >= LogLevelError){
                handler->SetColor(RED);
                std::cout<<formatted_text<<std::endl;
                ConsoleUtils::ResetColor();
                consoleWrite = false;
            }
        }
        else if(const auto& handler = this->get_element<BaseUtils>(pair.first)){
            formatted_text = Logger::PrepareLog(handler, LogLevelError, message);
            if (LoggerHelper::getLevel(handler) >= LogLevelError){
                handler->LogConsole(formatted_text);
                consoleWrite = false;
            }
        }
    }
    if (consoleWrite and m_Level >= LogLevelError) {
        formatted_text = Logger::PrepareLog(basicLogger, LogLevelError, message);
        basicLogger->LogConsole(formatted_text);
    }
    this->remove_element(BASE);
}