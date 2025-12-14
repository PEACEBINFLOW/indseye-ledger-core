#pragma once
#include <cstdint>
#include <vector>

namespace mindseye::ledger {

// Computes Merkle root from leaf hashes (each leaf is already a 32-byte hash).
// If odd number of nodes, duplicates the last (standard Merkle behavior).
std::vector<uint8_t> merkle_root(const std::vector<std::vector<uint8_t>>& leaf_hashes);

} // namespace mindseye::ledger
