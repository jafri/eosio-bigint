// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include <evm.hpp>

#include <algorithm>
#include <limits>

using namespace std;

namespace eevm
{
  using ET = Exception::Type;

  uint256_t eevm::Stack::pop()
  {
    // TODO: don't check size for every single pop, but rather once at the
    // beginning of each op handler in vm.cpp
    if (st.empty()) {
      eosio::check(false, "Stack out of range (outOfBounds)");
    }

    uint256_t val = st.front();
    st.pop_front();
    return val;
  }

  uint64_t eevm::Stack::pop64()
  {
    const auto val = pop();
    if (val > numeric_limits<uint64_t>::max()) {
      eosio::check(false, "Value on stack (" + to_hex_string(val) + ") is larger than 2^64 (outOfBounds)");
    }

    return static_cast<uint64_t>(val);
  }

  void eevm::Stack::push(const uint256_t& val)
  {
    if (size() == MAX_SIZE) {
      if (val > numeric_limits<uint64_t>::max()) {
        eosio::check(false, "Stack mem exceeded (" + to_string(size()) +
          " == " + to_string(MAX_SIZE) + ") (outOfBounds");
      }
    }

    // TODO Handle exception?
    // eosio::check(false, "bad_alloc while pushing onto stack");
    st.push_front(val);
  }

  uint64_t eevm::Stack::size() const
  {
    return st.size();
  }

  void eevm::Stack::swap(uint64_t i)
  {
    if (i >= size()) {
      eosio::check(false, "Swap out of range (" + to_string(i) + " >= " + to_string(size()) + ") (outOfBounds)");
    }

    std::swap(st[0], st[i]);
  }

  void eevm::Stack::dup(uint64_t a)
  {
    if (a >= size()) {
      eosio::check(false, "Dup out of range (" + to_string(a) + " >= " + to_string(size()) + ") (outOfBounds)");
    }

    st.push_front(st[a]);
  }

  std::ostream& operator<<(std::ostream& os, const eevm::Stack& s)
  {
    int i = 0;
    os << std::dec;
    for (const auto& elem : s.st)
      os << fmt::format(" {}: {}", i++, eevm::to_hex_string(elem)) << std::endl;
    return os;
  }
} // namespace eevm
