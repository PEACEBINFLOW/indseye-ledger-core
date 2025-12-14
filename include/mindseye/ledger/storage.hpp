#pragma once

#include "mindseye/ledger/block.hpp"
#include <optional>
#include <string>
#include <vector>

namespace mindseye::ledger {

class IStorage {
public:
  virtual ~IStorage() = default;

  virtual void append(const Block& b) = 0;
  virtual std::optional<Block> get_latest() const = 0;
  virtual std::vector<Block> read_all() const = 0;
};

// In-memory storage (for tests/dev)
class MemoryStorage final : public IStorage {
public:
  void append(const Block& b) override;
  std::optional<Block> get_latest() const override;
  std::vector<Block> read_all() const override;

private:
  std::vector<Block> blocks_;
};

// File storage (simple line-based persistence)
// Deterministic, explicit format; no database required.
class FileStorage final : public IStorage {
public:
  explicit FileStorage(std::string path);

  void append(const Block& b) override;
  std::optional<Block> get_latest() const override;
  std::vector<Block> read_all() const override;

private:
  std::string path_;
};

} // namespace mindseye::ledger
