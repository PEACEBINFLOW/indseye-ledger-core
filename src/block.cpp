#include "mindseye/ledger/block.hpp"
#include "mindseye/ledger/merkle.hpp"
#include "mindseye/ledger/sha256.hpp"
#include "mindseye/ledger/util.hpp"

namespace mindseye::ledger {

static std::vector<uint8_t> hash_entry(const std::vector<uint8_t>& entry) {
  return sha256(entry);
}

Block finalize_block(Block b) {
  // leaf hashes
  std::vector<std::vector<uint8_t>> leaf;
  leaf.reserve(b.entries.size());
  for (const auto& e : b.entries) leaf.push_back(hash_entry(e));

  auto root = merkle_root(leaf);
  b.merkle_root_hex = to_hex(root);

  // block header bytes: block_id|prev_hash|ts_ms|merkle_root
  std::string header = b.block_id + "|" + b.prev_hash + "|" + std::to_string(b.ts_ms) + "|" + b.merkle_root_hex;
  b.block_hash_hex = sha256_hex(to_bytes(header));
  return b;
}

} // namespace mindseye::ledger
