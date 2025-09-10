#include <iostream>

class Player // We are creating a new variable "type". It doesn't have a type. It is a type.
{
// By Default visibility is Private in a class. Only function inside these class can access Private variables.
public: // We are allowed to Access these variables anywhere outside the class
	int x, y, speed;

	void Move_by_class(int xa, int ya) { // We add functionality Move to every Player object

		x += xa * speed; // These x, y vary the variables of our Player class, if Player object calls the Move function.
		y += ya * speed; 

	}
};

void Move_by_ref(Player& player, int xa, int ya) { // Pass by reference

	player.x += xa * player.speed;
	player.y += ya * player.speed;

}

Player Move_by_value(Player player, int xa, int ya) { // Pass by value

	player.x += xa * player.speed;
	player.y += ya * player.speed;
	return player;

}

int main() {

	Player player; // we create a variable player of type Player. Hence we created a instance/object (player) of the Player.
	player.x = 0;
	player.y = 0;
	player.speed = 10;

	std::cout << "Initial x coordinate : " << player.x << "\nInitial y coordinate : " << player.y << std::endl;

	player = Move_by_value(player, 2, 5);
	std::cout << "Passing player object by value" << std::endl;
	std::cout << "x coordinate : " << player.x << "\ny coordinate : " << player.y << std::endl;

	Move_by_ref(player, 2, 5);
	std::cout << "Passing player object by reference" << std::endl;
	std::cout << "x coordinate : " << player.x << "\ny coordinate : " << player.y << std::endl;

	player.Move_by_class(2, 5);  // Best way to implement a functionality for our Player object
	std::cout << "Calling Move function using the object created by the class" << std::endl;
	std::cout << "x coordinate : " << player.x << "\ny coordinate : " << player.y << std::endl;
}
/*
Class is just a collection of all the data and functions into a type
*/