#pragma once

#include <iostream>
#include <string>


class Entity {
private:
    Entity* m_Parent;
    std::string m_Name = "Entity";
public:
    static int population;
    Entity() = default;
    std::string getName() const;
    static void total();
    void PrintType();
};