#include <iostream>
#include <array>
#include <bitset>
#include <iomanip>
#include <map>

constexpr std::array<std::pair<std::size_t, std::size_t>, 129> IEEE754_BitMap() noexcept {
    std::array<std::pair<std::size_t, std::size_t>, 129> map{};
    map[8]   = {0, 0};
    map[16]  = {5, 10};
    map[32]  = {8, 23};
    map[64]  = {11, 52};
    map[128] = {15, 112};
    return map;
}

template<std::size_t... I>
[[nodiscard]] constexpr auto make_exp_range(double exp, std::index_sequence<I...>) {
    constexpr size_t range_size = sizeof...(I);
    return std::array<double, range_size>{std::pow(exp, ((range_size - 1) - I))...};
}

template<std::size_t N>
[[nodiscard]] constexpr auto exp_range(double exp) {
    return make_exp_range(exp, std::make_index_sequence<N>{});
}

template<typename T>
constexpr auto ByteArray(T value) {
    std::array<std::bitset<8>, sizeof(T)> bytearray;
    for (size_t i = 0; i < sizeof(T); i++) {
        bytearray[i] = std::bitset<8>(*((unsigned char*)&value + i));
    }
    return bytearray;
}

template<size_t N>
constexpr typename std::enable_if<(N > 1) && (N <= 16), long double>::type IEEE754(std::array<std::bitset<8>, N> byteArray) {
    constexpr std::array<std::pair<std::size_t, std::size_t>, 129> exp_man_bit_map = IEEE754_BitMap();
    double exponent = 0, mantissa = 1;
    long double result;
    if constexpr (std::endian::native == std::endian::little) {
        for (size_t i = 0; i < (int)(N / 2); i++) {
            byteArray[i] = byteArray[i] ^ byteArray[(N - 1) - i];
            byteArray[(N - 1) - i] = byteArray[i] ^ byteArray[(N - 1) - i];
            byteArray[i] = byteArray[i] ^ byteArray[(N - 1) - i];
            // std::swap(bytearray[i], bytearray[N - 1 - i]);
        }
    }
    
    std::array<bool, N * 8> bitStream; // N bytes, 8 bits per byte
    size_t bitIndex = 0;

    for (const auto& byte : byteArray) {
        for (int i = 7; i >= 0; --i) {
            // Extract each bit (0 or 1) and store in the bitStream
            bitStream[bitIndex++] = (bool)((byte >> i) & std::bitset<8>(1)).to_ulong();
        }
    }

    bool signBit = bitStream[0];
    constexpr size_t e = std::get<0>(exp_man_bit_map[N * 8]);
    constexpr size_t m = std::get<1>(exp_man_bit_map[N * 8]);
    int32_t Bias = (int32_t)((std::pow(2, e) - 1) / 2);
    
    bitIndex = 1;
    for(const auto& exp_2 : exp_range<e>(2)) {
        exponent += (exp_2 * bitStream[bitIndex++]);
    }

    bitIndex = bitIndex + (m - 1);
    for(const auto& exp_0_5 : exp_range<m + 1>(1.0/2)) {
        if (bitIndex <= e) [[unlikely]] { break; }
        mantissa += (exp_0_5 * bitStream[bitIndex--]);
    }

    result = std::pow(-1, signBit) * mantissa * std::pow(2, (exponent - Bias));
    return result;
}

