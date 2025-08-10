/*
Virtual functions are used when using polymorphism for classes
- A virtual function is declared in a base class using the virtual keyword.
- When a function is declared as virtual in the base class then this function is stored in a vtable
- Hence, when this instance of function is called then it looks up the vtable and dispatches the appropriate function for the base class
*/

#include <iostream>
#include <string>

class Entity
{
public:
    inline static std::string message;
    virtual std::string GetName(){return "Your dad";}
    void whisper() {std::cout<<".."<<message<<".."<<std::endl;}
};

class Player : public Entity{
private:
    std::string m_Name;
public:
    Player(const std::string& name) : m_Name(name) {};
    std::string GetName() override {return m_Name;}
    void shout() {std::cout<<"!!!"<<message<<"!!!"<<std::endl;}
};

void PrintName(Entity* entity){
    std::cout<<entity->GetName()<<std::endl;
}

// std::string Entity::message;

void Speak(Player* player, std::string message, std::string tone){
    player->message = message;
    if (tone == "whisper")
        player->whisper();
    else if (tone == "shout")
        player->shout();
    else
        std::cout<<message<<std::endl;
}

int main(){
    Entity* e = new Entity();
    e->message = "Hello Dude";
    std::cout<<e->GetName()<<std::endl;

    Player* p = new Player("Rahul");
    std::cout<<p->GetName()<<std::endl;

    PrintName(e);
    PrintName(p);
    Speak(p, "Hello there", "whisper");
    Speak(p, "Hey there", "shout");
    return 0;
}