#include "utils.h"

template bool Handlers::add_element(const std::string&, std::shared_ptr<FileUtils>);
template bool Handlers::add_element(const std::string&, std::shared_ptr<ConsoleUtils>);
template bool Handlers::add_element(const std::string&, std::shared_ptr<BaseUtils>);


template std::shared_ptr<FileUtils> Handlers::get_element<FileUtils>(const std::string&);
template std::shared_ptr<ConsoleUtils> Handlers::get_element<ConsoleUtils>(const std::string&);
template std::shared_ptr<BaseUtils> Handlers::get_element<BaseUtils>(const std::string&);

template<typename T>
bool Handlers::add_element(const std::string& key, std::shared_ptr<T> value) {
    if (handlers.find(key) != handlers.end()) {
        return false;
    }
    this->handlers[key] = value;  // Store value as std::any
    return true;
}

template<typename T>
std::shared_ptr<T> Handlers::get_element(const std::string& key) {
    if (handlers.find(key) == handlers.end()) {
        std::cerr<<"The handler does not exist"<<std::endl;
        return nullptr;
    }
    try {
        // return dynamic_cast<T*>(std::any_cast<BaseUtils*>(this->handlers[key])); 
        return std::any_cast<std::shared_ptr<T>>(this->handlers[key]);
    } catch (const std::bad_any_cast& e) {
        std::cerr << "Bad cast: " << e.what() << std::endl;
        return nullptr;
    }
}

bool Handlers::remove_element(const std::string& key){
    if (handlers.find(key) != handlers.end()) {
        this->handlers.erase(key);
        return true;
    }
    return false;
}

Handlers::~Handlers(){
    handlers[CONSOLE].reset();
    handlers[FILE].reset();
    handlers[BASE].reset();
}

std::string getCurrentDateTime(const char* date_format){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),date_format,timeinfo);
    std::string strdatetime(buffer);
    return strdatetime;
}

void ConsoleUtils::SetColor(Colors color){
    std::cout << "\033[" << color << "m";
}

void ConsoleUtils::ResetColor(){
    std::cout << "\033[0m";
}

ConsoleUtils::~ConsoleUtils(){
    ConsoleUtils::ResetColor();
    std::cout<<"Reset the console"<<std::endl;
}

void ConsoleUtils::GetInfo() {
    std::cout<<"This is a console handler"<<std::endl;
    switch(m_Level){
        case LogLevelDefault :
            std::cout<<"Default LogLevel"<<std::endl;
            break;
        case LogLevelInfo :
            std::cout<<"Loglevel is Info"<<std::endl;
            break;
        case LogLevelWarning :
            std::cout<<"Loglevel is Warning"<<std::endl;
            break;
        case LogLevelError : 
            std::cout<<"Loglevel is Error"<<std::endl;
            break;
    }
}

void BaseUtils::GetInfo(){
    std::cout<<"This is the basic handler"<<std::endl;
    switch(m_Level) {
        case LogLevelDefault :
            std::cout<<"Default LogLevel"<<std::endl;
            break;
        case LogLevelInfo :
            std::cout<<"LogLevel is Info"<<std::endl;
            break;
        case LogLevelWarning :
            std::cout<<"Loglevel is Warning"<<std::endl;
            break;
        case LogLevelError :
            std::cout<<"Loglevel is Error"<<std::endl;
            break;
    }
}

void BaseUtils::LogConsole(const std::string& message){
    std::cout<<message<<std::endl;
}

bool FileUtils::ensureDirectoryExists(const std::string& directory) {
    // Check if directory exists
    if (access(directory.c_str(), F_OK) != -1) {
        // Directory exists
        return true;
    } else {
        // Directory does not exist, so create it
        if (mkdir(directory.c_str(), 0755) == 0) {
            std::cout << "Directory created: " << directory << std::endl;
            return true;
        } else {
            std::cerr << "Error: Could not create directory: " << directory << std::endl;
            return false;
        }
    }
}

FileUtils::FileUtils(const std::string& filename) : filename(filename) {
    std::cout << "Initialized file Utils class" << std::endl;
    
    // Get current working directory
    char buff[FILENAME_MAX];
    getcwd(buff, FILENAME_MAX);
    std::string current_working_dir(buff);
    
    // Ensure that the directory exists (create it if necessary)
    std::string logDirectory = current_working_dir + "/logs";
    if (!ensureDirectoryExists(logDirectory)) {
        throw std::runtime_error("Failed to ensure log directory exists.");
    }

    // Build the file path
    std::string file = logDirectory + "/" + filename + "_" + getCurrentDateTime("%d%m%Y") + ".log";
    std::cout << "File at: " << file << std::endl;

    // Open the file in append mode
    MyFile.open(file, std::ios::app | std::ios::in);
    if (!MyFile.is_open()) {
        throw std::runtime_error("Failed to open log file.");
    }
}

void FileUtils::GetInfo() {
    std::cout<<"This is a file handler"<<std::endl;
    switch(m_Level){
        case LogLevelDefault :
            std::cout<<"Default LogLevel"<<std::endl;
            break;
        case LogLevelInfo :
            std::cout<<"Loglevel is Info"<<std::endl;
            break;
        case LogLevelWarning :
            std::cout<<"Loglevel is Warning"<<std::endl;
            break;
        case LogLevelError :
            std::cout<<"Loglevel is Error"<<std::endl;
            break;
    }
}

std::string FileUtils::Reader() {
    std::string data;
    MyFile.clear();
    MyFile.seekg(0, std::ios::beg);
    try {
        if (!MyFile.is_open()) {
            std::cerr << "Error: Unable to open the file!" << std::endl;
            return "";
        }

        // Write to the file
        std::string line;
        while (std::getline(MyFile, line)) {
            data += line + "\n";  // Append each line with a newline character
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
        return "";
    }
    return data;
}

bool FileUtils::Writer(const char* message) {
    bool isWritten = false;
    try {
        if (!MyFile.is_open()) {
            std::cerr << "Error: Unable to open the file!" << std::endl;
            return false;
        }

        // Write to the file
        MyFile << std::string(message) <<"\n";

        // Check if the write operation was successful
        if (MyFile.fail()) {
            std::cerr << "Error: Failed to write to the file!" << std::endl;
        } else {
            isWritten = true;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
        return false;
    }
    return isWritten;
}

FileUtils::~FileUtils() {
    std::cout << "Closed file Utils class" << std::endl;
    if (MyFile.is_open()) {
        MyFile.close();
    }
}
