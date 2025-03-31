#include <math.h>
#include <iostream>
#include <iomanip>
#include <variant>

#define struct_offset(s, m) ((size_t)&(((s*)0)->m))

struct GameState {
    int level;
    int health;
    int score;
    bool game_completed;
    bool boss_defeated;

    template<typename... Args>
    GameState(Args&&... args) {
        static_assert(sizeof...(args) == 5, "GameState requires exactly 5 arguments.");
        auto values = std::make_tuple(std::forward<Args>(args)...);
        Assign(this, values);
        std::cout << "GameState Initialized" << std::endl;
    }

    ~GameState() {
        std::cout << "GameState Destroyed" << std::endl;
    }
};

template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type Assign(GameState*, const std::tuple<Tp...>&) {}

template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I < sizeof...(Tp), void>::type Assign(GameState* instance, const std::tuple<Tp...>& t) {
    if constexpr (I == 0) instance->level = std::get<I>(t);
    else if constexpr (I == 1) instance->health = std::get<I>(t);
    else if constexpr (I == 2) instance->score = std::get<I>(t);
    else if constexpr (I == 3) instance->game_completed = std::get<I>(t);
    else if constexpr (I == 4) instance->boss_defeated = std::get<I>(t);
    Assign<I + 1>(instance, t);
}


void Print(const std::variant<long, double, float, int>& value) {
    std::visit([&](auto&& v) {
        std::cout << std::setprecision(14) << v <<std::endl;
    }, value);
}

void Delete(GameState* gs) {
    GameState* instance = *reinterpret_cast<GameState**>(gs);
    if (instance != nullptr) {
        delete gs;
        gs = nullptr;
    } else {
        std::cout<<"Instance already deleted"<<std::endl;
    }
}

int main() {
    float PI = 3.14159265358979323846f;
    
    Print(static_cast<int>(PI));
    Print(*reinterpret_cast<int*>(&PI));
    Print(*reinterpret_cast<float*>(&PI));

    std::cout<< "Raw Address using reference operator : " << &PI <<std::endl;
    std::cout<< "Address of int* casted PI: " << reinterpret_cast<int*>(&PI) << std::endl;
    std::cout<< "Address of float* casted PI : " << reinterpret_cast<float*>(&PI) << std::endl;
    {
        GameState gs = {66, 100, 900, false, true};

        char saved_gs[sizeof(gs)];
        std::memcpy(saved_gs, &gs, sizeof(gs));

        std::cout<<"\nCasting values based on size"<<std::endl;
        std::cout<<*reinterpret_cast<int*>(saved_gs)<<std::endl;
        std::cout<<*reinterpret_cast<int*>(saved_gs + sizeof(int))<<std::endl;
        std::cout<<*reinterpret_cast<int*>(saved_gs + (sizeof(int) * 2))<<std::endl;
        std::cout<<*reinterpret_cast<bool*>(saved_gs + ((sizeof(int) * 3)))<<std::endl;
        std::cout<<*reinterpret_cast<bool*>(saved_gs + ((sizeof(int) * 3) + sizeof(bool)))<<std::endl;

        std::cout<<"\nCasting values based on offset"<<std::endl;
        std::cout<<*reinterpret_cast<int*>(saved_gs + struct_offset(GameState, level))<<std::endl;
        std::cout<<*reinterpret_cast<int*>(saved_gs + struct_offset(GameState, health))<<std::endl;
        std::cout<<*reinterpret_cast<int*>(saved_gs + struct_offset(GameState, score))<<std::endl;
        std::cout<<*reinterpret_cast<bool*>(saved_gs + struct_offset(GameState, game_completed))<<std::endl;
        std::cout<<*reinterpret_cast<bool*>(saved_gs + struct_offset(GameState, boss_defeated))<<std::endl;
    }

    std::cout<<"\nHandling double delete of values"<<std::endl;
    GameState* gs = new GameState(66, 100, 900, false, true);
    Delete(gs);
    Delete(gs);
    return 0;
}

/*
Casting using C-style (Example : (int)val )
-> First casts using static_cast
-> If static_cast is not possible, then dymanic cast is used 
-> If dynamic_cast is not possible, then reinterpret_cast will be used
*/