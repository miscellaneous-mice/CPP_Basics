#include "hashing.h"

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