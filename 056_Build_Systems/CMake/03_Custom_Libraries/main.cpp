#include <iostream>
#include "hashing.h"

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
mdkir build && cd build
cmake ../
make
./exec/hashing_exec
*/
