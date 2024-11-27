#pragma once

#include "entities.h"

template <typename T>
std::shared_ptr<T> castHandler(std::shared_ptr<Base> handler);

class Accessor : protected HashMap {
public:
    void GetInfo(std::unique_ptr<Base> handler);
    void GetMapInfo(std::string key);
    void addElement(std::unique_ptr<Base> handler);
    void AllElements();
};