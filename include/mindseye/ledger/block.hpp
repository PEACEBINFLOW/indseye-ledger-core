#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace mindseye::ledger {

struct Block {
  std::string block_id;
  std::string prev_hash;                 // hex
  std::vector<std::vector<uint8_t>> entries; // opaque envelopes (bytes)
  int64_t ts_ms = 0;

  std::string merkle_root_hex;           // computed
  std::string block_hash_hex;            // computed (header hash)
};

// Deterministically compute block merkle root + block hash.
Block finalize_block(Block b);

} // namespace mindseye::ledger
