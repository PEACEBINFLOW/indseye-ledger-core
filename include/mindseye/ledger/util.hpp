#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace mindseye::ledger {

// Convert bytes to lowercase hex string
std::string to_hex(const std::vector<uint8_t>& bytes);

// Convert string to bytes (raw UTF-8 bytes)
std::vector<uint8_t> to_bytes(const std::string& s);

} // namespace mindseye::ledger
