#pragma once

#include "entities.h"

template <typename T>
T* castHandler(Base* handler);

class Accessor : protected HashMap {
public:
    void GetInfo(Base* handler);
    void GetMapInfo(std::string key);
    void addElement(Base* handler);
    void AllElements();
};