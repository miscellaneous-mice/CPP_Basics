#include "consoleutils.h"


void ConsoleUtils::SetColor(Colors color){
    std::cout << "\033[" << color << "m";
}

void ConsoleUtils::Log(const std::string& message){
    std::cout<<message<<std::endl;
}