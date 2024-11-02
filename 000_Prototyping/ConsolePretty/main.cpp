#include "consoleutils.h"

int main(){
    ConsoleUtils* console = new ConsoleUtils();
    console->SetColor(ConsoleUtils::GREEN);
    console->Log("Hello world");
    delete console;
}