int main() {
    std::cout<<"Swap 2 variables"<<std::endl;
    int x = 5;
    int y = 6;
    x = x ^ y;
    y = x ^ y; // (x ^ y) ^ y -> x ^ (y ^ y) -> x ^ 0 -> x 
    x = x ^ y; // (x ^ y) ^ x -> (x ^ x) ^ y -> 0 ^ y -> y
    std::cout<<x<<", "<<y<<std::endl;

    std::cout<<"Endianess"<<std::endl;
    unsigned int i = 1;
    char ch = *(char*)&i;
    if (ch)
        std::cout<<"Little endian"<<std::endl;
    else
        std::cout<<"Big endian"<<std::endl;

    std::cout<<"\nReading Bytes"<<std::endl;
    int a = 10; // 0a 00 00 00 -> 4 bytes // Due to Little endian storage (LSB first)
    double b = a; // 00 00 00 00 00 00 24 40 -> 8 bytes // Implicit conversion happens automatically : double b = (double)a
    std::cout<<"int : "<<a<<", double : "<<b<<std::endl;

	double c = *(double*)&a; // 0a 00 00 00 00 00 00 00 -> 8 bytes, copied the 4 bytes of the a and allocated to c which is 8 bytes
	std::cout<<"int : "<<a<<", double : "<<c<<std::endl;

    int d = 16786442; // 01 00 24 0a (Raw bits)
    int e = *(char*)&d; // 0a -> Convert to Little endian format(0a 24 00 01) and then take the first byte(01)
    std::cout<<"double : "<<d<<", int : "<<e<<std::endl;

    e = *((char*)&d + 1); // 24 -> Convert to Little endian format (0a 24 00 01) and then take the second byte (24)
    std::cout<<"double : "<<d<<", int : "<<e<<std::endl;

    e = *((char*)&d + 2); // 00 -> Convert to Little endian format (0a 24 00 01) and then take the second byte (00)
    std::cout<<"double : "<<d<<", int : "<<e<<std::endl;

    e = *((char*)&d + 3); // 01 -> Convert to Little endian format (0a 24 00 01) and then take the second byte (01)
    std::cout<<"double : "<<d<<", int : "<<e<<std::endl;

    std::cout<<"\nIEEE754 Values"<<std::endl;
    {
        double value = 10.0;
        auto bytes = ByteArray(value);
        for (auto& byte : bytes) {
            std::cout<< byte << " ";
        }
        std::cout << std::endl;
    }
    {
        int64_t value = 10;
        auto bytes = ByteArray(value);
        for (auto& byte : bytes) {
            std::cout<< byte << " ";
        }
        std::cout << std::endl;
    }
    {
        double value = 10.0;
        auto bytes = ByteArray(value);
        std::cout<<IEEE754(bytes)<<std::endl;
    }
    {
        float value = 45.534879324f;
        auto bytes = ByteArray(value);
        std::cout<<IEEE754(bytes)<<std::endl;
    }
}
/*

Converting Hex to decimal using IEEE754 : 
-----------------------------------------------------------------
-----------------------------------------------------------------
Hexadecimal : 00 00 00 00 00 00 24 40 (little endian)

Convert to big endian Standard format : 40 24 00 00 00 00 00 00

Convert this Hexadecimal to binary format : 
40 = 01000000  
24 = 00100100  
00 = 00000000  
00 = 00000000  
00 = 00000000  
00 = 00000000  
00 = 00000000  
00 = 00000000  
Final Binary : 01000000 00100100 00000000 00000000 00000000 00000000 00000000 00000000
--------------------
Expression : 
For 64 bit value (8 bytes) : 
---------------------------------------------------------------------------------
| S | Exponent (11 bits) | Mantissa (52 bits)								    |
---------------------------------------------------------------------------------
| 0 | 10000000010 	     | 0100000000000000000000000000000000000000000000000000 |
---------------------------------------------------------------------------------
Sign Bit -> 0
--------------------
Exponent : 
10000000010
E = 1 × 2¹⁰ + 0 × 2⁹ + 0 × 2⁸ + 0 × 2⁷ + 0 × 2⁶ + 0 × 2⁵ + 0 × 2⁴ + 0 × 2³ + 0 × 2² + 1 × 2¹ + 0 × 2⁰  
E = 1024 + 2  
E = 1026

Bias : 1023 (Max value of Exponent : 2047 (2^11 - 1) -> -1023 to 1024)
--------------------
Mantissa : 
0100000000000000000000000000000000000000000000000000 -> mantissa bits
1.0100000000000000000000000000000000000000000000000000 -> In Binary

M = 1 + (0 * 1/2) + (1 * 1/4) + (0 * 1/8) + (0 * 1/16) + (0 * 1/32) .....) => 1.25
--------------------
Result : 
Value = (-1 ^ S) * M * (2 ^ (E - Bias))
Value = (-1 ^ 0) * 1.25 * (2 ^ (1026 - 1023))
Value = 1 * 1.25 * (2 ^ 3)
Value = 1.25 * 8 = 10

-----------------------------------------------------------------
-----------------------------------------------------------------
Hexadecimal : 01 00 24 0a (little endian)

Convert to big endian Standard format : 0a 24 00 01

Convert this Hexadecimal to binary format : 
0a = 00001010
24 = 00100100 
00 = 00000000  
01 = 00000001
Final Binary : 00001010 00100100 00000000 00000001
--------------------
Expression : 
For 32 bit value (4 bytes) : 
---------------------------------------------------------------------------------
| S | Exponent (8 bits)  | Mantissa (23 bits)								    |
---------------------------------------------------------------------------------
| 0 | 00010100 	         | 01001000000000000000001							    |
---------------------------------------------------------------------------------
Sign Bit -> 0
--------------------
Exponent : 
00010100
E = 0 × 2⁷ + 0 × 2⁶ + 0 × 2⁵ + 1 × 2⁴ + 0 × 2³ + 1 × 2² + 0 × 2¹ + 0 × 2⁰  
E = 16 + 4 = 20

Bias : 127 (Max value of Exponent : 255 (2^8 - 1) -> -127 to 128)
--------------------
Mantissa : 
01001000000000000000001 -> mantissa bits
1.01001000000000000000001 -> In Binary

M = 1 + (0 * 1/2) + (1 * 1/4) + (0 * 1/8) + (0 * 1/16) + (1 * 1/32) ..... + (1 * 1/(2^23))
M = 1 + 0.25 + 0.03125 + 0.00000012
M = 1.28125012
--------------------
Result : 
Value = (-1 ^ S) * M * (2 ^ (E - Bias))
Value = (-1 ^ 0) * 1.28125012 * (2 ^ (20 - 127))
Value = 1.28125012 * 6.16297582e-33
Value = 7.89631351e-33

-----------------------------------------------------------------
-----------------------------------------------------------------
*/