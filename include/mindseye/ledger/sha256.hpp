#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace mindseye::ledger {

// Deterministic SHA-256. Returns 32 bytes.
std::vector<uint8_t> sha256(const std::vector<uint8_t>& data);

// Convenience: sha256 hex string
std::string sha256_hex(const std::vector<uint8_t>& data);

} // namespace mindseye::ledger
