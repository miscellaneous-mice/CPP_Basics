#pragma once

#include <sstream>
#include <iomanip>
#include <string>
#include <openssl/sha.h>
#include <vector>
#include <variant>

using Arg = std::variant<int, double, std::string>;

std::string serialize_arg(const Arg& arg);

std::string sha256(const std::string& data);

// Convert hex string to integer as string
std::string hex_to_decimal(const std::string& hex);