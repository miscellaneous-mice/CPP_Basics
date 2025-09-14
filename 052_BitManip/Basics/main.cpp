#include <iostream>
#include <cstdint>
#include <atomic>
#include <bitset>

// typedef enum {
//     STATUS_OK = 0x000000001,
//     STATUS_FAULT_OVERTEMP = 0x000000002,
//     STATUS_FAULT_UNDERVOLTAGE = 0x000000004,
//     STATUS_RUNNING = 0x000000008,
//     STATUS_IDLE = 0x000000010
// } DeviceStatus;

enum class DeviceStatus : uint32_t {
    OK                = 0x01,
    FAULT_OVERTEMP    = 0x02,
    FAULT_UNDERVOLTAGE= 0x04,
    RUNNING           = 0x08,
    IDLE              = 0x10
};

// Bitwise operators for DeviceStatus
inline DeviceStatus operator|(DeviceStatus lhs, DeviceStatus rhs) {
    return static_cast<DeviceStatus>(
        static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
}
inline DeviceStatus operator&(DeviceStatus lhs, DeviceStatus rhs) {
    return static_cast<DeviceStatus>(
        static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
}
inline DeviceStatus& operator|=(DeviceStatus& lhs, DeviceStatus rhs) {
    lhs = lhs | rhs;
    return lhs;
}
inline DeviceStatus& operator&=(DeviceStatus& lhs, DeviceStatus rhs) {
    lhs = lhs & rhs;
    return lhs;
}

static std::atomic<int> print_inc = {0};

template<typename T>
T extract_bits(T value, size_t start_bit, size_t end_bit = 0) {
    static_assert(std::is_integral_v<T>, "Integral type required");

    if (start_bit < end_bit)
        std::swap(start_bit, end_bit);

    uint8_t width = start_bit - end_bit + 1;

    // Build mask for the required width
    auto mask = ((T(1) << width) - 1) << end_bit;

    return (value & mask) >> end_bit;
}

std::ostream& operator<<(std::ostream& stream, const DeviceStatus& status) {
    switch (status) {
        case DeviceStatus::OK: stream << "OK"; break;
        case DeviceStatus::FAULT_OVERTEMP: stream << "FAULT_OVERTEMP"; break;
        case DeviceStatus::FAULT_UNDERVOLTAGE: stream << "FAULT_UNDERVOLTAGE"; break;
        case DeviceStatus::RUNNING: stream << "RUNNING"; break;
        case DeviceStatus::IDLE: stream << "IDLE"; break;
        default: stream << "INVALID"; break;
    }
    return stream;
}

#define size_in_bits(T) (sizeof(T) * 8)
#define getmaxval(T) (std::pow(2, size_in_bits(T)) - 1)

template<typename T>
void set_bit(T& value, size_t n) {
    value |= (1 << n);
}

template<typename T>
void clr_bit(T& value, size_t n) {
    value &= ~(1 << n);
}

template<typename T>
std::bitset<size_in_bits(T)> auto_bitset(T value) {
    return std::bitset<size_in_bits(T)>(value);
}

int main() {
    int a = 10;
    int b = 6;
    int c = a & b;
    std::cout<<a<<" & "<<b<<" : "<<c<<std::endl;

    int d = a | b;
    std::cout<<a<<" | "<<b<<" : "<<d<<std::endl;

    int e = a ^ b;
    std::cout<<a<<" ^ "<<b<<" : "<<e<<std::endl;

    unsigned int f = ~e;
    std::cout<<"~"<<e<<" : "<<f<<std::endl;

    int g = e << d;
    std::cout<<e<<" << "<<d<<" : "<<g<<std::endl;

    int h = g >> e;
    std::cout<<g<<" >> "<<e<<" : "<<h<<std::endl;

    std::cout<<"\nBit Mask Operations"<<std::endl;
    std::cout<<"Bit extraction"<<std::endl;
    uint16_t Data = 0xB410;
    std::cout<<"9th bit to 14th bit of data : " << std::bitset<16>(Data) << ", is : " <<std::bitset<16>(extract_bits(Data, 9, 14))<<std::endl;

    std::cout<<"Data before : "<<auto_bitset(Data);
    set_bit(Data, 2);
    std::cout<<", After setting 2nd bit : "<<auto_bitset(Data)<<std::endl;

    std::cout<<"Data before : "<<auto_bitset(Data);
    clr_bit(Data, 2);
    std::cout<<", After clearing 2nd bit : "<<auto_bitset(Data)<<std::endl;

    std::cout<<"\nDataGrams" <<std::endl;
    auto auto_inc_print = [] (bool reset, auto... msg) {
        (reset) ? print_inc = 0 : print_inc++;
        std::cout << "Example " << print_inc;
        ((std::cout << " : " << msg << " "), ...);
        std::cout << std::endl;
    };

    DeviceStatus status = DeviceStatus::OK;
    auto_inc_print(false, status);

    status &= DeviceStatus::OK;
    auto_inc_print(false, status);

    status &= DeviceStatus::IDLE;
    auto_inc_print(false, status);

    status |= DeviceStatus::RUNNING;
    status |= DeviceStatus::FAULT_UNDERVOLTAGE;

    auto_inc_print(false, status);
    auto_inc_print(false, status & DeviceStatus::RUNNING);
    auto_inc_print(false, status & DeviceStatus::FAULT_UNDERVOLTAGE);
    auto_inc_print(false, status & DeviceStatus::OK);

    status |= DeviceStatus::OK;
    auto_inc_print(false, status);

    auto_inc_print(false, status & DeviceStatus::OK);
    auto_inc_print(false, status & DeviceStatus::FAULT_UNDERVOLTAGE);
    auto_inc_print(false, status & DeviceStatus::FAULT_OVERTEMP);
    auto_inc_print(false, status & DeviceStatus::IDLE);
}

/*
a = 0000 0000 0000 0000 0000 0000 0000 1010 -> 10
b = 0000 0000 0000 0000 0000 0000 0000 0110 -> 6
c = a & b -> 0000 0000 0000 0000 0000 0000 0000 0010 -> 2
d = a | b -> 0000 0000 0000 0000 0000 0000 0000 1110 -> 14
e = a ^ b -> 0000 0000 0000 0000 0000 0000 0000 1100 -> 12
f = ~e -> 1111 1111 1111 1111 1111 1111 1111 0011 -> 4294967283 (unsigned), -13 (signed)
g = e << d -> 0000 0000 0000 0011 0000 0000 0000 0000 -> 196608
h = g >> e -> 0000 0000 0000 0000 0000 0000 0011 0000 -> 48
*/