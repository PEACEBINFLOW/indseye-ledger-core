#include "mindseye/ledger/ledger.hpp"
#include "mindseye/ledger/storage.hpp"

#include <chrono>
#include <iostream>

static int64_t now_ms() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

int main() {
  auto storage = std::make_shared<mindseye::ledger::MemoryStorage>();
  mindseye::ledger::Ledger ledger(storage);

  for (int i = 0; i < 3; ++i) {
    std::vector<std::vector<uint8_t>> entries;
    entries.push_back(std::vector<uint8_t>{static_cast<uint8_t>('a' + i)});
    ledger.append_block(std::move(entries), now_ms() + i);
  }

  std::string err;
  bool ok = ledger.verify_chain(&err);
  std::cout << (ok ? "OK\n" : ("FAIL: " + err + "\n"));
  return ok ? 0 : 1;
}
