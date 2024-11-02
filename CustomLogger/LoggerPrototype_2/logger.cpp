#include "logger.h"

template FileUtils* castHandler<FileUtils>(void*);
template ConsoleUtils* castHandler<ConsoleUtils>(void*);
template BaseUtils* castHandler<BaseUtils>(void*);
template Logger* castHandler<Logger>(void*);

template <typename T>
T* castHandler(void* handler){
    return dynamic_cast<T*>(static_cast<BaseUtils*>(handler));
}

Configs::Level LoggerHelper::getLevel(void* handler){
    if (auto file = castHandler<FileUtils>(handler)) {
        return file->m_Level;
    } else if (auto console = castHandler<ConsoleUtils>(handler)){
        return console->m_Level;
    } else if (auto basic = castHandler<BaseUtils>(handler)){
        return basic->m_Level;
    } else if (auto logger = castHandler<Logger>(handler)){
        return logger->m_Level;
    }
    return Configs::LogLevelDefault;
}

void LoggerHelper::setLevel(void* handler, Configs::Level level){
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

const std::string LoggerHelper::getLoggerName(const Logger* logger) {
    return logger->logger_name;
}

void LoggerHelper::setFormatter(void* handler, const std::string& format) {
    if (auto file = castHandler<FileUtils>(handler)) {
        file->format = format;
    } else if (auto console = castHandler<ConsoleUtils>(handler)){
        console->format = format;
    } 
}

std::string Logger::PrepareLog(void* handler, std::string message) {
    BaseUtils* Utils = castHandler<BaseUtils>(handler);
    if (auto file = castHandler<FileUtils>(handler)) {
        FileUtils* Utils = file;
    } else if (auto console = castHandler<ConsoleUtils>(handler)){
        ConsoleUtils* Utils = console;
    } 
    std::string result;
    std::transform(Utils->format.begin(), Utils->format.end(), result.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    std::string now = getCurrentDateTime(Utils->dateformat);
    std::string target1 = "date";
    std::string target2 = "level";
    std::string target3 = "message";

    result = Utils->format;
    // result = target1 + "||" + target2 + "||" + target3;
    // Replace "name" with "LOGGER"
    size_t pos = result.find(target1);
    if (pos != std::string::npos) {
        result.replace(pos, target1.length(), now);
    }

    // Replace "date" with "17-06-2024"
    pos = result.find(target2);
    if (pos != std::string::npos) {
        switch(LoggerHelper::getLevel(Utils)) {
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

    // Replace "level" with "INFO"
    pos = result.find(target3);
    if (pos != std::string::npos) {
        result.replace(pos, target3.length(), message);
    }
    return result;
}

BaseUtils* Logger::StreamHandler(Level loglevel, const char* datefmt, std::string formatter){
    BaseUtils* consoleutils = new ConsoleUtils();
    LoggerHelper::setLevel(consoleutils, loglevel);
    consoleutils->dateformat = datefmt;
    consoleutils->format = formatter;
    return consoleutils;
}

BaseUtils* Logger::FileHandler(Level loglevel, const char* datefmt, std::string formatter) {
    BaseUtils* fileutils = new FileUtils(logger_name);
    LoggerHelper::setLevel(fileutils, loglevel);
    fileutils->dateformat = datefmt;
    fileutils->format = formatter;
    return fileutils;
}

void Logger::addHandler(void* handler){
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
        // const std::type_info& type = pair.second.type();
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
    BaseUtils* basicLogger = new BaseUtils();
    LoggerHelper::setLevel(basicLogger, m_Level);
    if (this->handlers.size() == 0) {
        this->add_element(BASE, basicLogger);
    }
    for (const auto& pair: handlers) {
        if(const auto& handler = this->get_element<FileUtils>(pair.first)){
            formatted_text = Logger::PrepareLog(handler, message);
            if (LoggerHelper::getLevel(handler) >= LogLevelInfo){
                handler->Writer(formatted_text.c_str());
            }
        }
        else if(const auto& handler = this->get_element<ConsoleUtils>(pair.first)){
            formatted_text = Logger::PrepareLog(handler, message);
            if (LoggerHelper::getLevel(handler) >= LogLevelInfo){
                handler->SetColor(GREEN);
                std::cout<<formatted_text<<std::endl;
                consoleWrite = false;
            }
        }
        else if(const auto& handler = this->get_element<BaseUtils>(pair.first)){
            formatted_text = Logger::PrepareLog(handler, message);
            if (LoggerHelper::getLevel(handler) >= LogLevelInfo){
                handler->LogConsole(formatted_text);
                consoleWrite = false;
            }
        }
    }
    if (consoleWrite) {
        formatted_text = Logger::PrepareLog(basicLogger, message);
        basicLogger->LogConsole(formatted_text);
    }
    this->remove_element(BASE);
    delete basicLogger;
}

void Logger::warning(const std::string& message){
    bool consoleWrite = true;
    std::string formatted_text;
    BaseUtils* basicLogger = new BaseUtils();
    LoggerHelper::setLevel(basicLogger, m_Level);
    if (this->handlers.size() == 0) {
        this->add_element(BASE, basicLogger);
    }
    for (const auto& pair: handlers) {
        if(const auto& handler = this->get_element<FileUtils>(pair.first)){
            formatted_text = Logger::PrepareLog(handler, message);
            if (LoggerHelper::getLevel(handler) >= LogLevelWarning){
                handler->Writer(formatted_text.c_str());
            }
        }
        else if(const auto& handler = this->get_element<ConsoleUtils>(pair.first)){
            formatted_text = Logger::PrepareLog(handler, message);
            if (LoggerHelper::getLevel(handler) >= LogLevelWarning){
                handler->SetColor(YELLOW);
                std::cout<<formatted_text<<std::endl;
                consoleWrite = false;
            }
        }
        else if(const auto& handler = this->get_element<BaseUtils>(pair.first)){
            formatted_text = Logger::PrepareLog(handler, message);
            if (LoggerHelper::getLevel(handler) >= LogLevelWarning){
                handler->LogConsole(formatted_text);
                consoleWrite = false;
                this->remove_element(BASE);
            }
        }
    }
    if (consoleWrite) {
        formatted_text = Logger::PrepareLog(basicLogger, message);
        basicLogger->LogConsole(formatted_text);
        this->remove_element(BASE);
    }
    delete basicLogger;
}

void Logger::error(const std::string& message){
    bool consoleWrite = true;
    std::string formatted_text;
    BaseUtils* basicLogger = new BaseUtils();
    LoggerHelper::setLevel(basicLogger, m_Level);
    if (this->handlers.size() == 0) {
        this->add_element(BASE, basicLogger);
    }
    for (const auto& pair: handlers) {
        if(const auto& handler = this->get_element<FileUtils>(pair.first)){
            formatted_text = Logger::PrepareLog(handler, message);
            if (LoggerHelper::getLevel(handler) >= LogLevelError){
                handler->Writer(formatted_text.c_str());
            }
        }
        else if(const auto& handler = this->get_element<ConsoleUtils>(pair.first)){
            formatted_text = Logger::PrepareLog(handler, message);
            if (LoggerHelper::getLevel(handler) >= LogLevelError){
                handler->SetColor(RED);
                std::cout<<formatted_text<<std::endl;
                consoleWrite = false;
            }
        }
        else if(const auto& handler = this->get_element<BaseUtils>(pair.first)){
            formatted_text = Logger::PrepareLog(handler, message);
            if (LoggerHelper::getLevel(handler) >= LogLevelError){
                handler->LogConsole(formatted_text);
                consoleWrite = false;
                this->remove_element(BASE);
            }
        }
    }
    if (consoleWrite) {
        formatted_text = Logger::PrepareLog(basicLogger, message);
        basicLogger->LogConsole(formatted_text);
        this->remove_element(BASE);
    }
    delete basicLogger;
}