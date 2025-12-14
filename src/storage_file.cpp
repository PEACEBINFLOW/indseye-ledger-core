#include "mindseye/ledger/storage.hpp"
#include "mindseye/ledger/util.hpp"

#include <fstream>
#include <sstream>

namespace mindseye::ledger {

// Very explicit, deterministic persistence format:
// One block per line.
// Fields separated by TAB:
// block_id \t prev_hash \t ts_ms \t merkle_root_hex \t block_hash_hex \t entry_count \t entry_hex_0 \t ... \t entry_hex_n
static std::string bytes_to_hex(const std::vector<uint8_t>& b) { return to_hex(b); }

static std::vector<uint8_t> hex_to_bytes(const std::string& hex) {
  std::vector<uint8_t> out;
  out.reserve(hex.size()/2);
  auto val = [](char c)->int{
    if (c>='0'&&c<='9') return c-'0';
    if (c>='a'&&c<='f') return 10 + (c-'a');
    if (c>='A'&&c<='F') return 10 + (c-'A');
    return 0;
  };
  for (size_t i=0;i+1<hex.size();i+=2) {
    out.push_back(static_cast<uint8_t>((val(hex[i])<<4) | val(hex[i+1])));
  }
  return out;
}

FileStorage::FileStorage(std::string path) : path_(std::move(path)) {}

void FileStorage::append(const Block& b) {
  std::ofstream f(path_, std::ios::app);
  f << b.block_id << "\t"
    << b.prev_hash << "\t"
    << b.ts_ms << "\t"
    << b.merkle_root_hex << "\t"
    << b.block_hash_hex << "\t"
    << b.entries.size();

  for (const auto& e : b.entries) {
    f << "\t" << bytes_to_hex(e);
  }
  f << "\n";
}

std::optional<Block> FileStorage::get_latest() const {
  auto all = read_all();
  if (all.empty()) return std::nullopt;
  return all.back();
}

std::vector<Block> FileStorage::read_all() const {
  std::ifstream f(path_);
  if (!f.good()) return {};

  std::vector<Block> blocks;
  std::string line;
  while (std::getline(f, line)) {
    if (line.empty()) continue;
    std::stringstream ss(line);

    Block b;
    std::string ts_ms, entry_count;
    std::getline(ss, b.block_id, '\t');
    std::getline(ss, b.prev_hash, '\t');
    std::getline(ss, ts_ms, '\t');
    std::getline(ss, b.merkle_root_hex, '\t');
    std::getline(ss, b.block_hash_hex, '\t');
    std::getline(ss, entry_count, '\t');

    b.ts_ms = std::stoll(ts_ms);
    size_t n = static_cast<size_t>(std::stoull(entry_count));

    b.entries.clear();
    b.entries.reserve(n);

    for (size_t i = 0; i < n; ++i) {
      std::string entry_hex;
      if (!std::getline(ss, entry_hex, '\t')) break;
      b.entries.push_back(hex_to_bytes(entry_hex));
    }

    blocks.push_back(std::move(b));
  }

  return blocks;
}

} // namespace mindseye::ledger
