#include <iostream>

#include "Log.h"
#include "Common.h"

#if !header
void Log(const char* message) {
    std::cout << message << std::endl;
}
#endif

int main()
{
    InitLog();
    Log("Hello World!\n");
    int result = Multiply(5, 2);
    std::cout << result << std::endl;
}

/*
- .h files have function declaration. So when you use compiler knows that there is an function in header files
- .cpp files have function definition. All the contents, the body and the characteristics of a function
- Log function is included by Common.h. And as well as Log.h hence when you include both the header files you have:
  #include <iostream>

  void Log(const char* message)
  void Log(const char* message)

  int main(){
  |
  |
  |
  }

  As Log is defined 2 times gives an error. Hence pragma once is included in Log.h so that it avoids code duplication

- Instead of # pragma once you can use the ifdef method to avoid code duplication

*/