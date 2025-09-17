#include "hashing.h"
#include "stringstream.h"

template<typename... Types>
std::string gen_uniq_id(int precision, const Types&... args) {
    SStream serialized;
    ((serialized << std::string(args)), ...);

    std::string hash_hex = sha256(serialized.ret_str());
    std::string big_decimal = hex_to_decimal(hash_hex);

    if (precision > 0 && big_decimal.size() > precision)
        return big_decimal.substr(big_decimal.size() - precision);

    return big_decimal;
}

int main() {
    std::string uid = gen_uniq_id(
        10,
        "x01","dsfkj3242k3l"
    );
    std::cout << "Unique ID: " << uid << std::endl;
}

/*
mdkir build && cd build
cmake ../
make
./exec/hashing_exec


Now you can delete `056_Build_Systems/CMake/04_CustomLibs/build/lib/libmylib.a` and run `./exec/hashing_exec` it will work as libmylib.a is a static library
But when you delete `056_Build_Systems/CMake/04_CustomLibs/build/customlib/libsstreamlib.dylib` and run `./exec/hashing_exec` it will not work as it is a shared/dynamic library
*/