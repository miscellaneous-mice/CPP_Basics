#include <iostream>
#include <format>

class Vec {
private:
    int x, y;
public:
    Vec(int a, int b) : x(a), y(b) {};
    int get_x() const { return x; }
    int get_y() const { return y; }
};

// namespace std {
//     template <>
//     struct formatter<Vec> : std::formatter<std::string> {
//         auto format(const Vec& vec, format_context& ctx)  const{
//             return std::formatter<std::string>::format(std::format("x : {}, y: {}", vec.get_x(), vec.get_y()), ctx);
//         }
//     };
// }

template <>
struct std::formatter<Vec> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin(); // no custom format options
    }
    auto format(const Vec& v, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "x : {}, y : {}", v.get_x(), v.get_y());
    }
};

int main() {
    Vec vector(1, 2);
    std::string string = std::format("Speed is {}, mass is {}, name is {}, Vector is {}", 5.5f, 40, "Cherno", vector);
    std::cout<<string<<std::endl;
}