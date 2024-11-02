#pragma once

#include "entities.h"

template <typename T>
T* castHandler(void* handler);

class Accessor : protected HashMap {
public:
    void GetInfo(void* handler);
    void GetMapInfo(std::string key);
    void addElement(void* handler);
    void AllElements();
};