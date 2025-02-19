#include "entities.h"

int main(){
    Player::velocity = 5;
    Player player1("Jane");
    player1.get_name();
    player1.X = 0;
    player1.Y = 10;
    player1.Move(10, 5);
    std::cout<<"x: "<<player1.X<<", y: "<<player1.Y<<std::endl;

    Player player2("Roby");
    player2.get_name();
    player2.X = 5;
    player2.Y = 20;
    player2.Move(5, 3);
    std::cout<<"x: "<<player2.X<<", y: "<<player2.Y<<std::endl;

    std::cout<<"Distance between 2 players are : "<<Player::get_distance(player1, player2)<<std::endl;
    return 0;
}