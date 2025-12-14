#include "mindseye/ledger/merkle.hpp"
#include "mindseye/ledger/sha256.hpp"

namespace mindseye::ledger {

std::vector<uint8_t> merkle_root(const std::vector<std::vector<uint8_t>>& leaf_hashes) {
  if (leaf_hashes.empty()) return sha256({}); // deterministic empty root

  std::vector<std::vector<uint8_t>> level = leaf_hashes;

  while (level.size() > 1) {
    std::vector<std::vector<uint8_t>> next;
    next.reserve((level.size() + 1) / 2);

    for (size_t i = 0; i < level.size(); i += 2) {
      const auto& left = level[i];
      const auto& right = (i + 1 < level.size()) ? level[i + 1] : level[i]; // duplicate last
      std::vector<uint8_t> concat;
      concat.reserve(left.size() + right.size());
      concat.insert(concat.end(), left.begin(), left.end());
      concat.insert(concat.end(), right.begin(), right.end());
      next.push_back(sha256(concat));
    }
    level = std::move(next);
  }

  return level[0];
}

} // namespace mindseye::ledger
