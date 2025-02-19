#pragma once
#include <iostream>
#include <cmath>

class Entity{
protected:
    Entity() {};
public:
    float X, Y;
    static float velocity;
    void Move(int xa, int ya);
};

class Player : public Entity{
public:
    std::string name;
    Player(std::string name) : name(name) {std::cout<<"Created a player : "<<name<<std::endl;}
    void get_name();
    static float get_distance(Player& p1, Player& p2);
};