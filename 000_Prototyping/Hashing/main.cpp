#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <openssl/sha.h>
#include <vector>
#include <variant>

using Arg = std::variant<int, double, std::string>;

std::string serialize_arg(const Arg& arg) {
    std::ostringstream oss;
    if (std::holds_alternative<int>(arg))
        oss << "i:" << std::get<int>(arg);
    else if (std::holds_alternative<double>(arg))
        oss << "f:" << std::get<double>(arg);
    else if (std::holds_alternative<std::string>(arg))
        oss << "s:" << std::get<std::string>(arg);
    return oss.str();
}

std::string sha256(const std::string& data) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)data.c_str(), data.size(), hash);
    std::ostringstream oss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    return oss.str();
}

// Convert hex string to integer as string
std::string hex_to_decimal(const std::string& hex) {
    std::string result = "0";
    for (char c : hex) {
        int digit = (c >= '0' && c <= '9') ? c - '0'
                   : (c >= 'a' && c <= 'f') ? c - 'a' + 10
                   : c - 'A' + 10;

        int carry = digit;
        for (int i = result.size() - 1; i >= 0; --i) {
            int num = (result[i] - '0') * 16 + carry;
            result[i] = '0' + (num % 10);
            carry = num / 10;
        }

        while (carry > 0) {
            result = char('0' + (carry % 10)) + result;
            carry /= 10;
        }
    }
    return result;
}

template<typename... Types>
std::string gen_uniq_id(int precision, const Types&... args) {
    std::ostringstream serialized;
    ((serialized << ":" << serialize_arg(args)), ...);

    std::string hash_hex = sha256(serialized.str());
    std::string big_decimal = hex_to_decimal(hash_hex);

    if (precision > 0 && big_decimal.size() > precision)
        return big_decimal.substr(big_decimal.size() - precision);

    return big_decimal;
}

int main() {
    std::string uid = gen_uniq_id(
        10,
        12342,
        234578.344,
        std::string("x01"),
        std::string("dsfkj3242k3l")
    );
    std::cout << "Unique ID: " << uid << std::endl;

    return 0;
}

/*
cd 000_Prototyping/Hashing/
brew install openssl
brew --prefix openssl
clang++ -std=c++20 main.cpp -o main -I /opt/homebrew/opt/openssl@3/include -L /opt/homebrew/opt/openssl@3/lib -lssl -lcrypto
*/
