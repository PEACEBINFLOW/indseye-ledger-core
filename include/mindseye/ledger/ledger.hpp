#pragma once

#include "mindseye/ledger/storage.hpp"
#include <memory>
#include <string>
#include <vector>

namespace mindseye::ledger {

class Ledger {
public:
  explicit Ledger(std::shared_ptr<IStorage> storage);

  // Append a new block created from entries.
  // Returns finalized block.
  Block append_block(std::vector<std::vector<uint8_t>> entries, int64_t ts_ms);

  // Verify entire chain integrity:
  // - block hashes match recomputation
  // - prev_hash matches previous block hash
  // - merkle_root matches entries
  bool verify_chain(std::string* error = nullptr) const;

  std::vector<Block> read_all() const;

private:
  std::shared_ptr<IStorage> storage_;
};

} // namespace mindseye::ledger
