#include <iostream>

struct PrivateAccessor;
struct ProtectedAccessor;

class Base {
public:
    enum Level{
        info=0, warning, error
    };
private:
    std::string m_name;
    inline static int m_speed;
    friend struct PrivateAccessor;
protected:
    friend struct ProtectedAccessor;
    static int get_speed(){
        return m_speed;
    }
    virtual void Move(int xa, int ya) = 0;
public:
    Base(std::string name): m_name(name) {}
    int x, y;
    static void set_speed(int speed){
        m_speed = speed;
    }
    virtual void Info() {
        std::cout<<"Base class : "<<m_name<<std::endl;
    }
    ~Base() = default;
};

// int Base::m_speed;

class Entity : protected Base {
public:
    std::string m_name;
    Entity(std::string name) : Base(name), m_name(name) {}
    void Move(int xa, int ya) override {
        x +=  xa*Base::get_speed();
        y +=  ya*Base::get_speed();
    }
    void Info() override{
        std::cout<<"Entity : "<<m_name<<std::endl;
    }
};

struct PrivateAccessor {
private:
    PrivateAccessor() = default;
public:
    static int get_speed() {
        return Base::m_speed;
    }
    static std::string get_name(std::shared_ptr<Base> base) {
        return base->m_name;
    }
};


struct ProtectedAccessor {
private:
    ProtectedAccessor() = default;
public:
    static int get_speed(std::shared_ptr<Base> base) {
        return base->get_speed();
    }
    static std::string get_name(std::shared_ptr<Base> base) {
        return base->m_name;
    }
};

class EntityInfo : public Entity{
public:
    EntityInfo(std::string name) : Entity(name) {};
    void entity_speed(std::unique_ptr<Base> base) {
        // std::shared_ptr<Base> base_shared = std::make_shared<Base>(std::move(base));
        std::cout<<"Speed via PrivateAccessor : "<<PrivateAccessor::get_speed()<<std::endl;
        // std::cout<<"Speed via ProtectedAccessor : "<<ProtectedAccessor::get_speed(base_shared)<<std::endl;
    }
    void get_current_loc() {
        std::cout<<this->m_name<<" is at "<<"x : "<<this->x<<", y : "<<y<<std::endl;
    }
};

int main() {
    std::unique_ptr<Entity> e = std::make_unique<Entity>("John");
    std::unique_ptr<Entity> e_info = std::make_unique<EntityInfo>("Nog");
    e->Info();
    e_info->Info();

    Base::set_speed(10);
    // e_info->set_speed(10);

    e_info->entity_speed(std::move(e));
    return 0;
}