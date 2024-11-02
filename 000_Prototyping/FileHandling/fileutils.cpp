#include "fileutils.h"

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
    std::string file = logDirectory + "/" + filename + ".log";
    std::cout << "File at: " << file << std::endl;

    // Open the file in append mode
    MyFile.open(file, std::ios::app | std::ios::in);
    if (!MyFile.is_open()) {
        throw std::runtime_error("Failed to open log file.");
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
