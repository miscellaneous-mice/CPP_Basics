#include "Common.h"
#include "Log.h"

int main(){
    int result = 0;
    result = Multiply(5, 6);
    std::string s = std::to_string(result);
    const char* pchar = s.c_str();
    Log(pchar);
    return 0;
}