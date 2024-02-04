#ifndef _LOG_H
#define _LOG_H
// Resolves error of including Log.h multiple times in a single .cpp file
#define header true

void Log(const char* message);
void InitLog();

#endif
/*

- Anything that starts with # is an preprocessor directive

- Check if _LOG_H is defined somewhere else. If its not defined then the code inside it is included into a .cpp file.

- If _LOG_H is defined somewhere else then none of the code inside the #ifndef to #endif will be included

*/