#include <iostream>
#include <cmath>
#include <type_traits>
#include <typeindex>

struct Player_Public // We are creating a new variable "type". It doesn't have a type. It is a type.
{

	int x, y, speed;

	void Move(int xa, int ya) {

		x += xa * speed;
		y += ya * speed;

	}
};

struct Vec // Just used to stores some vector values inside this struct. Maybe have some functinality but primarily used to just store variables as object.
{

	float Ax, Ay;

	float Magnitude() {
		float mag = sqrt((Ax * Ax) + (Ay * Ay));
		return mag;
	}

	float Angle() {
		float ang = tan(Ay / Ax);
		return ang;
	}
};

#define struct class // As c has struct keyword, hence we can just define this struct keyword as class, hence we get features of class in c code using struct keyword

struct Player_Private // This is a class not a struct
{
public:
	int x, y, speed;

	void Move(int xa, int ya) {

		x += xa * speed;
		y += ya * speed;

	}
};

template <typename T>
std::type_index print_type() {
    std::cout << __PRETTY_FUNCTION__ << "\n"; // Compiler-specific
	if constexpr (std::is_class<T>::value) { std::cout<<"It's class/struct"<<std::endl; }
	else { std::cout<<"It's not class/struct"<<std::endl; }
	return std::type_index(typeid(T));
}

int main() {


	Player_Public player1; // we create a variable player of type Player_private which is a class. We can access all the elements of the struct from Player_public objects by default
	Player_Private player2; // we create a variable player of type Player_private which is a class. We can't access all the elements of the class using Player_private objects by default

    std::cout << print_type<decltype(player1)>().name() <<std::endl;
	std::cout << print_type<decltype(player2)>().name() <<std::endl;

	player1.x = 0;
	player1.y = 0;
	player1.speed = 10;

	player1.Move(1, 3);

	std::cout << "Player Object is struct" << std::endl;
	std::cout << "x coordinate : " << player1.x << "\ny coordinate : " << player1.y << std::endl;

	player2.x = 0;
	player2.y = 0;
	player2.speed = 10;

	player2.Move(2, 5);

	std::cout << "Player Object is class" << std::endl;
	std::cout << "x coordinate : " << player2.x << "\ny coordinate : " << player2.y << std::endl;

	Vec a;
	a.Ax = 3;
	a.Ay = 4;
	float mag = a.Magnitude();
	float ang = a.Angle();

	std::cout << "Mag: " << mag << "\nAngle: " << ang << std::endl;



}
/*
Struct is technically same as a class only difference is by default class declares the variables as private, whereas Struct by default declares variables as public

Structs are just used for maintaining some data in a structure
	
Structs shouldn't be used for inheritance
*/