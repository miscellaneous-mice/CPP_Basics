#include "entities.h"

float Entity::velocity;

void Entity::Move(int xa, int ya){
    X += xa * velocity;
    Y += ya * velocity;
}

void Player::get_name(){
    std::cout<< name <<std::endl;
}

float Player::get_distance(Player& p1, Player& p2){
    float del_x = p2.X - p1.X;
    float del_y = p2.Y - p1.Y;
    float distance = std::sqrt(std::pow(del_x, 2) + std::pow(del_y,2));
    return distance;
}