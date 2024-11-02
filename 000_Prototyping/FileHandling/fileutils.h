#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>   // For getcwd and access
#include <sys/stat.h> // For mkdir

class FileUtils {
private:
    std::string filename;
    std::fstream MyFile;
    bool ensureDirectoryExists(const std::string& directory);

public:
    FileUtils(const std::string& filename);
    std::string Reader();
    bool Writer(const char* message);
    ~FileUtils();
};
