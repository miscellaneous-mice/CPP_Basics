#pragma once

#include <iostream>
#include <string>

static int population;

struct EntityData{
    EntityData* m_Parent;
    std::string m_Name;
};

std::string Entity_getName(EntityData* self);

void Entity_total();

void Entity_PrintType(EntityData* self);